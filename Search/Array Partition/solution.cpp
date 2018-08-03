/*
 * Array Partition
 * https://www.hackerrank.com/contests/hourrank-29/challenges/array-partition/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <set>

#define LOG(x) std::cout << x << std::endl

const int MOD = 1e9 + 7;

class UnionFind
{
public:
    std::vector<int> data;

    UnionFind(int length)
    {
        data.insert(data.begin(), length, -1);
    };

    bool connected(int n1, int n2)
    {
        return find(n1) == find(n2);
    };

    int find(int n)
    {
        if (data[n] < 0)
        {
            return n;
        }
        data[n] = find(data[n]);
        return data[n];
    };

    void merge(int n1, int n2)
    {
        int r1 = find(n1);
        int r2 = find(n2);
        if (r1 == r2)
        {
            return;
        }
        if (data[r1] < data[r2])
        {
            data[r1] = data[r1] + data[r2];
            data[r2] = r1;
        }
        else
        {
            data[r2] = data[r1] + data[r2];
            data[r1] = r2;
        }
    };
};

std::vector<int> get_prime_factors(int n)
{
    std::vector<int> result;
    if (n % 2 == 0)
    {
        result.push_back(2);
        while (n % 2 == 0)
        {
            n = n / 2;
        }
    }
    for (int i = 3; i <= std::sqrt(n); i = i + 2)
    {
        if (n % i == 0)
        {
            result.push_back(i);
            while (n % i == 0)
            {
                n = n / i;
            }
        }
    }
    if (n > 2)
    {
        result.push_back(n);
    }
    return result;
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::cin >> N;
        UnionFind uf(1000000);
        std::set<int> distinct_prime_factors;
        int groups = 0;
        for (auto i = 0; i < N; ++i)
        {
            int value;
            std::cin >> value;
            if (value == 1)
            {
                groups++;
            }
            else
            {
                auto prime_factors = get_prime_factors(value);
                for (auto factor : prime_factors)
                {
                    uf.merge(prime_factors[0], factor);
                    distinct_prime_factors.insert(factor);
                }
            }
        }
        for (auto factor : distinct_prime_factors)
        {
            if (uf.data[factor] < 0)
            {
                groups++;
            }
        }
        int64_t result = 1;
        for (auto i = 0; i < groups; i++)
        {
            result = (result * 2) % MOD;
        }
        // Minus 2 cases when all items are either in P or Q
        result = (result + MOD - 2) % MOD;
        LOG(result);
    }
}

