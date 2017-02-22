/*
 * HackerRank - Jack goes to Rapture
 * https://www.hackerrank.com/challenges/jack-goes-to-rapture
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <cmath>

#define LOG(x) std::cout << x << std::endl;

class Distance
{
public:
    int to;
    int64_t cost;
    Distance(int to, int64_t cost) : to(to), cost(cost) { }
    bool operator<(const Distance& other) const
    {
        return cost > other.cost;
    }
};

class Station
{
public:
    std::vector<Distance> roads;

    void add(int to, int cost)
    {
        roads.emplace_back(to, cost);
    }
};

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, M;
    std::cin >> N >> M;
    std::vector<Station> stations(N);
    std::vector<int64_t> costs(N, std::numeric_limits<int64_t>::max());
    for (int i = 0; i < M; ++i)
    {
        int a, b, cost;
        std::cin >> a >> b >> cost;
        stations[a - 1].add(b - 1, cost);
        stations[b - 1].add(a - 1, cost);
    }
    std::priority_queue<Distance> queue;
    queue.emplace(0, 0);
    costs[0] = 0;
    while (!queue.empty())
    {
        auto current = queue.top();
        queue.pop();
        if (current.cost > costs[current.to])
        {
            continue;
        }
        if (current.to == N - 1)
        {
            LOG(current.cost);
            return 0;
        }
        for (auto& road : stations[current.to].roads)
        {
            auto new_cost = current.cost + std::max(static_cast<int64_t>(0), road.cost - current.cost);
            if (new_cost < costs[road.to])
            {
                queue.emplace(road.to, new_cost);
                costs[road.to] = new_cost;
            }
        }
    }
    LOG("NO PATH EXISTS");
    return 0;
}

