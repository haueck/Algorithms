/*
 * HackerRank - Grid Walking
 * https://www.hackerrank.com/challenges/grid-walking/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

const int64_t MOD = 1e9 + 7;

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
    extended_euclidean_algorithm(a, MOD, x, y);
    return x < 0 ? x + MOD : x;
}

int64_t factorial(int n)
{
    int64_t result = 1;
    while (n > 0)
    {
        result = (result * n) % MOD;
        n--;
    }
    return result;
}

int64_t binomial_coefficient(int n, int k)
{
    auto denominator = (factorial(k) * factorial(n - k)) % MOD;
    return (factorial(n) * modular_multiplicative_inverse(denominator)) % MOD;
}

std::vector<int64_t> paths_in_1d(int size, int position, int steps)
{
    std::vector<int64_t> result(steps + 1);
    std::vector<int64_t> helper(size);
    helper[position - 1] = 1;
    result[0] = 1;
    for (int step = 1; step <= steps; ++step)
    {
        int previous = 0;
        for (int i = 0; i < size - 1; ++i)
        {
            auto current = helper[i];
            helper[i] = (previous + helper[i + 1]) % MOD;
            result[step] = (result[step] + helper[i]) % MOD;
            previous = current;
        }
        helper.back() = previous;
        result[step] = (result[step] + previous) % MOD;
    }
    return result;
}

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int n, m;
        std::cin >> n >> m;
        std::vector<int> x(n), D(n);
        for (auto i = 0; i < n; ++i)
        {
            std::cin >> x[i];
        }
        for (auto i = 0; i < n; ++i)
        {
            std::cin >> D[i];
        }
        // paths[i][j] tells how many paths we get if we make j moves in the i + 1 dimension alone
        std::vector<std::vector<int64_t>> paths;
        for (auto i = 0; i < n; ++i)
        {
            paths.emplace_back(paths_in_1d(D[i], x[i], m));
        }
        // dp[i][j] tells how many paths we get if we make j moves in the first i + 1 dimensions
        std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(m + 1));
        dp[0].swap(paths[0]);
        // This loop iterates over all dimension
        for (auto i = 1; i < n; ++i)
        {
            // This loop iterates over all possible number of moves
            for (auto j = 0; j < m + 1; ++j)
            {
                // Let's say i = 3 (we are adding 4th dimension to dp)
                // and j = 4 (we want to make 4 moves in the first 4 dimensions).
                // It means, that we can make 0, 1, 2, 3 or 4 moves in the 4th dimension
                // and other moves in the dimensions 1-3.
                for (auto k = 0; k <= j; ++k)
                {
                    // Let's say k = 1 (we make 1 move in the dimensions 1-3 and 4 - 1 = 3 moves in 4th dimension).
                    // dp[2][1] tells how many paths there are if make 1 move in dimensions 1-3.
                    // paths[3][3] tells how many paths there are if we make 3 moves in the 4th dimension alone.
                    // binomial_coefficient(4, 1) calculates the number of ways we can make those move,
                    // e.g. first move in 4th dimension, then one in 1-3 and two moves again in 4th.
                    int64_t tmp1 = (binomial_coefficient(j, k) * dp[i - 1][k]) % MOD;
                    int64_t tmp2 = (tmp1 * paths[i][j - k]) % MOD;
                    dp[i][j] = (dp[i][j] + tmp2) % MOD;
                }
            }
        }
        LOG(dp[n-1][m]);
    }
}

