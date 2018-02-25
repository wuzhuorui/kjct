#pragma once
#include<istream>
#include<unordered_map>
#include<string>
#include<ctime>
class WordMap {
public:
	WordMap(const std::string& filename);
	~WordMap();
	bool init();
	std::unordered_map<std::string, int> m_map;
	std::string m_filename;

private:
	time_t difftime;
	std::string timestr( tm*);
};