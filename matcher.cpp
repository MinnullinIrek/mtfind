#include "matcher.h"
#include <regex>

Matcher::Matcher(const std::string& mask):m_mask(mask)
{
}

Matcher::~Matcher()
{
}

int Matcher::checkMatch(std::string&& line)
{
	return 0;
}

std::string Matcher::converterToRegex(std::string& mask)
{
	return std::string();
}
