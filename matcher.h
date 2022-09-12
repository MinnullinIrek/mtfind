#pragma once
#include <string>
#include <list>


class Matcher
{
public:
	Matcher(const std::string& mask);
	~Matcher();

	int checkMatch(std::string&& line);

private:
	std::string converterToRegex(std::string& mask);

	std::string m_mask;

};