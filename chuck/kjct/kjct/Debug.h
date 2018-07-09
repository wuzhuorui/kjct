#pragma once
#include<memory>
#include<string>
using std::shared_ptr;
#include<fstream>
using std::ofstream;
#include"Document.h"
#include"Nword.h"

class Debug
{
public:
	static shared_ptr<Debug> GetInstance();
	~Debug() {
		output.close();
	}
	void LogInfo(std::string s);
	void LogInfo(const Document& d); 
	void LogInfo(const Nword& d); 
private:
	ofstream output;
	Debug() {
		output.open("output/Debug.txt");
	}
};
