/*
 * HackerRank - Sherlock and Cost
 * https://www.hackerrank.com/challenges/sherlock-and-cost
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

uint32_t cost(std::vector<int>& B, size_t i, bool max, int prev, std::vector<std::vector<uint32_t>>& cache)
{
    if (i == B.size())
    {
        return 0;
    }
    auto current = max ? B[i] : 1;
    if (cache[max][i] == std::numeric_limits<uint32_t>::max())
    {
        auto result1 = cost(B, i + 1, true, current, cache);
        auto result2 = cost(B, i + 1, false, current, cache);
        cache[max][i] = std::max(result1, result2);
    }
    return cache[max][i] + std::abs(current - prev);
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int N;
        std::cin >> N;
        std::vector<int> B(N);
        std::vector<std::vector<uint32_t>> cache(2, std::vector<uint32_t>(N, std::numeric_limits<uint32_t>::max()));
        for (int i = 0; i < N; ++i)
        {
            std::cin >> B[i];
        }
        auto result1 = cost(B, 0, true, B[0], cache);
        auto result2 = cost(B, 0, false, 1, cache);
        LOG(std::max(result1, result2));
    }
    return 0;
}

