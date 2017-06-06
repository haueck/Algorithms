/*
 * Game Of Throne - II
 * https://www.hackerrank.com/challenges/game-of-throne-ii
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <string>

#define LOG(x) std::cout << x << std::endl

const int modulo = 1000000007;

int64_t extended_euclidean_algorithm(int64_t a, int64_t b, int64_t& x, int64_t& y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    int64_t x1, y1;
    auto gcd = extended_euclidean_algorithm(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int modular_multiplicative_inverse(int64_t a)
{
    int64_t x, y;
    extended_euclidean_algorithm(a, modulo, x, y);
    return x < 0 ? x + modulo : x;
}

int64_t factorial(int n)
{
    int64_t result = 1;
    while (n > 0)
    {
        result = (result * n) % modulo;
        n--;
    }
    return result;
}

int main()
{
    std::string s;
    std::cin >> s;
    std::vector<int> freq('z' - 'a' + 1);
    for (auto c : s)
    {
        ++freq[c - 'a'];
    }
    int one_side_count = 0;
    int64_t permutations = 1;
    for (auto c : freq)
    {
        int one_side_freq = c / 2;
        one_side_count += one_side_freq;
        permutations = (permutations * modular_multiplicative_inverse(factorial(one_side_freq))) % modulo;
    }
    permutations = (permutations * factorial(one_side_count)) % modulo;
    LOG(permutations);
}
