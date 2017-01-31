/*
 * HackerRank - Introduction to Nim Game
 * https://www.hackerrank.com/challenges/nim-game-1
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int G;
    std::cin >> G;
    for (int g = 0; g < G; ++g)
    {
        int n;
        std::cin >> n;
        uint32_t result = 0;
        for (int i = 0; i < n; ++i)
        {
            uint32_t pile;
            std::cin >> pile;
            result ^= pile;
        }
        LOG((result == 0 ? "Second" : "First"));
    }
    return 0;
}

