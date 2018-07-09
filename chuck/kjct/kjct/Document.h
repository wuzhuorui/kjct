#pragma once
#include<vector>
#include<string>
using std::vector;
using std::string;
#include<ostream>
using std::ostream;
#include<unordered_set>
#include<unordered_map>
using std::unordered_map;
using std::unordered_set;
#include<map>
using std::map;
#include<memory>
#include"wordmap.h"
#include"Nword.h"
class Word {
public:
	Word(string s);
	string m_s;
	double value = 1;
	double m_count = 0;
	double m_struct_value = 0;
	map<int, int> m_map;
	double sumwidget;
	friend bool operator < (const Word& l, const Word& r);
};

template<>
struct std::equal_to<Word> {
	bool operator()(const Word& left, const Word& right) const _NOEXCEPT {
		return std::equal_to<std::string>()(left.m_s, right.m_s);
	}
};

template<>
struct std::hash<Word> {
	size_t operator()(const Word& _Keyval) const _NOEXCEPT
	{	// hash _Keyval to size_t value by pseudorandomizing transform
		return std::hash<std::string>()(_Keyval.m_s);
	}
};

class Document 
{
public:
	Document() {};
	~Document() {};
	vector<vector<string>> m_document;
	vector<double> m_widget;
	int m_curwidgetindex = -1;
	void Push(vector<string>& strings) {
		m_document.push_back(strings);
	}
	void Push(double widget) {
		m_widget.push_back(widget);
		m_document.push_back(vector<string>{"@"});
	}
	void make_word(const WordMap& wordmap);
	void make_Nword();
	friend ostream& operator << (ostream& output, const Document& right);
	std::vector<Word> m_words;
	std::vector<Word> m_old_words;
	void CalValue();
};