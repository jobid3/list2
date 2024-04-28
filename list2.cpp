#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>

std::vector<std::string> line_to_vector( std::string line)
{
    std::stringstream ss(line);
    std::vector<std::string> words;
    std::string word;

    while(std::getline(ss, word, ' '))
    {
        words.push_back(word);
    }
    return words;
}


std::vector<std::vector<std::string>> generate_combinations(std::vector<std::string> items)
{
    std::vector<std::vector<std::string>> combinations;
    int n = items.size();
    for (int i = 1; i < (1 << n); ++i) {
        std::vector<std::string> combination;
        for (unsigned int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                combination.push_back(items[j]);
            }
        }
        combinations.push_back(combination);
    }
    return combinations;
}

int main()
{
    std::vector<std::vector<std::string>> list;
    std::fstream file;
    file.open("list.txt");
    std::string line;
    std::map<std::vector<std::string>, int> combinationCounts;
    std::map<std::string, int> products;

    while(std::getline(file, line))
    {
        list.push_back(line_to_vector(line));
    }

    for(int j = 0; j < list.size(); j++)
    {
        for(int i = 0; i < list[j].size(); i++)
        {
            products[list[j][i]] += 1;
        }
    }

    for(int i = 0; i < list.size(); i++)
    {
        std::vector<std::vector<std::string>> combinations = generate_combinations(list[i]);
        for(int j = 0; j < combinations.size(); j++)
        {
            combinationCounts[combinations[j]]++;
        }
    }

    for(std::map<std::vector<std::string>, int>::iterator it = combinationCounts.begin(); it != combinationCounts.end(); it++)
    {
        std::vector<std::string> combination = it->first;
        float count = it->second;
        float percentage = (count / list.size()) * 100;
        for(int i = 0; i < combination.size(); i++)
        {
            std::cout << combination[i] << " ";
        }
        std::cout << " - " << std::setprecision(2) << percentage << "%" << std::endl;
    }

    return 0;
}