/*
 * Decibinary numbers
 * https://www.hackerrank.com/challenges/decibinary-numbers/problem
 * Author: Rafal Kozik
 */

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

const int P = 19;

int64_t powers_of_ten[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000,
    100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000,
    10000000000000000, 100000000000000000, 1000000000000000000
};

int db_to_dec(int64_t decibinary)
{
    int value = 0;
    int exp = 0;
    while (decibinary > 0)
    {
        value += (decibinary % 10) * (1 << exp);
        exp++;
        decibinary /= 10;
    }
    return value;
}

/*
 * Returns a table dp[i][j] with the numbers of decibinary numbers
 * that are equal to a decimal i and have at most j digits
 */
auto precompute()
{
    auto size = db_to_dec(powers_of_ten[15] - 1) + 1;
    std::vector<int64_t[P + 1]> result(size);
    for (auto t = 0; t < P; ++t)
    {
        result[0][t] = 1;
        for (auto i = 1; i < 10; ++i)
        {
            int a = i * (1 << t);
            for (auto j = 0; j < size - a; ++j)
            {
                result[a + j][t + 1] += result[j][t];
            }
        }
        // Accumulate
        for (auto j = 0; j < size; ++j)
        {
            result[j][t + 1] += result[j][t];
        }
    }
    return result;
}

auto accumulate(const std::vector<int64_t[P + 1]>& dp)
{
    std::vector<int64_t> accumulated(dp.size());
    accumulated[0] = dp[0][P];
    for (auto i = 1u; i < dp.size(); ++i)
    {
        accumulated[i] = accumulated[i - 1] + dp[i][P];
    }
    return accumulated;
}

int64_t find_decibinary(const std::vector<int64_t[P + 1]>& dp, int decimal, int64_t position, int digits, int start)
{
    if (decimal == 0)
    {
        return 0;
    }
    if (digits == 1)
    {
        return decimal;
    }
    for (int64_t i = start; i < 10; ++i)
    {
        auto new_decimal = decimal - i * (1 << (digits - 1));
        auto count  = dp[new_decimal][digits - 1];
        if (position > count)
        {
            // Skip all numbers that have digit i at the current position
            position = position - count;
        }
        else
        {
            // Digit i must be at the current position, go the next one
            return i * powers_of_ten[digits - 1] + find_decibinary(dp, new_decimal, position, digits - 1, 0);
        }
    }
    throw 110;
}

int main()
{
    int q;
    std::cin >> q;
    auto dp = precompute();
    auto accumulated = accumulate(dp);
    while (q--)
    {
        int64_t position;
        std::cin >> position;
        // Sorting by decimal value - skip all those with lower decimal value
        auto it1 = std::lower_bound(accumulated.begin(), accumulated.end(), position);
        position -= *std::prev(it1);
        auto decimal = it1 - accumulated.begin();
        // Sorting by decibinary value - skip all those having too few digits
        auto it2 = std::lower_bound(std::begin(dp[decimal]), std::end(dp[decimal]), position);
        position -= *std::prev(it2);
        auto digits = it2 - std::begin(dp[decimal]);
        // Find a number that is equal to the given decimal number and has the given number of digits
        auto result = find_decibinary(dp, decimal, position, digits, 1);
        LOG(result);
    }
}

