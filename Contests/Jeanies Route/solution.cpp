/*
 * HackerRank - Jeanie's Route
 * Graphs
 * https://www.hackerrank.com/contests/101hack35/challenges/jeanies-route
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

struct Distance
{
    Distance(int dest, int dist) : destination(dest), distance(dist) { }
    int destination;
    int distance;
};

struct City
{
    std::vector<Distance> roads;
    bool visited{false};
    bool visit{false};
};

bool mark(std::vector<City>& cities, int current, int& total)
{
    auto& city = cities[current];
    bool found = false;
    city.visited = true;
    for (auto& road : city.roads)
    {
        auto& destination = cities[road.destination];
        if (!destination.visited)
        {
            if (mark(cities, road.destination, total))
            {
                destination.visit = true;
                total += road.distance;
                found = true;
            }
        }
    }
    return found || cities[current].visit;
}

Distance furthest(std::vector<City>& cities, int current, int total = 0)
{
    auto& city = cities[current];
    Distance max(current, total);
    city.visited = true;
    for (auto& road : city.roads)
    {
        auto& destination = cities[road.destination];
        if (destination.visit && !destination.visited)
        {
            auto distance = furthest(cities, road.destination, total + road.distance);
            if (distance.distance > max.distance)
            {
                max = distance;
            }
        }
    }
    return max;
}

void clear(std::vector<City>& cities)
{
    for (auto& city : cities)
    {
        city.visited = false;
    }
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, K;
    std::cin >> N >> K;
    std::vector<int> dests(K, 0);
    std::vector<City> cities(N + 1, City());

    for (int i = 0; i < K; ++i)
    {
        std::cin >> dests[i];
    }

    for (int i = 1; i <= N; ++i)
    {
        int a, b, d;
        std::cin >> a >> b >> d;
        cities[a].roads.emplace_back(b, d);
        cities[b].roads.emplace_back(a, d);
    }

    for (auto d : dests)
    {
        cities[d].visit = true;
    }

    int total = 0;
    mark(cities, dests[0], total);
    clear(cities);
    Distance d1 = furthest(cities, dests[0]);
    clear(cities);
    Distance d2 = furthest(cities, d1.destination);

    LOG(2 * total - d2.distance);

    return 0;
}

