/*
 * HackerRank - Components in a graph
 * Graphs
 * https://www.hackerrank.com/challenges/components-in-graph
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

class DisjointSet
{
    std::vector<int> nodes;

public:

    DisjointSet() = delete;
    DisjointSet(int n) : nodes(n, -1) { };

    int find(int n)
    {
        if (nodes[n] < 0)
        {
            return n;
        }
        nodes[n] = find(nodes[n]);
        return nodes[n];
    }

    void merge(int n, int m)
    {
        int root1 = find(n);
        int root2 = find(m);
        if (root1 == root2)
        {
            return;
        }

        if (nodes[root1] < nodes[root2])
        {
            nodes[root1] += nodes[root2];
            nodes[root2] = root1;
        }
        else
        {
            nodes[root2] += nodes[root1];
            nodes[root1] = root2;
        }
    }

    void result()
    {
        int max = 0;
        int min = std::numeric_limits<int>::min();
        for (auto e : nodes)
        {
            if (e < max)
            {
                max = e;
            }
            if (e < -1 && e > min)
            {
                min = e;
            }
        }
        LOG(-1 * min << " " << -1 * max);
    }
};

class Node
{
public:
    std::vector<int> edges;
    bool visited{false};

    void addEdge(int n)
    {
        edges.push_back(n);
    }
};

void dfs(DisjointSet& ds, std::vector<Node>& nodes, int root, int current)
{
    ds.merge(root, current);
    nodes[current].visited = true;
    for (auto e : nodes[current].edges)
    {
        if (!nodes[e].visited)
        {
            dfs(ds, nodes, root, e);
        }
    }
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N = 0;
    std::cin >> N;
    std::vector<Node> nodes(2 * N, Node());
    DisjointSet ds(2 * N);

    for (int i = 0; i < N; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        nodes[a - 1].addEdge(b - 1);
        nodes[b - 1].addEdge(a - 1);
    }

    for (int i = 0; i < N; ++i)
    {
        if (!nodes[i].visited)
        {
            dfs(ds, nodes, i, i);
        }
    }

    ds.result();
    return 0;
}

