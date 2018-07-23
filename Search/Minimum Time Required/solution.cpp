/*
 * Minimum Time Required
 * https://www.hackerrank.com/challenges/minimum-time-required/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

bool is_order_complete(std::vector<int>& machines, int64_t days, int64_t goal)
{
    int64_t products = 0;
    for (auto m : machines)
    {
       products += days / m;
       if (products >= goal)
       {
           return true;
       }
    }
    return false;
}

int64_t binary_search(std::vector<int>& machines, int64_t left, int64_t right, int64_t goal)
{
    if (right > left)
    {
        int64_t mid = (left + right) / 2;
        if (is_order_complete(machines, mid, goal))
        {
            return binary_search(machines, left, mid, goal);
        }
        else
        {
            return binary_search(machines, mid + 1, right, goal);
        }
    }
    return left;
}

int main()
{
    int n, goal;
    std::cin >> n >> goal;
    std::vector<int> machines(n);
    for (auto& m : machines)
    {
        std::cin >> m;
    }
    LOG(binary_search(machines, 1, 1e18, goal));
}
