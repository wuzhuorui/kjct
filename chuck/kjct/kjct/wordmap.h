#pragma once
#include<istream>
#include<unordered_set>
#include<string>
#include<ctime>
#include<winsock.h>
//#include<mysql.h>

struct DicWord {
	std::string m_name;
	double m_p;
	enum Type {
		normal,
		unuse
	};
	Type m_type;
public:
	DicWord() { m_type = Type::normal; };
	DicWord(std::string name, double p);
};

template<>
struct std::hash<DicWord> {
	size_t operator()(const DicWord& _Keyval) const _NOEXCEPT
	{	// hash _Keyval to size_t value by pseudorandomizing transform
		return std::hash<std::string>()(_Keyval.m_name);
	}
};

template<>
struct std::equal_to<DicWord> {
	bool operator()(const DicWord& left,const DicWord& right) const _NOEXCEPT {
		return std::equal_to<std::string>()(left.m_name, right.m_name);
	}
};

class WordMap {
public:
	WordMap(const std::string& filename);
	~WordMap();
	bool init();
	std::unordered_set<DicWord> m_map;
	bool find(std::string)const;
	bool isNormal(std::string)const;
	bool updataMap(const DicWord&);
	static WordMap* instance;
private:
	time_t difftime;
	//bool connectmysql();
	std::string m_filename;
	std::string timestr( tm*);
};