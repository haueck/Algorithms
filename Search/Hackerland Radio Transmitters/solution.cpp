/*
 * HackerRank - Hackerland Radio Transmitters
 * Search
 * https://www.hackerrank.com/challenges/hackerland-radio-transmitters
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

int find_furthest_within_reach(std::vector<int>& houses, int current, int k)
{
    uint32_t furthest = current;
    while (furthest + 1 < houses.size() && houses[furthest + 1] - houses[current] <= k)
    {
        ++furthest;
    }
    return furthest;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> houses(n, 0);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> houses[i];
    }
    std::sort(houses.begin(), houses.end());
    int current = 0;
    int result = 0;
    while (current < n)
    {
        int furthest = find_furthest_within_reach(houses, current, k);
        current = 1 + find_furthest_within_reach(houses, furthest, k);
        ++result;
    }
    LOG(result);
    return 0;
}

