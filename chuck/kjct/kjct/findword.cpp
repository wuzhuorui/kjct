#include "findword.h"
#include<fstream>
#include<sstream>
#include<iostream>
using std::ifstream;
using std::istringstream;
vector<string> FindWord::GetKeyWords(const string & filename, const WordMap& wordmap)
{
	vector<string> l_keyword;
	ifstream inputfile(filename);
	if (!inputfile.is_open())
	{
		std::cerr << "cann't not open file:" << filename;
		return l_keyword;
	}
	string sinput;
	string last;
	while (std::getline(inputfile, sinput))
	{
		last = sinput;
		int begpos = 0;
		int length;
		while ((length = getlocalfindstring(last, begpos)) != 0)
		{
			int movelen = ischinese(&last[begpos]) ?  2:1;
			int findlen = -1;
			while (movelen<=length)
			{
				string ls = last.substr(begpos, movelen);
				auto res = wordmap.m_map.find(ls);
				if (res != wordmap.m_map.end())
				{
					findlen = movelen;
				}
				movelen += ischinese(&last[begpos + movelen]) ? 2 : 1;
			}
			if (findlen != -1)
			{
				l_keyword.push_back(last.substr(begpos, findlen));
				begpos = begpos + findlen;
			}
			else {
				begpos += length;
			}
		}
	}
	return l_keyword;
}

bool FindWord::ischinese(const char* c)
{
	unsigned char cur = *c;
	unsigned char next = *(c + 1);
	if (next == 0)return false;
	return (cur >= 0xB0 && cur <= 0xF7) && (next >= 0xA1 && next <= 0xFE);
}

int FindWord::getlocalfindstring(const string& ostring,int begpos)
{
	int size = wsize;
	int endpos = begpos;
	while (size > 0 && ostring[endpos])
	{
		if (ischinese(&ostring[endpos])) {
			endpos++;
		}
		size--;
		endpos++;
	}
	return endpos-begpos;
}