/*
 * HackerRank - What Are the Odds?
 * https://www.hackerrank.com/contests/hourrank-19/challenges/what-are-the-odds
 * Author: Rafal Kozik
 */

#include <vector>
#include <unordered_map>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<int> s(n + 1);
    std::unordered_map<uint32_t,std::vector<int>> idx;
    idx[0].push_back(0);
    uint32_t x = 0;
    for (int i = 1; i < n + 1; i++)
    {
        std::cin >> s[i - 1];
        x ^= s[i - 1];
        idx[x].push_back(i);
    }
    x = 0;
    uint64_t result = 0;
    for (int i = n; i > 0; --i)
    {
        x ^= s[i];
        auto& c = idx[x];
        auto it = std::lower_bound(c.begin(), c.end(), i);
        result += std::distance(c.begin(), it);
    }
    LOG(result);
}

