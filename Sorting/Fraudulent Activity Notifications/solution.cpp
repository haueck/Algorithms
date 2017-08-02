/*
 * HackerRank - Fraudulent Activity Notifications
 * https://www.hackerrank.com/challenges/fraudulent-activity-notifications
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

const float epsilon{0.0001};

double calculate_median(std::vector<std::pair<int,int>>& lower, std::vector<std::pair<int,int>>& greater, int lower_count, int greater_count, int d)
{
    if (lower_count + greater_count < d)
    {
        if (greater_count > 0)
        {
            return greater[0].first;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (d & 1)
        {
            return greater[0].first;
        }
        else
        {
            return static_cast<double>(lower[0].first + greater[0].first) / 2.0;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    int n, d;
    std::cin >> n >> d;
    std::vector<std::pair<int,int>> lower, greater;
    int lower_count = 0;
    int greater_count = 0;
    int notifications = 0;
    std::vector<bool> is_lower(n);
    for (int i = 0; i < n; ++i)
    {
        int value;
        std::cin >> value;
        int outdated = i - d;
        auto median = calculate_median(lower, greater, lower_count, greater_count, d);
        if (lower_count + greater_count == d && !(value < 2.0 * (median - epsilon)))
        {
            ++notifications;
        }
        if (outdated >= 0)
        {
            if (is_lower[outdated])
            {
                --lower_count;
            }
            else
            {
                --greater_count;
            }
        }
        if (value < median - epsilon)
        {
            is_lower[i] = true;
            lower.emplace_back(value, i);
            std::push_heap(lower.begin(), lower.end());
            if (lower_count < d / 2)
            {
                ++lower_count;
            }
            else
            {
                std::pop_heap(lower.begin(), lower.end());
                auto largest = lower.back();
                lower.pop_back();
                greater.push_back(largest);
                std::push_heap(greater.begin(), greater.end(), std::greater<std::pair<int,int>>());
                greater_count++;
                is_lower[largest.second] = false;
            }
        }
        else
        {
            is_lower[i] = false;
            greater.emplace_back(value, i);
            std::push_heap(greater.begin(), greater.end(), std::greater<std::pair<int,int>>());
            if (greater_count < static_cast<int>(0.9 + d / 2.0))
            {
                ++greater_count;
            }
            else
            {
                std::pop_heap(greater.begin(), greater.end(), std::greater<std::pair<int,int>>());
                auto smallest = greater.back();
                greater.pop_back();
                lower.push_back(smallest);
                std::push_heap(lower.begin(), lower.end());
                lower_count++;
                is_lower[smallest.second] = true;
            }
        }
        while (lower.size() > 0 && lower[0].second <= outdated)
        {
            std::pop_heap(lower.begin(), lower.end());
            lower.pop_back();
        }
        while (greater.size() > 0 && greater[0].second <= outdated)
        {
            std::pop_heap(greater.begin(), greater.end(), std::greater<std::pair<int,int>>());
            greater.pop_back();
        }
    }
    LOG(notifications);
}

