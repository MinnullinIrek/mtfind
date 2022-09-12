#include "RegexGetter.h"
#include <algorithm>
#include <sstream>

RegexGetter::RegexGetter(const std::string& spec):
    m_specSimbols(spec)
{
}

RegexGetter::~RegexGetter()
{
}

std::string RegexGetter::getRegex(std::string mask)
{
    size_t pos = 0;
    std::string reg;
    std::stringstream ss;
    std::for_each(std::begin(mask), std::end(mask), 
        [this, &ss](auto& symb) 
            {
                if (m_specSimbols.find(symb) != std::string::npos)
                {
                    ss << '['  << symb << ']';

                }
                else if (symb == '?')
                {
                    ss << ".{1}";
                }
                else
                {
                    ss << symb;
                }            


            });

	return ss.str();
}

void ReplaceStringInPlace(std::string& subject, const std::string& search,const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}