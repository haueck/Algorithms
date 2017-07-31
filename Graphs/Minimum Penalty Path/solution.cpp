/*
 * HackerRank - Minimum Penalty Path
 * https://www.hackerrank.com/challenges/beautiful-path
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

struct Edge
{
    int to;
    int cost;
    bool enabled{true};
    Edge(int to, int cost) : to(to), cost(cost) { }
    bool operator<(const Edge& o) const { return cost > o.cost; }
};

struct Node
{
    std::vector<Edge> edges;
    bool visited{false};
};

bool dfs(std::vector<Node>& nodes, int current, int target, int forbidden)
{
    nodes[current].visited = true;
    for (auto edge : nodes[current].edges)
    {
        if (edge.cost & forbidden)
        {
            continue;
        }
        if (nodes[edge.to].visited)
        {
            continue;
        }
        if (edge.enabled)
        {
            if (edge.to == target)
            {
                return true;
            }
            auto found = dfs(nodes, edge.to, target, forbidden);
            if (found)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<Node> nodes(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b, cost;
        std::cin >> a >> b >> cost;
        nodes[a - 1].edges.emplace_back(b - 1, cost);
        nodes[b - 1].edges.emplace_back(a - 1, cost);
    }
    int start, target, cost = 0;
    std::cin >> start >> target;
    for (int i = 10; i >= 0; i--)
    {
        // Can we reach the target node, if we skip edges
        // for which cost has a certain bit set to 1?
        auto forbidden = 1 << i;
        auto reachable = dfs(nodes, start - 1, target - 1, forbidden);
        if (reachable)
        {
            for (auto& node : nodes)
            {
                for (auto& edge : node.edges)
                {
                    if (edge.cost & forbidden)
                    {
                        edge.enabled = false;
                    }
                }
            }
        }
        else
        {
            cost |= forbidden;
        }
        for (auto& node : nodes)
        {
            node.visited = false;
        }
    }
    // If the cost is equal to the maximum possible cost,
    // it means there is no path between A and B.
    if (cost == (1 << 11) - 1)
    {
        LOG(-1);
    }
    else
    {
        LOG(cost);
    }
}

