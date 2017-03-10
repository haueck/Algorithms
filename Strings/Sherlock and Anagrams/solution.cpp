/*
 * HackerRank - Sherlock and Anagrams
 * https://www.hackerrank.com/challenges/sherlock-and-anagrams
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int anagrams = 0;
        std::string string;
        std::cin >> string;
        std::vector<std::vector<char>> data(string.size(), std::vector<char>('z' - 'a' + 1));
        for (auto length = 1u; length < string.size(); ++length)
        {
            int size = string.size() - length + 1;
            for (int i = 0; i < size; ++i)
            {
                data[i][string[i + length - 1] - 'a']++;
            }
            for (int i = 0; i < size; ++i)
            {
                for (int j = i + 1; j < size; ++j)
                {
                    ++anagrams;
                    for (int k = 0; k < 'z' - 'a' + 1; ++k)
                    {
                        if (data[i][k] != data[j][k])
                        {
                            --anagrams;
                            break;
                        }
                    }
                }
            }
        }
        LOG(anagrams);
    }
}

