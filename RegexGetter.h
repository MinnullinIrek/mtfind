#pragma once

#include <string>

class RegexGetter
{
public:
	RegexGetter(const std::string& spec);
	~RegexGetter();

	std::string getRegex(std::string mask);

private:
	std::string m_specSimbols;
};

