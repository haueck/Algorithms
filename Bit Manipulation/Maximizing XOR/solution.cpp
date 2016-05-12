/*
 * HackerRank - Maximizing XOR
 * Bit Manipulation
 * https://www.hackerrank.com/challenges/maximizing-xor
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int L, R;
    std::cin >> L >> R;
    int v = L ^ R;
    int e = v ? 1 : 0;
    while (v >>= 1)
    {
        ++e;
    }
    LOG((1 << e) - 1);
    return 0;
}

