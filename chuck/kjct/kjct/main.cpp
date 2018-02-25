#include"wordmap.h"
#include<iostream>
#include<string>
#include"findword.h"
using std::string;
int main()
{

	WordMap m_wordmap("../../../word/word1.txt");
	FindWord m_findword;
	if (!m_wordmap.init()) { return 0; };
	vector<string> res= m_findword.GetKeyWords("../../../inputfile/1999.txt", m_wordmap);
	for (auto elems : res)
		std::cout << elems << " ";
	return 0;
}
