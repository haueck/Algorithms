/*
 * HackerRank - Two Robots
 * https://www.hackerrank.com/challenges/two-robots/problem
 * Author: Rafal Kozik
 */

#include <cmath>
#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

int64_t minimum_distance(std::vector<std::pair<int,int>>& queries, uint32_t q, int r1, int r2, std::vector<std::vector<int64_t>>& dp)
{
    if (q == queries.size())
    {
        return 0;
    }
    if (dp[q][r2] == -1)
    {
        auto dist1 = r1 == 0 ? 0 : std::abs(r1 - queries[q].first);
        auto dist2 = r2 == 0 ? 0 : std::abs(r2 - queries[q].first);
        auto option1 = dist1 + minimum_distance(queries, q + 1, queries[q].second, r2, dp);
        auto option2 = dist2 + minimum_distance(queries, q + 1, queries[q].second, r1, dp);
        dp[q][r2] = std::abs(queries[q].first - queries[q].second) + std::min(option1, option2);
    }
    return dp[q][r2];
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int M, N;
        std::cin >> M >> N;
        std::vector<std::pair<int,int>> queries(N);
        std::vector<std::vector<int64_t>> dp(N, std::vector<int64_t>(M + 1, -1));
        for (int i = 0; i < N; ++i)
        {
            std::cin >> queries[i].first >> queries[i].second;
        }
        auto result = minimum_distance(queries, 0, 0, 0, dp);
        LOG(result);
    }
}

