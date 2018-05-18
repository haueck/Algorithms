/*
 * HackerRank - Prime Digit Sums
 * https://www.hackerrank.com/challenges/prime-digit-sums/problem
 * Author: Rafal Kozik
 */

#include <vector>
#include <numeric>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

const int MOD = 1e9 + 7;

auto find_primes()
{
    std::vector<bool> primes(46, true);
    primes[0] = false;
    primes[1] = false;
    for (int i = 2 ; i < 46; ++i)
    {
        for (int j = 2; j < i; ++j)
        {
            if (i % j == 0)
            {
                primes[i] = false;
                break;
            }
        }
    }
    return primes;
}

auto find_numbers(std::vector<bool>& primes)
{
    std::vector<std::string> special;
    for (int i = 1; i < 100000; ++i)
    {
        auto d1 = i / 10000;
        auto d2 = (i / 1000) % 10;
        auto d3 = (i / 100) % 10;
        auto d4 = (i / 10) % 10;
        auto d5 = i % 10;
        if (primes[d1 + d2 + d3] && primes[d1 + d2 + d3 + d4] && primes[d1 + d2 + d3 + d4 + d5])
        {
            if (primes[d2 + d3 + d4] && primes[d2 + d3 + d4 + d5] && primes[d3 + d4 + d5])
            {
                special.push_back("");
                special.back().append(1, '0' + d1);
                special.back().append(1, '0' + d2);
                special.back().append(1, '0' + d3);
                special.back().append(1, '0' + d4);
                special.back().append(1, '0' + d5);
            }
        }
    }
    return special;
}

auto n_equal_3(std::vector<bool>& primes)
{
    int n3 = 0;
    for (int i = 100; i < 1000; ++i)
    {
        auto d1 = i / 100;
        auto d2 = (i / 10) % 10;
        auto d3 = i % 10;
        if (primes[d1 + d2 + d3])
        {
            ++n3;
        }
    }
    return n3;
}

auto n_equal_4(std::vector<bool>& primes)
{
    int n4 = 0;
    for (int i = 1000; i < 10000; ++i)
    {
        auto d1 = i / 1000;
        auto d2 = (i / 100) % 10;
        auto d3 = (i / 10) % 10;
        auto d4 = i % 10;
        if (primes[d1 + d2 + d3] && primes[d2 + d3 + d4] && primes[d1 + d2 + d3 + d4])
        {
            ++n4;
        }
    }
    return n4;
}

// A leader is a valid number that can be followed by another valid number
// Leader 90200 can be followed by 02005 and both numbers are valid
auto find_leaders(std::vector<std::string>& numbers, std::vector<int>& leaders_ids)
{
    std::vector<std::vector<int>> leaders;
    for (auto i = 0u; i < numbers.size(); ++i)
    {
        std::vector<int> followers;
        for (auto j = 0u; j < numbers.size(); ++j)
        {
            auto match = true;
            for (int k = 0; k < 4; ++k)
            {
                if (numbers[i][k + 1] != numbers[j][k])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                followers.push_back(j);
            }
        }
        if (followers.size() > 0)
        {
            leaders_ids[i] = leaders.size();
            leaders.emplace_back(std::move(followers));
        }
    }
    for (auto i = 0u; i < leaders.size(); ++i)
    {
        for (auto follower : leaders[i])
        {
            if (leaders_ids[follower] == -1)
            {
                leaders_ids[follower] = leaders.size();
                leaders.emplace_back();
            }
        }
    }
    return leaders;
}

auto find_valid_starts(std::vector<std::string>& numbers, std::vector<int>& leaders_ids)
{
    std::vector<int> valid_starts;
    for (auto i = 0u; i < numbers.size(); ++i)
    {
        if (numbers[i][0] != '0' && leaders_ids[i] != -1)
        {
            valid_starts.push_back(leaders_ids[i]);
        }
    }
    return valid_starts;
}

int prime_digits_sums(int id, int remaining, std::vector<std::vector<int>>& leaders, std::vector<int>& leaders_ids, std::vector<std::vector<int>>& dp)
{
    if (dp[remaining][id] == -1)
    {
        int64_t result = 0;
        for (auto follower : leaders[id])
        {
            result = (result + prime_digits_sums(leaders_ids[follower], remaining - 1, leaders, leaders_ids, dp)) % MOD;
        }
        dp[remaining][id] = result;
    }
    return dp[remaining][id];
}

int main()
{
    int q;
    std::cin >> q;
    auto primes = find_primes();
    auto n3 = n_equal_3(primes);
    auto n4 = n_equal_4(primes);
    auto numbers = find_numbers(primes);
    auto leaders_ids = std::vector<int>(numbers.size(), -1);
    auto leaders = find_leaders(numbers, leaders_ids);
    auto valid_starts = find_valid_starts(numbers, leaders_ids);
    auto n5 = std::accumulate(numbers.begin(), numbers.end(), 0, [](int a, std::string b) { if (b[0] != '0') { return a + 1; } });
    std::vector<std::vector<int>> dp(4e5, std::vector<int>(leaders.size(), -1));
    for (auto id = 0u; id < leaders.size(); ++id)
    {
        dp[4][id] = 1;
    }
    // If the first call will be with a huge n, then the recursion will be too deep causing segmentation fault.
    // So here I am precomputing same values.
    for (auto id : leaders_ids)
    {
        prime_sums(id, 2e5, leaders, leaders_ids, dp);
    }
    for (int t = 0; t < q; t++)
    {
        int n;
        std::cin >> n;
        if (n == 1)
        {
            LOG(9);
        }
        else if (n == 2)
        {
            LOG(9 * 10);
        }
        else if (n == 3)
        {
            LOG(n3);
        }
        else if (n == 4)
        {
            LOG(n4);
        }
        else if (n == 5)
        {
            LOG(n5);
        }
        else
        {
            int64_t result = 0;
            for (auto start : valid_starts)
            {
                result = (result + prime_digits_sums(start, n - 1, leaders, leaders_ids, dp)) % MOD;
            }
            LOG(result);
        }
    }
}

