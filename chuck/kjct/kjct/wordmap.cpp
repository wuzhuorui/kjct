#include"wordmap.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<ctime>
WordMap::WordMap(const std::string& filename):m_filename(filename), difftime(5)
{
}

WordMap::~WordMap() {}

bool WordMap::init()
{
	std::ifstream input(m_filename);
	std::istringstream inputstring;
	time_t last;
	time(&last);
	time_t cur;
	if (input.is_open())
	{
		std::string inputs;
		tm nowtime; 
		localtime_s(&nowtime,&last);

		std::cout << "开始初始化分词库,当前时间" << timestr(&nowtime)<<std::endl;
		while (std::getline(input, inputs))
		{
			time(&cur);
			std::istringstream inputstring(inputs);
			int num;
			int num2;
			std::string word;
			inputstring >> num;
			inputstring >> word;
			inputstring >> num2;
			m_map[word] = num2;
			if (cur - last > difftime)
			{
				std::cout << "已初始化分词个数：" << m_map.size() << std::endl;
				last = cur;
			}

		}
		time(&cur);
		localtime_s(&nowtime, &cur);
		std::cout << "结束初始化分词库,当前时间" << timestr(&nowtime) << std::endl;
	}
	else
	{
		std::cerr << "can't not open file:" << m_filename;
		return false;
	}
	return true;
}

std::string WordMap::timestr(tm* nowtime)
{
	std::ostringstream out;
	out << nowtime->tm_hour << ":" << nowtime->tm_min << ":" << nowtime->tm_sec;
	return  std::move(out.str());
}
