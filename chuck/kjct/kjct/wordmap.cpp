#include"wordmap.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<ctime>
WordMap* WordMap::instance = nullptr;
WordMap::WordMap(const std::string& filename):m_filename(filename), difftime(5)
{
	instance = this;
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

		std::cout << "BeginInitWordMap: " << timestr(&nowtime)<<std::endl;
		while (std::getline(input, inputs))
		{
			time(&cur);
			std::istringstream inputstring(inputs);
			int num;
			int num2;
			std::string word;
			std::string type;
			inputstring >> num;
			inputstring >> word;
			inputstring >> num2;
			inputstring >> type;
			DicWord d(word, num2);
			if (type[0] == 'w') {
				d.m_type = DicWord::Type::unuse;
			}
			updataMap(d);
			if (cur - last > difftime)
			{
				std::cout << "InitWordCount:" << m_map.size() << std::endl;
				last = cur;
			}

		}
		time(&cur);
		localtime_s(&nowtime, &cur);
		std::cout << "EndInitWordMap" << timestr(&nowtime) << std::endl;
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
/*
bool WordMap::connectmysql()
{
	MYSQL *pConn = NULL;
	pConn = mysql_init(pConn);

	if (!mysql_real_connect(pConn, "116.56.143.162", "huochenpeng", "123456", "intelligentService", 0, NULL, 0))
	{
		printf("cann't connect :%s", mysql_error(pConn));
	}
	mysql_query(pConn, "set names utf8");
	if (mysql_query(pConn, "select * from tb_entryOfMachineLearning"))
	{
		printf("error:%s", mysql_error(pConn));
		return 0;
	}

	MYSQL_RES *result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int count = 0;
	while (row = mysql_fetch_row(result))
	{
		DicWord d(std::string(row[0]), 1.0);
		updataMap(d);
		std::cout << std::string(row[0]) << std::endl;
		count++;
	}

	mysql_free_result(result);
	mysql_close(pConn);


	return true;
}
*/
bool WordMap::find(std::string wordname)const
{
	return m_map.find(DicWord(wordname, 1.0)) != m_map.end();
}

bool WordMap::isNormal(std::string s) const
{
	auto res = m_map.find(DicWord(s, 1.0));
	return res != m_map.end() ? res->m_type == DicWord::Type::normal : true;
}

bool WordMap::updataMap(const DicWord & word)
{
	m_map.erase(word);
	m_map.insert(word);
	return true;
}

DicWord::DicWord(std::string name, double p):m_name(name),m_p(p)
{
	m_type = Type::normal;
}
