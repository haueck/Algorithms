/*
 * Maximum Subarray Sum
 * https://www.hackerrank.com/challenges/maximum-subarray-sum/problem
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int q;
    std::cin >> q;
    while (q--)
    {
        int64_t n, m;
        std::cin >> n >> m;
        std::set<int64_t> set;
        std::vector<int64_t> agregated(n + 1);
        for (auto i = 0; i < n; ++i)
        {
            int64_t value;
            std::cin >> value;
            agregated[i + 1] = (agregated[i] + value) % m;
        }
        auto result = 0l;
        for (auto a : agregated)
        {
            result = std::max(result, a);
            auto it = set.upper_bound(a);
            if (it != set.end())
            {
                result = std::max(result, (a - *it) + m);
            }
            set.insert(a);
        }
        LOG(result);
    }
}

