#include"Document.h"
#include<algorithm>
bool operator<(const Word & l, const Word & r)
{
	return l.m_s < r.m_s;
}

ostream& operator << (ostream& output, const Document& right) {
	for (auto elems : right.m_document) {
		for (auto elem : elems) {
			output << elem << " ";
		}
		output << std::endl;
	}

	for (int i = 0; i < right.m_words.size();i++) {
		output << i << "     " << right.m_words[i].m_s<< " " << right.m_words[i].value<< "\n";
		for (auto elems : right.m_words[i].m_map) {
			int index = elems.first;
			output << right.m_old_words[index].m_s << " " << elems.second << " ";
		}
		output << std::endl;
	}

	return output;
}

void Document::make_word(const WordMap& wordmap)
{
	std::unordered_map<std::string,int> words;
	m_curwidgetindex = -1;
	for (auto elems : m_document) {
		for (int pos = 0; pos < elems.size();pos++) {
			if (elems[pos][0] == '@') {
				m_curwidgetindex++;
				continue;
			}
			int cur_pos;
			std::unordered_map<std::string, int>::iterator res = words.find(elems[pos]);
			if (res != words.end()) {
				//find
				cur_pos = res->second;
			}
			else {
				m_words.push_back(elems[pos]);
				words[elems[pos]] = m_words.size() - 1;
				cur_pos = m_words.size() - 1;
			}
			m_words[cur_pos].m_count++;
			m_words[cur_pos].m_struct_value += m_widget[m_curwidgetindex];

			for (int prepos = pos -1; prepos >= 0 && prepos >= pos-5; prepos--) {
				std::unordered_map<std::string, int>::iterator left = words.find(elems[prepos]);
				int pre_pos = left->second;
				auto wordmapres = wordmap.isNormal(elems[pos]) && wordmap.isNormal(elems[prepos]);
				int widget = wordmapres?6 - (pos - prepos):0;
				m_words[cur_pos].m_map[pre_pos] += widget;
				m_words[pre_pos].m_map[cur_pos] += widget;
			}
		}
	}
	for (int i = 0; i < m_words.size(); i++) {
		m_words[i].sumwidget = 0;
		for (auto elems : m_words[i].m_map) {
			m_words[i].sumwidget += elems.second;
		}
	}
	CalValue();
	make_Nword();
	Nword::CalValue();
	Nword::Log();
}

void Document::CalValue()
{
	m_old_words = m_words;
	for (int time = 0; time < 10; time++)
	{
		for (int i = 0; i < m_words.size(); i++) {
			m_words[i].value = 0.8;
			for (auto elems : m_words[i].m_map) {
				int index = elems.first;
				if (m_words[index].sumwidget > 0.1) {
					m_words[i].value += (0.2 *(elems.second*1.0) / m_words[index].sumwidget)*m_words[index].value;
				}
			}
		}
	}
	for (int i = 0; i < m_words.size(); i++) {
		if (m_words[i].value > 0.9)
		{
			m_words[i].value *= m_words[i].m_struct_value / m_words[i].m_count;
		}
	}
	std::sort(m_words.begin(), m_words.end(), [](const Word&l, const Word&r) {return l.value > r.value; });
}

Word::Word(string s):m_s(s)
{

}


void Document::make_Nword()
{
	std::unordered_map<std::string, double> map_words;
	for (auto& elems : m_words) {
		map_words[elems.m_s] = elems.value;
	}
	for (auto elems : m_document) {
		for (int pos = 0; pos < elems.size(); pos++) {
			vector<string> tmp(1, elems[pos]);
			Nword& res = Nword::AddNword(tmp, map_words[elems[pos]]);
			if (pos - 1 >= 0)
				res.l_string.insert(elems[pos - 1]);
			if (pos + 1 < elems.size())
				res.r_string.insert(elems[pos + 1]);

			for (int r = pos + 2; r < pos + 6 && r < elems.size()+1; r++) {
				vector<string> tmp1(&elems[pos], &elems[pos]+r-pos);
				Nword& res1=Nword::AddNword(tmp1, 0);
				if (pos - 1 >= 0)
					res1.l_string.insert(elems[pos - 1]);
				if (r < elems.size())
					res1.r_string.insert(elems[r]);
			}
		}
	}
}

