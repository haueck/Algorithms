/*
 * HackerRank - Vertical Sticks
 * https://www.hackerrank.com/challenges/vertical-sticks
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#define LOG(x) std::cout << x << std::endl

std::vector<long double> cache(51);

long double factorial(int n)
{
    if (cache[n] == 0)
    {
        cache[n] = (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
    }
    return cache[n];
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int N;
        std::cin >> N;
        std::vector<int> sticks(N);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> sticks[i];
        }
        std::sort(sticks.begin(), sticks.end());
        int first_lower = -1;
        long double result = 1.0;
        for (int i = 1; i < N; ++i)
        {
            if (sticks[i] > sticks[i - 1])
            {
                first_lower = i - 1;
            }
            long double covered_permutations = 0;
            int number_of_lower_sticks = first_lower + 1;
            for (int k = number_of_lower_sticks; k > 0; --k)
            {
                // The number of ways we can choose k lower sticks
                // from all available lower sticks. Those sticks
                // are just in front of the current stick i.
                auto a0 = factorial(number_of_lower_sticks) / factorial(k) / factorial(number_of_lower_sticks - k);
                // The number of ways we can arrange k lower sticks
                // in front of the current stick
                auto a1 = factorial(k);
                // The number of ways we can arrange all other stick
                auto a2 = factorial(N - 1 - k);
                // The number of valid positions of stick i
                auto a3 = N - number_of_lower_sticks;
                auto permutations = a0 * a1 * a2 * a3;
                covered_permutations += permutations;
                result += permutations * (k + 1) / factorial(N);
            }
            // All other permutations will contribute 1 to the sum
            result += (factorial(N) - covered_permutations) / factorial(N);
        }
        LOG(std::fixed << std::setprecision(2) << result);
    }
}

