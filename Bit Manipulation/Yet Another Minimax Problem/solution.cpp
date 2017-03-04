/*
 * HackerRank - Yet Another Minimax Problem
 * https://www.hackerrank.com/challenges/yet-another-minimax-problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

int msb(int a)
{
    int position = 0;
    while (a > 0)
    {
        ++position;
        a >>= 1;
    }
    return position;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int N, max = 0;
    std::cin >> N;
    std::vector<int> data(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> data[i];
        max = std::max(max, data[i]);
    }
    int shift = msb(max) - 1;
	// Find the most significant bit that is not
    // the same in all values. The maximal value
    // will be for a1 ^ a2 where a1 and a2 have
    // this bit different.
    while (shift >= 0)
    {
        int zeros = 0;
        int ones = 0;
        for (auto a : data)
        {
           (a & (1 << shift)) ? ++ones : ++zeros;
        }
        if (zeros > 0 && ones > 0)
        {
            break;
        }
        --shift;
    }
    if (shift < 0)
    {
        LOG(0);
    }
    else
    {
        auto split = std::partition(data.begin(), data.end(), [shift](int v) { return v & (1 << shift); });
        int min = std::numeric_limits<int>::max();
        for (auto it1 = data.begin(); it1 < split; ++it1)
        {
            for (auto it2 = split; it2 < data.end(); ++it2)
            {
                min = std::min(min, *it2 ^ *it1);
            }
        }
        LOG(min);
    }
}

