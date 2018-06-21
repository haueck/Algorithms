/*
 * HackerRank - Xor and Sum
 * https://www.hackerrank.com/challenges/xor-and-sum/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

const int mod = 1e9 + 7;
const auto window = 314160u;
const auto max_size = window + 1e5;

auto calc_powers_of_two()
{
    std::vector<int> powers_of_two(max_size);
    powers_of_two[0] = 1;
    for (auto i = 1; i < max_size; ++i)
    {
        powers_of_two[i] = (2 * powers_of_two[i - 1]) % mod;
    }
    return powers_of_two;
}

auto calc_zeros_contrib(const std::string& a, std::vector<int>& powers_of_two)
{
    std::vector<int> zeros_contrib;
    auto sum = 0;
    for (auto i = 0u; i < window; ++i)
    {
        if (not(i < a.size() && a[i] == '1'))
        {
            sum = (sum + powers_of_two[i]) % mod;
        }
    }
    zeros_contrib.push_back(sum);
    for (auto i = window; i < max_size; ++i)
    {
        auto remove = i - window;
        if (not(remove < a.size() && a[remove] == '1'))
        {
            sum = (sum - powers_of_two[remove]) % mod;
            if (sum < 0)
            {
                sum = sum + mod;
            }
        }
        sum = (sum + powers_of_two[i]) % mod;
        zeros_contrib.push_back(sum);
    }
    return zeros_contrib;
}

auto calc_ones_contrib(const std::string& a, std::vector<int>& powers_of_two)
{
    std::vector<int> ones_contrib;
    auto sum = 0;
    for (auto i = 0u; i < a.size(); ++i)
    {
        if (a[i] == '1')
        {
            sum = (sum + powers_of_two[i]) % mod;
        }
    }
    ones_contrib.push_back(sum);
    for (auto i = window; i < max_size; ++i)
    {
        auto remove = i - window;
        if (remove < a.size() && a[remove] == '1')
        {
            sum = (sum - powers_of_two[remove]) % mod;
            if (sum < 0)
            {
                sum = sum + mod;
            }
        }
        ones_contrib.push_back(sum);
    }
    return ones_contrib;
}

int main()
{
    std::string a, b;
    std::cin >> a >> b;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    if (b.size() < a.size())
    {
        b.append(a.size() - b.size(), '0');
    }
    auto powers_of_two = calc_powers_of_two();
    auto zeros_contrib = calc_zeros_contrib(a, powers_of_two);
    auto ones_contrib = calc_ones_contrib(a, powers_of_two);
    auto result = 0;
    for (auto i = 0u; i < b.size(); ++i)
    {
        if (b[i] == '0')
        {
            // This 0 will produce 1s with 1s in a
            result = (result + ones_contrib[i]) % mod;
        }
        else
        {
            // This 1 will produce 1s with 0s in a
            result = (result + zeros_contrib[i]) % mod;
        }
    }
    // Those are the 1 from a that are revealed when b is shifted right
    auto current = 0;
    for (auto i = 0u; i < window - 1; ++i)
    {
        if (i < a.size() && a[i] == '1')
        {
            current = (current + powers_of_two[i]) % mod;
        }
        result = (result + current) % mod;
    }
    LOG(result);
}

