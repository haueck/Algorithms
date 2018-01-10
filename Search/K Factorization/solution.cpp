/*
 * HackerRank - K Factorization
 * https://www.hackerrank.com/challenges/k-factorization/problem
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

bool minimal_number_of_factors(int n, std::vector<int>& numbers, int current, std::vector<int>& factors)
{
    if (n == 1)
    {
        return true;
    }
    if (current < 0)
    {
        return false;
    }
    if (n % numbers[current] == 0 && minimal_number_of_factors(n / numbers[current], numbers, current, factors))
    {
        factors.push_back(numbers[current]);
        return true;
    }
    return minimal_number_of_factors(n, numbers, current - 1, factors);
}

std::vector<int> factorization(int n, std::vector<int> numbers)
{
    std::sort(numbers.begin(), numbers.end());
    std::vector<int> factors, result(1, 1);
    auto found = minimal_number_of_factors(n, numbers, numbers.size() - 1, factors);
    if (found)
    {
        std::sort(factors.begin(), factors.end());
        for (auto factor : factors)
        {
            result.push_back(factor * result.back());
        }
        return result;
    }
    else
    {
        return { -1 };
    }
}

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> numbers(k);
    for (int i = 0; i < k; i++)
    {
       std::cin >> numbers[i];
    }
    auto result = factorization(n, numbers);
    for (auto i = 0u; i < result.size(); i++)
    {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}

