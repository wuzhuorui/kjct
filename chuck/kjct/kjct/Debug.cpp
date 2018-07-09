#include "Debug.h"
shared_ptr<Debug> Debug::GetInstance()
{
	static shared_ptr<Debug> instance(new Debug);
	return instance;
}

void Debug::LogInfo(std::string s)
{
	output << s;
}

void Debug::LogInfo(const Document & d)
{
	output << d;

}

void Debug::LogInfo(const Nword & d)
{
	output << d;
}
