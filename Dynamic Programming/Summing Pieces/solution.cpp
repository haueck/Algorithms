/*
 * HackerRank - Summing Pieces
 * https://www.hackerrank.com/challenges/summing-pieces/problem
 * Author: Rafal Kozik
 */

/*
 * A = [1, 2, 3, 4]
 *
 * (1)(2)(3)(4)
 * (1, 2)(3)(4)
 * (1)(2, 3)(4)
 * (1, 2, 3)(4)
 * (1)(2)(3, 4)
 * (1, 2)(3, 4)
 * (1)(2, 3, 4)
 * (1, 2, 3, 4)
 *
 * [0][0] - top-left corner
 */

#include <vector>
#include <iostream>

const int MOD = 1000000007;

int64_t power_of_two(int y)
{
    int64_t result = 1;
    int64_t x = 2;
    while (y > 0)
    {
        if (y & 1)
        {
            result = (result * x) % MOD;
        }
        y = y >> 1;
        x = (x * x) % MOD;
    }
    return result;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int64_t> a(n);
    for (auto i = 0; i < n; ++i)
    {
        std::cin >> a[i];
    }
    std::vector<int64_t> helper(n);
    helper[0] = 1;
    for (auto i = 1ll; i < n; ++i)
    {
        helper[i] = ((helper[i - 1] - i) * 2ll + i + (i + 1)) % MOD;
    }
    std::vector<int64_t> results(n);
    // To calculate a sum for 4th element we need a sum of all previous solutions.
    // In the example above, those are rectangles [0][0]:[2,3], [0][4]:[1][5] and [0][6].
    std::vector<int64_t> accumulated_results(n);
    // This array stores parts of solution that include only those subarrays which include
    // current element. For the third element, subarrays are (3), (3), (2, 3), (1, 2, 3).
    // including_current[2] = 3 * 1 + 3 * 1 + (2 + 3) * 2 + (1 + 2 + 3) * 3
    std::vector<int64_t> including_current(n);
    // This is just a sum of all elements in all subarrays that include the current element.
    // sum_including_current[2] = 3 + 3 + (2 + 3) + (1 + 2 + 3)
    std::vector<int64_t> sum_including_current(n);
    results[0] = a[0];
    accumulated_results[0] = a[0];
    including_current[0] = a[0];
    sum_including_current[0] = a[0];
    for (auto i = 1; i < n; ++i)
    {
        including_current[i] = including_current[i - 1];
        including_current[i] = (including_current[i] + sum_including_current[i - 1]) % MOD;
        including_current[i] = (including_current[i] + (a[i] * helper[i]) % MOD) % MOD;
        sum_including_current[i] = (sum_including_current[i - 1] + (a[i] * power_of_two(i)) % MOD) % MOD;
        results[i] = (accumulated_results[i - 1] + including_current[i]) % MOD;
        accumulated_results[i] = (accumulated_results[i - 1] + results[i]) % MOD;
    }
    std::cout << results[n - 1] << std::endl;
}

