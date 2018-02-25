#pragma once
#include<string>
using std::string;
#include<vector>
using std::vector;
#include"wordmap.h"
class FindWord 
{
public:
	FindWord() {};
	~FindWord() {};
	vector<string> GetKeyWords(const string& filename,const WordMap& wordmap);
private:
	int wsize = 5;
	bool ischinese(const char* c);
public:
	int getlocalfindstring(const string& ostring, int begpos);
};