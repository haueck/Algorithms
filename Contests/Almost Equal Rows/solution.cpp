/*
 * HackerRank - Almost Equal Rows
 * https://www.hackerrank.com/contests/101hack48/challenges/almost-equal-rows
 * Author: Rafal Kozik
 */

#include <set>
#include <vector>
#include <limits>
#include <random>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl

uint64_t hash(uint64_t h, uint64_t value)
{
    return ((h << 5) + h) ^ value;
}

void init(std::vector<uint64_t>& seed)
{
    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());
    std::uniform_int_distribution<uint64_t> dist(0, std::numeric_limits<uint64_t>::max());
    auto gen = std::bind(dist, mersenne_engine);
    std::generate(seed.begin(), seed.end(), gen);
}

int main()
{
    int n, m;
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    std::vector<uint64_t> seed(n);
    std::vector<std::set<int>> nodes(n);
    std::unordered_map<uint64_t,uint64_t> count;
    init(seed);
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        nodes[a - 1].emplace(b - 1);
        nodes[b - 1].emplace(a - 1);
    }
    for (int i = 0; i < n; ++i)
    {
        bool self = false;
        uint64_t h1 = 0;
        uint64_t h2 = 0;
        for (auto nb : nodes[i])
        {
            if (!self && nb > i)
            {
                self = true;
                h2 = hash(h2, seed[i]);
            }
            h1 = hash(h1, seed[nb]);
            h2 = hash(h2, seed[nb]);
        }
        if (!self)
        {
            h2 = hash(h2, seed[i]);
        }
        ++count[h1];
        ++count[h2];
    }
    uint64_t result = 0;
    for (auto& pair : count)
    {
        result += pair.second * (pair.second - 1) / 2;
    }
    LOG(result);
}

