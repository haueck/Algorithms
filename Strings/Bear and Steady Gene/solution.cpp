/*
 * HackerRank - Bear and Steady Gene
 * https://www.hackerrank.com/challenges/bear-and-steady-gene
 * Author: Rafal Kozik
 */

#include <cmath>
#include <vector>
#include <limits>
#include <iostream>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n;
    std::string dna;
    std::unordered_map<char,int> count{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
    std::unordered_map<char,std::vector<int>> index;
    std::cin >> n >> dna;
    for (auto c : dna)
    {
        ++count[c];
    }

    for (auto c : {'A', 'C', 'G', 'T'})
    {
        int excessive = std::max(0, count[c] - n / 4);
        if (excessive > 0)
        {
            index.emplace(c, std::vector<int>(n, std::numeric_limits<int>::max()));
            int current = 0;
            int end = 0;
            while (true)
            {
                while (end < n && excessive > 0)
                {
                    if (dna[end] == c)
                    {
                        --excessive;
                    }
                    ++end;
                }
                if (excessive == 0)
                {
                    index[c][current] = end - current;
                    if (dna[current] == c)
                    {
                        ++excessive;
                    }
                    ++current;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            index.emplace(c, std::vector<int>(n));
        }
    }

    int min = std::numeric_limits<int>::max();
    for (int i = 0; i < n; ++i)
    {
        min = std::min(min, std::max(index['A'][i], std::max(index['C'][i], std::max(index['G'][i], index['T'][i]))));
    }
    LOG(min);
}

