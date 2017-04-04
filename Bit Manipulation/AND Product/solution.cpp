/*
 * HackerRank - AND Product
 * https://www.hackerrank.com/challenges/and-product
 * Author: Rafal Kozik
 */

#include <iostream>
#include <bitset>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        uint32_t a, b, result = 0;
        std::cin >> a >> b;
        for (int i = 31; i >= 0; --i)
        {
            uint32_t ai = a & (1u << i);
            uint32_t bi = b & (1u << i);
            if (ai != bi)
            {
                break;
            }
            result |= ai;
        }
        LOG(result);
    }
}
