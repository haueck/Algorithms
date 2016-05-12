/*
 * HackerRank - Lonely Integer
 * Bit Manipulation
 * https://www.hackerrank.com/challenges/lonely-integer
 * Author: Rafal Kozik
 */

#include <iostream>
#include <bitset>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    std::bitset<101> index;
    for (int i = 0; i < N; ++i)
    {
        int x;
        std::cin >> x;
        index.flip(x);
    }
    for (int i = 0; i < 101; ++i)
    {
        if (index.test(i))
        {
            LOG(i);
            return 0;
        }
    }
    return 0;
}

