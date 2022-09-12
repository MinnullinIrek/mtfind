#include "Searcher.h"

#define C_ALL(X) cbegin(X), cend(X)

Searcher::Searcher(const std::string& regMask, std::function<std::pair<std::string, int>()> getNext):
	m_getNext(getNext),
	m_regmask(regMask),
	m_regex(regMask)
{

}

Searcher::~Searcher()
{
}

std::vector<std::tuple<int, int, std::string>> Searcher::getResult()
{
	return m_result;
}

void Searcher::pushResult(int lineCount, int pos, const std::string& text)
{
	std::lock_guard g(m_mutex);
	m_result.push_back({ lineCount, pos, text });
}

void Searcher::search(int thr)
{
	auto pair  = m_getNext();
	
	while (pair.second >= 0)
	{
		auto line = pair.first;
		auto lineCount =	pair.second;

		std::smatch m;


		std::regex_search(line, m, m_regex);

		const std::vector<std::smatch> matches{
			std::sregex_iterator{C_ALL(line), m_regex},
			std::sregex_iterator{}
		};

		for (auto& match : matches)
		{
			auto str = match.str(0);
			auto pos = line.find(str);
			pushResult(lineCount, pos, str);
		}

		pair = m_getNext();

	}
}
