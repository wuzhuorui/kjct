#pragma once
#include<string>
using std::string;
#include<unordered_map>
using std::unordered_map;
#include"wordmap.h"
#include<iostream>
using std::ostream;
using std::string;
using std::vector;
#include"Document.h"
class FindWord 
{
public:
	FindWord() {};
	~FindWord() {};
	bool GetWords(const string& filename,const WordMap& wordmap, Document& document);

};

class FindWordHelp {
public:
	enum FindRes {
		stop,
		skip,
		find,
	};
	FindWordHelp(std::string inputstring);
	FindRes next(const WordMap& wordmap);
	void append(std::string inputstring);
	std::string cur();
private:
	std::string m_inputstring;
	size_t m_cur_pos;
	int m_find_length = 0;
	size_t wsize = 8;
	int getlength(const char*);
	bool ischinese(const char* c);//unused
	int getlocalfindstring(const string& ostring, int begpos);
};