#pragma once

#include <string>
#include <functional>
#include <vector>
#include <tuple>
#include <regex>
#include <mutex>


class Searcher
{
public :
	Searcher(const std::string& regMask, std::function<std::pair<std::string, int>()> getNext);
	~Searcher();

	std::vector<std::tuple<int, int, std::string>> getResult();
	void search(int thr);

private:
	void pushResult(int linecount, int pos, const std::string& text);
	std::function<std::pair<std::string, int>()> m_getNext;
	std::string m_regmask;
	std::vector<std::tuple<int, int, std::string>> m_result;
	std::regex m_regex;
	std::mutex m_mutex;
};

