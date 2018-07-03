/*
 * HackerRank - Tower Construction
 * https://www.hackerrank.com/contests/101hack55/challenges/tower-construction
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <map>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> xs(n);
    std::map<int,int> min, max;
    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    for (int i = 0; i < n; ++i)
    {
        std::cin >> xs[i];
        min_x = std::min(min_x, xs[i]);
        max_x = std::max(max_x, xs[i]);
        min[xs[i]] = std::numeric_limits<int>::max();
        max[xs[i]] = std::numeric_limits<int>::min();
    }
    for (int i = 0; i < n; ++i)
    {
        int y;
        std::cin >> y;
        min[xs[i]] = std::min(min[xs[i]], y);
        max[xs[i]] = std::max(max[xs[i]], y);
    }
    int size = max_x - min_x + 1;
    std::vector<int> l2r_min(size), l2r_max(size), r2l_min(size), r2l_max(size);
    l2r_min[0] = min[min_x];
    l2r_max[0] = max[min_x];
    r2l_min[0] = min[max_x];
    r2l_max[0] = max[max_x];
    for (auto i = 1; i < size; ++i)
    {
        l2r_min[i] = std::min(min[min_x + i], l2r_min[i - 1]);
        l2r_max[i] = std::max(max[min_x + i], l2r_max[i - 1]);
        r2l_min[i] = std::min(min[max_x - i], r2l_min[i - 1]);
        r2l_max[i] = std::max(max[max_x - i], r2l_max[i - 1]);
    }
    std::vector<int> outline_min(size), outline_max(size);
    for (auto i = 0; i < size; ++i)
    {
        outline_min[i] = std::max(l2r_min[i], r2l_min[size - 1 - i]);
        outline_max[i] = std::min(l2r_max[i], r2l_max[size - 1 - i]);
    }
    int64_t total_area = 0;
    for (auto i = 0; i < size; ++i)
    {
        total_area += outline_max[i] - outline_min[i] + 1;
    }
    LOG(total_area - n);
}

