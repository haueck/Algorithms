/*
 * HackerRank - Funny String
 * Strings
 * https://www.hackerrank.com/challenges/funny-string
 * Author: Rafal Kozik
 */

#include <iostream>
#include <cstdlib>
#include <string>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T = 0;
    std::cin >> T;
    std::cin.ignore(1, '\n');
    for (int t = 0; t < T; ++t)
    {
        bool funny = true;
        std::string string;
        std::getline(std::cin, string);
        auto size = string.size();
        for (uint32_t i = 1; i < size; ++i)
        {
            auto v1 = std::abs(static_cast<int>(string[i]) - static_cast<int>(string[i - 1]));
            auto v2 = std::abs(static_cast<int>(string[size - 1 - i]) - static_cast<int>(string[size - i]));
            if (v1 != v2)
            {
                funny = false;
                break;
            }
        }
        LOG((funny ? "Funny" : "Not Funny"));
    }
    return 0;
}
