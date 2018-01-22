/*
 * HakcerRank - Nikita and the Game
 * https://www.hackerrank.com/challenges/array-splitting/problem
 * Author: Rafal Kozik
 */

#include <algorithm>
#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int find_max_score(std::vector<uint64_t>& data, int begin, int end)
{
    if (end - begin < 2)
    {
        return 0;
    }
    auto sum = data[end] - data[begin];
    if (sum & 1)
    {
        return 0;
    }
    auto half = data[begin] + sum / 2;
    auto begin_it = data.begin() + begin + 1;
    auto end_it = data.begin() + end + 1;
    auto found = std::lower_bound(begin_it, end_it, half);
    if (*found != half)
    {
        return 0;
    }
    auto split = found - data.begin();
    auto left = find_max_score(data, begin, split);
    auto right = find_max_score(data, split, end);
    return 1 + std::max(left, right);
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::cin >> N;
        std::vector<uint64_t> data(N + 1);
        for (int i = 0; i < N; ++i)
        {
            int value;
            std::cin >> value;
            data[i + 1] = data[i] + value;
        }
        auto score = find_max_score(data, 0, N);
        LOG(score);
    }
}

