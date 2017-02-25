/*
 * Misère Nim
 * https://www.hackerrank.com/challenges/misere-nim-1
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        bool nim = false;
        int n, result = 0;
        std::cin >> n;
        for (int i = 0; i < n; ++i)
        {
            int c;
            std::cin >> c;
            result ^= c;
            if (c > 1)
            {
                nim = true;
            }
        }
        if (nim)
        {
            LOG((result == 0 ? "Second" : "First"));
        }
        else
        {
            LOG((n % 2 == 0 ? "First" : "Second"));
        }
    }
    return 0;
}

