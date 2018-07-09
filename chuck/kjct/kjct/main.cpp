#include<iostream>
using std::cin;
using std::cout;
#include"wordmap.h"
#include"Debug.h"
#include"findword.h"
#include"Document.h"
int main() {
	WordMap m_wordmap("word/word1.txt");
	if (!m_wordmap.init()) {
		Debug::GetInstance()->LogInfo("m_wordmap init() failed");
	}
	Document document;
	FindWord findword;
	findword.GetWords("./input/0.txt", m_wordmap, document);
	//Debug::GetInstance()->LogInfo(document);
	document.make_word(m_wordmap);
	Debug::GetInstance()->LogInfo(document);
	return 0;
}