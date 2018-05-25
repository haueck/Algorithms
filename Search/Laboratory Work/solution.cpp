/*
 * Codeforces - Laboratory Work
 * http://codeforces.com/contest/931/problem/C
 * Author: Rafal Kozik
 */

#include <vector>
#include <limits>
#include <iostream>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n;
    std::cin >> n;
    int64_t sum = 0;
    int max = std::numeric_limits<int>::min();
    int min = std::numeric_limits<int>::max();
    std::unordered_map<int,int64_t> map;
    for (int i = 0; i < n; ++i)
    {
        int v;
        std::cin >> v;
        map[v]++;
        min = std::min(min, v);
        max = std::max(max, v);
        sum += v;
    }
    if (max - min == 2)
    {
        int64_t a = min;
        int64_t b = (min + max) / 2;
        int64_t c = max;
        int the_same = std::numeric_limits<int>::max();
        int min_x, min_y, min_z;
        for (int64_t y = 0; y <= n; ++y)
        {
            int64_t x = (sum - n * c - (b - c) * y) / (a - c);
            int64_t z = n - y - x;
            if (x >= 0 && z >= 0 && x * a + b * y + c * z == sum && x + y + z == n)
            {
                auto value = std::min(x, map[a]) + std::min(y, map[b]) + std::min(z, map[c]);
                if (value < the_same)
                {
                    the_same = value;
                    min_x = x;
                    min_y = y;
                    min_z = z;
                }
            }
        }
        LOG(the_same);
        for (auto i = 0; i < min_x; ++i)
        {
            std::cout << a << " ";
        }
        for (auto i = 0; i < min_y; ++i)
        {
            std::cout << b << " ";
        }
        for (auto i = 0; i < min_z; ++i)
        {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    else if (max - min == 1)
    {
        LOG(n);
        for (auto i = 0; i < map[min]; ++i)
        {
            std::cout << min << " ";
        }
        for (auto i = 0; i < map[max]; ++i)
        {
            std::cout << max << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        LOG(n);
        for (auto i = 0; i < n; ++i)
        {
            std::cout << min << " ";
        }
        std::cout << std::endl;
    }
}

