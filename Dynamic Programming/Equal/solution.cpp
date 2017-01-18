/*
 * HackerRank - Equal
 * https://www.hackerrank.com/challenges/equal
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

int minimum(int n, std::vector<int>& cache)
{
    if (n < 0)
    {
        return std::numeric_limits<int>::max();
    }
    if (cache.at(n) == std::numeric_limits<int>::max())
    {
        auto min = std::numeric_limits<int>::max();
        for (auto c : { 1, 2, 5 })
        {
            auto local_min = minimum(n - c, cache);
            if (local_min < min)
            {
                min = local_min;
            }
        }
        cache[n] = 1 + min;
    }
    return cache[n];
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    std::vector<int> cache(1000, std::numeric_limits<int>::max());
    cache[0] = 0;
    for (int t = 0; t < T; ++t)
    {
        int N, min = std::numeric_limits<int>::max();
        std::cin >> N;
        std::vector<int> cookies(N);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> cookies[i];
            if (cookies[i] < min)
            {
                min = cookies[i];
            }
        }
        int result = std::numeric_limits<int>::max();
        // Instead of giving cookies to all members except one,
        // we can take from one. So we take cookies from members
        // until all of them have the same amount. However, it
        // is possible that we can reach lower amount than minimal
        // in less operations, so we need to check some additional
        // values.
        for (int l = 0; l <= std::min(4, min); ++l)
        {
            int local_result = 0;
            int local_min = min - l;
            for (int i = 0; i < N; ++i)
            {
                local_result += minimum(cookies[i] - local_min, cache);
            }
            result = std::min(result, local_result);
        }
        LOG(result);
    }
    return 0;
}

