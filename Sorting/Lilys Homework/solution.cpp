/*
 * HackerRank - Lily's Homework
 * https://www.hackerrank.com/challenges/lilys-homework
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int calculate_swaps(std::vector<std::pair<int,int>>& sorted, std::vector<std::pair<int,int>> data)
{
    int count = 0;
    int n = sorted.size();
    std::vector<int> index(n);
    for (int i = 0; i < n; ++i)
    {
        index[sorted[i].second] = i;
    }
    for (int i = 0; i < n; ++i)
    {
        if (sorted[i].second != i)
        {
            ++count;
            std::swap(data[sorted[i].second], data[i]);
            std::swap(index[sorted[i].second], index[i]);
            sorted[index[sorted[i].second]].second = sorted[i].second;
        }
    }
    return count;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::pair<int,int>> data(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data[i].first;
        data[i].second = i;
    }
    auto sorted1 = data;
    auto sorted2 = data;
    std::sort(sorted1.begin(), sorted1.end());
    std::sort(sorted2.begin(), sorted2.end(), std::greater<std::pair<int,int>>());
    auto count1 = calculate_swaps(sorted1, data);
    auto count2 = calculate_swaps(sorted2, data);
    LOG(std::min(count1, count2));
}

