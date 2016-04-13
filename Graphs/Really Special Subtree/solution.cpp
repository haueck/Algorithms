/*
 * HackerRank - Kruskal (MST): Really Special Subtree
 * Graphs
 * https://www.hackerrank.com/challenges/kruskalmstrsub
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <queue>

#define LOG(x) std::cout << x << std::endl;

class DisjointSet
{
    std::vector<int> data;

public:

    DisjointSet(int n) : data(n, -1) { }

    int find(int node)
    {
        if (data[node] < 0)
        {
            return node;
        }

        data[node] = find(data[node]);
        return data[node];
    }

    bool cycle(int n1, int n2)
    {
        return find(n1) == find(n2);
    }

    void merge(int n1, int n2)
    {
        auto root1 = find(n1);
        auto root2 = find(n2);

        if (data[root1] < data[root2])
        {
            data[root1] += data[root2];
            data[root2] = root1;
        }
        else
        {
            data[root2] += data[root1];
            data[root1] = root2;
        }
    }
};

struct Edge
{
    Edge(int t, int c) : from(-1), to(t), cost(c) { }
    Edge(int f, int t, int c) : from(f), to(t), cost(c) { }
    int from;
    int to;
    int cost;
    bool operator<(const Edge& o) const
    {
        if (o.cost == cost)
        {
            return cost + from + to > o.cost + o.from + o.to;
        }
        else
        {
            return cost > o.cost;
        }
    }
};

struct Node
{
    std::vector<Edge> edges;
};

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, M;
    std::cin >> N >> M;
    std::priority_queue<Edge> queue;
    DisjointSet ds(N);
    for (int i = 0; i < M; ++i)
    {
        int x, y, c;
        std::cin >> x >> y >> c;
        queue.emplace(x - 1, y - 1, c);
    }

    int total = 0;
    while (!queue.empty())
    {
        auto e = queue.top();
        queue.pop();
        if (!ds.cycle(e.to, e.from))
        {
            total += e.cost;
            ds.merge(e.to, e.from);
        }
    }
    LOG(total);
    return 0;
}

