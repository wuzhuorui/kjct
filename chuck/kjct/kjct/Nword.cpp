#include "Nword.h"
#include"Debug.h"
#include<algorithm>
#include"wordmap.h"
vector<unordered_map<string, Nword>> Nword::g_map(6);
vector<int> Nword::g_Num(6);
Nword& Nword::AddNword(const vector<string>& vs,double v)
{
	g_Num[vs.size()]++;
	string s = "";
	for (auto elems : vs)
		s += elems;
	auto map_word = g_map[vs.size()].find(s);
	if (map_word == g_map[vs.size()].end()) {
		auto res = g_map[vs.size()].insert(std::make_pair(s, Nword(vs, v)));
		map_word = res.first;
		//g_map[s] =  (Nword(vs, v));
	}
	else {
		map_word->second.m_count++;
	}
	return (*map_word).second;
}

void Nword::CalValue()
{
	for (int i = 2; i < 6;i++) {
		unordered_map<string, Nword>& map = g_map[i];
		double onesize = g_map[1].size();

		for (auto & elems : map) {
			double inner_value = 1;
			double min_count = 1 << 30;
			elems.second.m_Value = 0;
			for (auto& substring : elems.second.m_SubWord) {
				Nword& sub = g_map[1].find(substring)->second;
				elems.second.m_Value += sub.m_Value;
				min_count = min_count < sub.m_count ? min_count : sub.m_count;
				inner_value *= sub.m_count;
			}
			inner_value = pow(min_count, elems.second.m_SubWord.size()) / inner_value;
			for (auto& substring : elems.second.l_string) {
				Nword& sub = g_map[1].find(substring)->second;
				double p = sub.m_count / onesize;
				elems.second.m_Value += -p * log2(p)*0.2;
			}
			for (auto& substring : elems.second.r_string) {
				Nword& sub = g_map[1].find(substring)->second;
				double p = sub.m_count / onesize;
				elems.second.m_Value += -p * log2(p)*0.2;
			}
			//elems.second.m_Value *= inner_value;
			if (elems.second.l_string.size() <= 2 || elems.second.r_string.size() <= 2) {
				elems.second.m_Value = -1;
			}
			if (!WordMap::instance->isNormal(elems.second.m_SubWord[0]) || !WordMap::instance->isNormal(elems.second.m_SubWord.back()) ){
				elems.second.m_Value = 0;
			}
		}
	}
}

int Nword::GetType()
{
	return m_SubWord.size();
}

Nword::Nword(const vector<std::string>& s, double v):m_SubWord(s),m_Value(v),m_count(1.0)
{
}

void Nword::Log()
{
	vector<vector<Nword>> res(g_map.size());

	for (int i = 0; i < g_map.size();i++) {
		for (auto & elems : g_map[i])
			res[i].push_back(elems.second);
		std::sort(res[i].begin(), res[i].end(), [](const Nword&l, const Nword&r) {
			return l.m_Value !=  r.m_Value? l.m_Value > r.m_Value:l.m_count > r.m_count;
		});
		for (auto & elems: res[i])
		Debug::GetInstance()->LogInfo(elems);// LogInfo(elems);
		Debug::GetInstance()->LogInfo("*******************************************************************************************************************");// LogInfo(elems);

	}
}

ostream & operator<<(ostream & output, const Nword & w)
{
	if (w.m_count < 2 || w.m_Value <= 0)return output;
	for (auto& elems : w.m_SubWord) {
		output << elems;
	}
	output << " "<< w.m_count << " " << w.m_Value;
	output << std::endl;
	return output;
}
