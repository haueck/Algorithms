/*
 * Stone Division, Revisited
 * https://www.hackerrank.com/challenges/stone-division-2/problem
 * Author: Rafal Kozik
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

#define LOG(x) std::cout << x << std::endl

int64_t divide_stones(std::vector<int64_t>& S, uint32_t current, int64_t n, std::vector<int64_t>& dp)
{
    if (dp[current] == -1)
    {
        int64_t max = 0;
        for (auto i = current + 1; i < S.size(); ++i)
        {
            if (S[current] % S[i] == 0)
            {
                max = std::max(max, n / S[current] + divide_stones(S, i, n, dp));
            }
        }
        dp[current] = max;
    }
    return dp[current];
}

int main()
{
    int q;
    std::cin >> q;
    while (q--)
    {
        int64_t n, m;
        std::cin >> n >> m;
        std::set<int64_t,std::greater<int64_t>> unique;
        for (int i = 0; i < m; i++)
        {
            int64_t v;
            std::cin >> v;
            unique.insert(v);
        }
        unique.insert(n);
        std::vector<int64_t> S(unique.begin(), unique.end());
        std::vector<int64_t> dp(S.size(), -1);
        auto iterator = std::lower_bound(S.begin(), S.end(), n, std::greater<int64_t>());
        long result = divide_stones(S, iterator - S.begin(), n, dp);
        LOG(result);
    }
}

