/*
 * HackerRank - Modular Game of Numbers
 * https://www.hackerrank.com/contests/101hack47/challenges/modular-game-of-numbers
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl

int main()
{
    std::ios::sync_with_stdio(false);
    int n, p, q;
    std::cin >> n >> p >> q;
    std::vector<int> a(p);
    for(int i = 0; i < p; i++)
    {
       std::cin >> a[i];
    }
    std::vector<int> b(q);
    for(int i = 0; i < q; i++)
    {
       std::cin >> b[i];
    }
    std::vector<int> freq(n);
    int global_lost = std::numeric_limits<int>::max();
    int result = 0;
    for (int i = 0; i < p; ++i)
    {
        for (int j = 0; j < q; ++j)
        {
            freq[(a[i] + b[j]) % n]++;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int lost = 0;
        for (int j = 0; j < n; ++j)
        {
            if ((j + i) % n == 0)
            {
                lost += freq[j];
                if (lost >= global_lost)
                {
                    break;
                }
            }
        }
        if (lost < global_lost)
        {
            global_lost = lost;
            result = i;
        }
    }
    LOG(result);
}

