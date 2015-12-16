/*
 * UVa Online Judge - Dark Roads
 * Minimum Spanning Tree (MST) - Kruskal
 * https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2678
 * Author: Rafal Kozik
 */

#include <iostream>
#include <algorithm>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class Road
{
public:
    Road(int j1, int j2, int cost) : j1(j1), j2(j2), cost(cost) { };
    int j1;
    int j2;
    int cost;
    bool operator<(const Road& other) const { return cost < other.cost; };
};

class UnionFind
{
public:

    /*
     * data contains negative and positive numbers
     * n is negative - I am the root of a set that has size |n|
     * n is positive - n is my parent
     */
    std::vector<int> data;

    UnionFind(int length)
    {
        // At the beginning all elements are roots
        data.insert(data.begin(), length, -1);
    };

    bool connected(int n1, int n2)
    {
        // Do we have the same root?
        return find(n1) == find(n2);
    };

    int find(int n)
    {
        // Am I root?
        if (data[n] < 0)
        {
            return n;
        }
        // Make the tree shallow - make all the elements in the set point to the root
        data[n] = find(data[n]);
        return data[n];
    };

    void merge(int n1, int n2)
    {
        int r1 = find(n1);
        int r2 = find(n2);
        if (r1 == r2)
        {
            // We are in the same set, no need to merge/union
            return;
        }

        // Check which subset is larger and connect smaller to larger
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

int main(int argc, char **argv)
{
    int m = -1;
    int n = -1;
    while (true)
    {
        scanf("%d %d", &m, &n);
        if (m == 0 && n == 0)
        {
            break;
        }
        std::vector<Road> roads;
        UnionFind forest(m);
        roads.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            int j1, j2, cost;
            scanf("%d %d %d", &j1, &j2, &cost);
            roads.emplace_back(j1, j2, cost);
        }
        std::sort(roads.begin(), roads.end());
        int total = 0;
        int cost = 0;
        for (auto& road : roads)
        {
            total += road.cost;
            if (!forest.connected(road.j1, road.j2))
            {
                forest.merge(road.j1, road.j2);
                cost += road.cost;
            }
        }
        std::cout << total - cost << std::endl;
    }
    return 0;
}

