/*
 * Codeforces - Perfect Number
 * http://codeforces.com/contest/919/problem/B
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl

int calc_sum(int64_t n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main()
{
    int k;
    std::cin >> k;
    int count = 0;
    int found = 0;
    while (found < k)
    {
        ++count;
        auto sum = calc_sum(count);
        if (sum <= 10)
        {
            ++found;
        }
    }
    LOG(count << (10 - calc_sum(count)));
}

