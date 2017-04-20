/*
 * HackerRank - Minimum Loss
 * https://www.hackerrank.com/challenges/minimum-loss
 * Author: Rafal Kozik
 */

#include <cmath>
#include <stack>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::pair<uint64_t,uint64_t>> data(n);
    std::stack<std::pair<uint64_t,uint64_t>> stack;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data[i].first;
        data[i].second = i;
    }
    std::sort(data.begin(), data.end(), std::greater<std::pair<uint64_t,uint64_t>>());
    for (int i = 0; i < n; ++i)
    {
        while (stack.size() > 0 && stack.top().second < data[i].second)
        {
            data[stack.top().first].second = i;
            stack.pop();
        }
        stack.emplace(i, data[i].second);
        data[i].second = 0;
    }
    uint64_t result = std::numeric_limits<uint64_t>::max();
    for (int i = 0; i < n; ++i)
    {
        if (data[i].second > 0)
        {
            result = std::min(result, data[i].first - data[data[i].second].first);
        }
    }
    std::cout << result << std::endl;
}

