/*
 * HackerRank - Tower Breakers, Revisited!
 * https://www.hackerrank.com/challenges/tower-breakers-revisited-1
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

std::vector<int> sift(int max)
{
    int size = (max + 1) / 2;
    std::vector<bool> sieve(size, true);
    std::vector<int> primes(1, 2);
    int i = 0;
    int is = 3;
    while (is < size)
    {
        if (sieve[i])
        {
            for (int j = is; j < size; j += i + i + 3)
            {
                sieve[j] = false;
            }
        }
        ++i;
        is = 2 * i * (i + 3) + 3;
    }
    for (int i = 0; i < size ; ++i)
    {
        if (sieve[i])
        {
            primes.push_back(i + i + 3);
        }
    }
    return primes;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    auto primes = sift(1000000);
    for (int t = 0; t < T; ++t)
    {
        int N;
        std::cin >> N;
        std::vector<int> nim(N);
        for (int i = 0; i < N; ++i)
        {
            int M, count = 0;
            std::cin >> M;
            auto upper = std::reverse_iterator<std::vector<int>::iterator>(std::upper_bound(primes.begin(), primes.end(), M));
            for (auto it = upper; it != primes.rend(); ++it)
            {
                while (M % *it == 0)
                {
                    ++count;
                    M = M / *it;
                }
                if (M == 1)
                {
                    break;
                }
            }
            nim[i] = count;
        }
        int result = 0;
        for (int i = 0; i < N; ++i)
        {
            result ^= nim[i];
        }
        LOG((result == 0 ? 2 : 1));
    }
    return 0;
}

