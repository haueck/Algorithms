/*
 * HackerRank - Gridland Metro
 * Search
 * https://www.hackerrank.com/challenges/gridland-metro
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <map>

#define LOG(x) std::cout << x << std::endl;

class Route
{
public:
    std::vector<std::pair<int,int>> pairs;

    void add(int a, int b)
    {
        for (auto it = pairs.begin(); it != pairs.end();)
        {
            if (a >= it->first && b <= it->second)
            {
                return;
            }
            else if (a >= it->first && a <= it->second)
            {
                a = it->first;
                it = pairs.erase(it);
            }
            else if (b >= it->first && b <= it->second)
            {
                b = it->second;
                it = pairs.erase(it);
            }
            else if (it->first >= a && it->second <= b)
            {
                it = pairs.erase(it);
            }
            else
            {
                ++it;
            }
        }
        pairs.emplace_back(a, b);
    }

    uint64_t sum()
    {
        uint64_t sum = 0;
        for (auto& pair : pairs)
        {
            sum += 1 + pair.second - pair.first;
        }
        return sum;
    }
};

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int k;
    uint64_t n, m;
    std::cin >> n >> m >> k;
    std::map<int,Route> routes;
    for (int i = 0; i < k; ++i)
    {
        int r, a, b;
        std::cin >> r >> a >> b;
        routes[r].add(a, b);
    }
    uint64_t result = 0;
    for (auto& route : routes)
    {
        result += route.second.sum();
    }
    LOG(n * m - result);
    return 0;
}
