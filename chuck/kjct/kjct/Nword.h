#pragma once
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<unordered_map>
using std::unordered_map;
#include<ostream>
using std::ostream;
#include<set>
using std::set;
class Nword {
public:
	static Nword& AddNword(const vector<string>&,double v);
	static vector<unordered_map<string, Nword>> g_map;
	static void CalValue();
	static vector<int> g_Num;
	int GetType();
	Nword(const vector<std::string>&, double v);
	friend ostream& operator << (ostream& output, const Nword&);
	double m_count;
	double m_Value;
	vector<std::string> m_SubWord;
	static void Log();
	set<string> l_string;
	set<string> r_string;
};
