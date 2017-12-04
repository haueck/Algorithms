/*
 * HackerRank - Contstruct the Array
 * https://www.hackerrank.com/contests/101hack52/challenges/construct-the-array
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl

int64_t mod(int64_t a)
{
    return ((a + 1000000007) % 1000000007);
}

int main()
{
    int n, k, x;
    std::cin >> n >> k >> x;
    // All possible numbers at index 1
    int64_t count_of_all = k - 1;
    // Number of x at index 1. At index 0 there is always 1,
    // so if x = 1, then there is no x at index 1.
    int64_t count_of_x = x == 1 ? 0 : 1;
    for (int i = 2; i < n - 1; ++i)
    {
        // It is possible to insert x at position i
        // if there was no x at i - 1.
        count_of_x = mod(count_of_all - count_of_x);
        count_of_all = mod(count_of_all * (k - 1));
    }
    // Subtract all arrays that have x at position n - 2
    LOG(mod(count_of_all - count_of_x));
}

