/*
 * HackerRank - Sam and Sub-strings
 * https://www.hackerrank.com/challenges/sam-and-substrings
 * Author: Rafal Kozik
 */

#include <iostream>
#include <string>

const int64_t mod = 1000000007;

int main()
{
    std::string balls;
    std::cin >> balls;
    int64_t previous = balls[0] - '0';
    int64_t result = previous;
    for (auto i = 1u; i < balls.size(); ++i)
    {
        auto current = (10ll * previous) % mod;
        current = (current + (i + 1) * (balls[i] - '0')) % mod;
        result = (result + current) % mod;
        previous = current;
    }
    std::cout << result << std::endl;
}

