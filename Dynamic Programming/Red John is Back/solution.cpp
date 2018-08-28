/*
 * Red John is Back
 * https://www.hackerrank.com/challenges/red-john-is-back/problem
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

int primes(int n)
{
    std::vector<bool> sieve(n + 1, true);
    for (auto i = 2l; i < n + 1; ++i)
    {
        if (sieve[i])
        {
            for (auto j = i * i; j < n + 1; j += i)
            {
                sieve[j] = false;
            }
        }
    }
    int count = 0;
    for (auto i = 2; i < n + 1; ++i)
    {
        if (sieve[i])
        {
            ++count;
        }
    }
    return count;
}

int calc_walls(int n, std::vector<int>& dp)
{
    if (n < 4)
    {
        return 1;
    }
    if (dp[n] == 0)
    {
        dp[n] = 1;
        for (auto left = 0; left <= n - 4; ++left)
        {
            auto r = calc_walls(n - 4 - left, dp);
            dp[n] += r;
        }
    }
    return dp[n];
}

int main()
{
    int t;
    std::cin >> t;
    std::vector<int> dp(41);
    while (t--)
    {
        int n;
        std::cin >> n;
        auto walls = calc_walls(n, dp);
        LOG(primes(walls));
    }
}

