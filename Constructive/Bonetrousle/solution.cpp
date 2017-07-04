/*
 * HackerRank - Bonetrousle
 * https://www.hackerrank.com/challenges/bonetrousle
 * Author: Rafal Kozik
 */

#include <limits>
#include <iostream>

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int64_t n, k, b, max_sticks;
        std::cin >> n >> k >> b;
        if (b < std::numeric_limits<int64_t>::max() / (2 * k - b))
        {
            max_sticks = (b * ((k - b + 1) + k)) / 2;
        }
        else
        {
            max_sticks = std::numeric_limits<int64_t>::max();
        }
        int64_t min_sticks = (b * (1 + b)) / 2;
        if (n < min_sticks || n > max_sticks)
        {
            std::cout << -1;
        }
        else
        {
            while (n > min_sticks)
            {
                min_sticks -= b;
                int64_t buy = std::min(k, n - min_sticks);
                k = buy - 1;
                n -= buy;
                b--;
                std::cout << buy << " ";
            }
            for (int i = 1; i <= b; ++i)
            {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }
}

