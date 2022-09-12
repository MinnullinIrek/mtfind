// otipacros.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <future>
#include <filesystem>
#include <fstream>

#include "RegexGetter.h"
#include "Searcher.h"

void printResult(const std::vector<std::tuple<int, int, std::string>>& result );

int main(int argc, char** argv)
{
 
    if (argc < 3) {
        std::cerr << "Incorrect number of arguments" << std::endl;
        return 1;
    }

    std::string infilename{ argv[1]};

    std::ifstream infile(infilename);
    if (!infile.is_open()) {
        std::cerr << "Can't open file for reading: " << infilename << std::endl;
        return 1;
    }

    RegexGetter rGetter({ '.', '[', ']', '{', '}' });
    auto sRegex = rGetter.getRegex(argv[2]);
    int i = 0;
    std::mutex mutexFile;

    auto getNext = [&i, &infile, &mutexFile]()->std::pair<std::string, int> 
    { 
        if (infile.eof())
        {
            return { "", -1 };
        }
        else
        {
            std::lock_guard guard(mutexFile);
            std::string line;
            std::getline(infile, line);
            return { line, ++i }; 
        }

    };

    Searcher searcher(sRegex, getNext);

    auto threadCounts = std::thread::hardware_concurrency();

    std::vector<std::future<void>> futures;

    for (int i = 0; i < threadCounts - 1; ++i)
    {
        futures.push_back(std::async(std::launch::async, [&searcher, i]() {searcher.search(i); }));
    }

    std::for_each(std::begin(futures), std::end(futures), [](auto& fut) {fut.get(); });

    auto res = searcher.getResult();

    printResult(res);


    return 0;

}

void printResult(const std::vector<std::tuple<int, int, std::string>>& result)
{
    std::for_each(std::begin(result), std::end(result),
        [](auto& res) {
            std::cout << std::get<0>(res) << " " << std::get<1>(res) << " " << std::get<2>(res) << std::endl;
        }
        );
}
