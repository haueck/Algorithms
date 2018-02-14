/*
 * HackerRank - Prime XOR
 * https://www.hackerrank.com/challenges/prime-xor/problem
 * Author: Rafal Kozik
 */

#include <set>
#include <map>
#include <cmath>
#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

const int MOD = 1e9 + 7;

int64_t count(std::vector<std::pair<int,int>>& numbers, std::vector<std::vector<int64_t>>& dp, std::set<int>& primes, uint32_t current, int value)
{
    if (current == numbers.size())
    {
        return primes.find(value) == primes.end() ? 0 : 1;
    }
    if (dp[current][value] == -1)
    {
        int64_t ways_to_include = (numbers[current].second + 1) / 2;
        int64_t ways_to_exclude = numbers[current].second / 2 + 1;
        dp[current][value] = (count(numbers, dp, primes, current + 1, value) * ways_to_exclude) % MOD;
        dp[current][value] = (dp[current][value] + (count(numbers, dp, primes, current + 1, value ^ numbers[current].first) * ways_to_include) % MOD) % MOD;
    }
    return dp[current][value];
}

int main()
{
    int q;
    std::cin >> q;
    std::set<int> primes;
    primes.insert(2);
    for (int i = 3; i < (1 << 13); i = i + 2)
    {
        bool prime = true;
        int sqrt = std::sqrt(i);
        for (int j = 3; j <= sqrt; ++j)
        {
            if (i % j == 0)
            {
                prime = false;
                break;
            }
        }
        if (prime)
        {
            primes.insert(i);
        }
    }
    while (q--)
    {
        int n;
        std::cin >> n;
        std::map<int,int> frequencies;
        for (int i = 0; i < n; ++i)
        {
            int value;
            std::cin >> value;
            frequencies[value]++;
        }
        std::vector<std::pair<int,int>> numbers(frequencies.begin(), frequencies.end());
        std::vector<std::vector<int64_t>> dp(1001, std::vector<int64_t>(1 << 13, -1));
        std::cout << count(numbers, dp, primes, 0, 0) << std::endl;
    }
}

