/*
 * Maximum Palindromes
 * https://www.hackerrank.com/challenges/maximum-palindromes/problem
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

const int MOD = 1e9 + 7;

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

auto modular_multiplicative_inverse(int64_t a)
{
    int64_t x, y;
    extended_euclidean_algorithm(a, MOD, x, y);
    return x < 0 ? x + MOD: x;
}

auto precompute_factorials()
{
    auto size = 50001;
    std::vector<int64_t> factorials(size, 1);
    for (auto i = 2; i < size; ++i)
    {
        factorials[i] = (factorials[i - 1] * i) % MOD;
    }
    return factorials;
}

int main()
{
    auto factorials = precompute_factorials();
    std::string word;
    std::cin >> word;
    std::vector<std::vector<int>> sums(1, std::vector<int>('z' - 'a' + 1));
    for (auto i = 0u; i < word.size(); ++i)
    {
        sums.push_back(sums.back());
        sums.back()[word[i] - 'a']++;
    }
    int q;
    std::cin >> q;
    while (q--)
    {
        int l, r;
        std::cin >> l >> r;
        auto total = 0;
        auto singles = 0;
        int64_t denominator = 1;
        for (auto i = 0u; i < sums[l].size(); ++i)
        {
            auto count = sums[r][i] - sums[l - 1][i];
            int pairs = count / 2;
            singles += count % 2;
            total += pairs;
            denominator = (denominator * factorials[pairs]) % MOD;
        }
        // Permutations with repetition
        auto permutations = (factorials[total] * modular_multiplicative_inverse(denominator)) % MOD;
        if (singles > 0)
        {
            permutations = (permutations * singles) % MOD;
        }
        LOG(permutations);
    }
}


