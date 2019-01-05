/*
 * Codeforces - Makoto and a Blackboard
 * https://codeforces.com/contest/1097/problem/D
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

const int64_t MOD = 1e9 + 7;

int64_t modular_multiplicative_inverse(int64_t a)
{
    int64_t power = MOD - 2;
    int64_t result = 1;
    a = a % MOD;
    while (power > 0) {
        if (power & 1) {
            result = (result * a) % MOD;
        }
        a = (a * a) % MOD;
        power /= 2;
    }
    return result;
}

std::map<int64_t,int> prime_factorization(int64_t n) {
    std::map<int64_t,int> result;
    while (n % 2 == 0) {
        result[2]++;
        n = n / 2;
    }
    for (int64_t i = 3; i <= std::sqrt(n); i = i + 2) {
        while (n % i == 0) {
            result[i]++;
            n = n / i;
        }
    }
    if (n > 1) {
        result[n]++;
    }
    return result;
}

int64_t expected_value(int64_t prime, int count, int K) {
    std::vector<int64_t> probabilities(count + 1);
    probabilities.back() = 1;
    for (int k = 0; k < K; ++k) {
        std::vector<int64_t> next(probabilities.size());
        for (auto i = 0; i < count + 1; ++i) {
            auto p = (probabilities[i] * modular_multiplicative_inverse(i + 1)) % MOD;
            for (auto j = 0; j <= i; ++j) {
                next[j] = (next[j] + p) % MOD;
            }
        }
        probabilities.swap(next);
    }
    int64_t current = 1;
    int64_t result = 0;
    for (auto p : probabilities) {
        result = (result + ((p * current) % MOD)) % MOD;
        current = (current * prime) % MOD;
    }
    return result;
}

int main()
{
    int64_t N, K;
    std::cin >> N >> K;
    auto factors = prime_factorization(N);
    int64_t result = 1;
    for (auto [ prime, count ] : factors) {
        result = (result * expected_value(prime, count, K)) % MOD;
    }
    LOG(result);
}

