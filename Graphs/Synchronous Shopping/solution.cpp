/*
 * HackerRank - Synchronous Shopping
 * https://www.hackerrank.com/challenges/synchronous-shopping
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>

#define LOG(x) std::cout << x << std::endl;

class Distance
{
public:
    int to;
    int cost;
    int fish;
    Distance(int to, int cost, int fish = 0) : to(to), cost(cost), fish(fish) { }
    bool operator<(const Distance& other) const { return cost > other.cost; }
};

class Shop
{
public:
    std::vector<Distance> neighbors;
    int fish{0};
};

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, M, K;
    std::cin >> N >> M >> K;
    int max_mask = 1 << K;
    std::vector<Shop> shops(N, Shop());
    for (int i = 0; i < N; ++i)
    {
        int T;
        std::cin >> T;
        for (int t = 0; t < T; ++t)
        {
            int fish;
            std::cin >> fish;
            shops[i].fish |= 1 << (fish - 1);
        }
    }
    for (int i = 0; i < M; ++i)
    {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        shops[from - 1].neighbors.emplace_back(to - 1, cost);
        shops[to - 1].neighbors.emplace_back(from - 1, cost);
    }
    std::vector<std::vector<int>> distance(N, std::vector<int>(max_mask, std::numeric_limits<int>::max()));
    std::priority_queue<Distance> queue;
    queue.emplace(0, 0, shops[0].fish);
    distance[0][shops[0].fish] = 0;
    while (!queue.empty())
    {
        auto current = queue.top();
        queue.pop();
        if (current.cost > distance[current.to][current.fish])
        {
            continue;
        }
        for (auto& road : shops[current.to].neighbors)
        {
            auto new_distance = distance[current.to][current.fish] + road.cost;
            auto mask = current.fish | shops[road.to].fish;
            if (new_distance < distance[road.to][mask])
            {
                distance[road.to][mask] = new_distance;
                queue.emplace(road.to, new_distance, mask);
            }
        }
    }
    int result = std::numeric_limits<int>::max();
    for (int i = 0; i < max_mask; ++i)
    {
        for (int j = 0; j < max_mask; ++j)
        {
            if ((i | j) == max_mask - 1)
            {
                result = std::min(result, std::max(distance[N - 1][i], distance[N - 1][j]));
            }
        }
    }
    LOG(result);
    return 0;
}

