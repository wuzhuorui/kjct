#include "findword.h"
#include<fstream>
#include<sstream>
#include<iostream>
using std::ifstream;
using std::istringstream;
#include"Debug.h"
bool FindWord::GetWords(const string& filename, const WordMap& wordmap , Document& document)
{
		ifstream inputfile(filename);
		if (!inputfile.is_open())
		{
			std::cerr << "cann't not open file:" << filename <<std::endl;
			return false;
		}
		string sinput;
		vector<std::string> cur;
		FindWordHelp findword("");
		FindWordHelp::FindRes isfind;
		while (std::getline(inputfile, sinput))
		{
			std::stringstream getnum(sinput);
			double widget = 0;
			if (getnum >> widget) {
				document.Push(widget);
				continue;
			}
			findword.append(sinput);
			while (isfind = findword.next(wordmap))
			{
				if (isfind == FindWordHelp::FindRes::skip)
				{
					if (cur.size() > 0) {
						document.Push(cur);
					}
					cur.clear();
					continue;
				}
				string onewords = findword.cur();
				cur.push_back(onewords);
			}
		}

	return true;
}

bool FindWordHelp::ischinese(const char* c)
{
	unsigned char cur = *c;
	unsigned char next = *(c + 1);
	if (next == 0)return false;
	return (cur >= 0xB0 && cur <= 0xF7) && (next >= 0xA1 && next <= 0xFE);
}

int FindWordHelp::getlocalfindstring(const string& ostring,int begpos)
{
	int size = wsize;
	int endpos = begpos;
	while (size > 0 && ostring[endpos])
	{
		endpos += getlength(&ostring[endpos]);
		size--;
	}
	return endpos-begpos;
}

int FindWordHelp::getlength(const char* c)
{
	if (*(c+1) == 0)return 1;

	unsigned char cur = *c;
	unsigned char next = *(c + 1);
	if (next == 0)return 1	;
	
	if (cur < 0x80)
	{
		return 1;
	}
	else if (cur < 0xE0)
	{
		return 2;
	}
	else if (cur < 0xF0)
	{
		return 3;
	}

	return ((cur >= 0xA0+1 && cur <= 0xA0+94) && (next >= 0xA0 + 1 && next <= 0xA0 + 94))?2:1;
}

FindWordHelp::FindWordHelp(std::string inputstring):m_inputstring(inputstring),m_cur_pos(0)
{
}

FindWordHelp::FindRes FindWordHelp::next(const WordMap& wordmap)
{
	m_cur_pos += m_find_length;
	m_find_length = getlocalfindstring(m_inputstring, m_cur_pos);
	if (m_find_length <= 3)return FindRes::stop;

	int movelen = getlength(&m_inputstring[m_cur_pos]);// ischinese(&last[begpos]) ? 2 : 1;
	int findlen = movelen;
	bool is_find = false;
	while (movelen <= m_find_length)
	{
		string ls = m_inputstring.substr(m_cur_pos, movelen);
		auto res = wordmap.find(ls);
		if (res)
		{
			findlen = movelen;
			is_find = true;
		}
		int len = getlength(&m_inputstring[m_cur_pos + movelen]);
		movelen += len; //(&last[begpos + movelen]) ? 2 : 1;
	}
	m_find_length = findlen;
	return  is_find ? FindRes::find : FindRes::skip;
}

void FindWordHelp::append(std::string inputstring)
{
	m_inputstring = m_inputstring.substr(m_cur_pos, m_find_length);
	m_inputstring += inputstring;
	m_cur_pos = 0;
	m_find_length = 0;
}

std::string FindWordHelp::cur()
{
	return m_inputstring.substr(m_cur_pos, m_find_length);
}
