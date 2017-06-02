/*
 * HackerRank - The Great XOR
 * https://www.hackerrank.com/challenges/the-great-xor
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

std::vector<int> find_zeros(long v)
{
    int count = 1;
    std::vector<int> result;
    while (v)
    {
        if (!(v & 1))
        {
            result.push_back(count);
        }
        v >>= 1;
        count++;
    }
    return result;
}

int main()
{
    int q;
    std::cin >> q;
    while (q--)
    {
        long x, result = 0;
        std::cin >> x;
        auto positions_of_zeros = find_zeros(x);
        for (auto position : positions_of_zeros)
        {
            result += 1l << (position - 1);
        }
        LOG(result);
    }
}

