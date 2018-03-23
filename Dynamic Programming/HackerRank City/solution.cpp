/*
 * HackerRank - HackerRank City
 * https://www.hackerrank.com/challenges/hr-city/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

const int MOD = 1e9 + 7;

int main()
{
    int steps;
    std::cin >> steps;
    std::vector<int> edges(steps);
    for (auto i = 0; i < steps; ++i)
    {
        std::cin >> edges[i];
    }
    uint64_t total = 0;
    uint64_t distances_to_corner = 0;
    uint64_t nodes = 1;
    uint64_t diameter = 0;
    for (auto i = 0; i < steps; ++i)
    {
        // Distances within previous graphs plus distance between the two new nodes
        total = (edges[i] + 4 * total) % MOD;
        // Distances from previous graphs to the two new nodes
        total = (total + 4 * (2 * distances_to_corner + 3 * nodes * edges[i])) % MOD;
        uint64_t helper1 = (nodes * distances_to_corner) % MOD;
        uint64_t helper2 = (nodes * nodes) % MOD;
        // Distances beetwen previous graphs separated by 3 new edges
        total = (total + 4 * (2 * helper1 + 3 * helper2 * edges[i])) % MOD;
        // Distances beetwen previous graphs separated by 2 new edges
        total = (total + 2 * (2 * helper1 + 2 * helper2 * edges[i])) % MOD;
        distances_to_corner = (4 * distances_to_corner + (8 * nodes + 3) * edges[i] + (3 * nodes + 2) * diameter) % MOD;
        diameter = (2 * diameter + 3 * edges[i]) % MOD;
        nodes = (4 * nodes + 2) % MOD;
    }
    LOG(total);
}

