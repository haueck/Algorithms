/*
 * HackerRank - The Value of Friendship
 * https://www.hackerrank.com/challenges/value-of-friendship/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

struct Edge
{
    Edge(int target, int id) : target(target), id(id) { }
    int target;
    int id;
};

struct Node
{
    std::vector<Edge> edges;
    bool visited{false};
};

void count_nodes_and_edges(std::vector<Node>& graph, std::vector<bool>& visited_edges, int current, int& nodes, int& edges)
{
    ++nodes;
    graph[current].visited = true;
    for (auto i = 0u; i < graph[current].edges.size(); ++i)
    {
        auto edge = graph[current].edges[i];
        if (!visited_edges[edge.id])
        {
            ++edges;
            visited_edges[edge.id] = true;
        }
        if (!graph[edge.target].visited)
        {
            count_nodes_and_edges(graph, visited_edges, edge.target, nodes, edges);
        }
    }
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int n, m;
        std::cin >> n >> m;
        std::vector<Node> graph(n);
        std::vector<bool> visited_edges(m);
        std::vector<std::pair<int,int>> clusters;
        for (int i = 0; i < m; i++)
        {
            int x, y;
            std::cin >> x >> y;
            graph[x - 1].edges.emplace_back(y - 1, i);
            graph[y - 1].edges.emplace_back(x - 1, i);
        }
        for (int i = 0; i < n; ++i)
        {
            if (!graph[i].visited)
            {
                int nodes = 0, edges = 0;
                count_nodes_and_edges(graph, visited_edges, i, nodes, edges);
                if (nodes > 1)
                {
                    clusters.emplace_back(nodes, edges);
                }
            }
        }
        std::sort(clusters.begin(), clusters.end(), std::greater<std::pair<int,int>>());
        uint64_t total = 0, last = 0;
        int redundant_edges = 0;
        for (auto cluster : clusters)
        {
            auto whole_clusters = last;
            for (uint64_t i = 2; i <= cluster.first; ++i)
            {
                last = whole_clusters + i * (i - 1);
                total += last;
            }
            redundant_edges += cluster.second - cluster.first + 1;
        }
        for (int i = 0; i < redundant_edges; ++i)
        {
            total += last;
        }
        LOG(total);
    }
}

