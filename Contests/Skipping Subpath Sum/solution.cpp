/*
 * HackerRank - Skipping Subpath Sum
 * https://www.hackerrank.com/contests/optimization-oct17/challenges/skipping-subpath-sum
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

struct InputOptimizer
{
    InputOptimizer()
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);
    }
};

InputOptimizer io;

struct Node
{
    Node(int n) : edges(n), index(n) { }
    int cost;
    int acost;
    std::vector<int> edges;
    std::vector<int> index;
};

int convert(std::vector<std::vector<int>>& g, std::vector<Node>& nodes, int v, int p, int current, std::vector<int>& map, std::vector<int>& cost)
{
    int next = current + 1;
    map[v] = current;
    nodes[current].edges[0] = map[p];
    nodes[current].index[0] = current;
    nodes[current].cost = cost[v];
    nodes[current].acost = std::max(0, cost[v]);
    int count = 1;
    for (auto u : g[v])
    {
        if (u != p)
        {
            nodes[current].edges[count] = next;
            nodes.emplace_back(g[u].size());
            next = convert(g, nodes, u, v, next, map, cost);
            nodes[current].index[count] = next - 1;
            ++count;
        }
    }
    return next;
}

std::vector<int> skippingSubpathSum(int n, std::vector<int> c, std::vector<std::vector<int>> graph, std::vector<std::pair<int,int>> queries)
{
    std::vector<Node> nodes;
    std::vector<int> answers(queries.size());
    std::vector<int> map(graph.size() + 1);
    nodes.reserve(graph.size());
    nodes.emplace_back(graph[0].size() + 1);
    convert(graph, nodes, 0, graph.size(), 0, map, c);
    for (auto q = 0u; q < queries.size(); ++q)
    {
        int emeh = 0, omeh = 0, emsf = 0, omsf = 0, d = 1;
        int current = map[queries[q].first];
        int last = map[queries[q].second];
        while (true)
        {
            if (d & 1)
            {
                omeh = std::max(nodes[current].acost, omeh + nodes[current].cost);
                omsf = std::max(omsf, omeh);
            }
            else
            {
                emeh = std::max(nodes[current].acost, emeh + nodes[current].cost);
                emsf = std::max(emsf, emeh);
            }
            if (current == last)
            {
                break;
            }
            int next = 0;
            for (int i = 0, size = nodes[current].index.size(); i < size; ++i)
            {
                if (nodes[current].index[i] >= last)
                {
                    next = i;
                    break;
                }
            }
            current = nodes[current].edges[next];
            ++d;
        }
        answers[q] = std::max(emsf, omsf);
    }
    return answers;
}

int main()
{
    auto answers = skippingSubpathSum(5, { 3, -2, 1, -1, 2 }, { { 1, 3 }, { 0, 2 }, { 1 }, { 0, 4 }, { 3 } }, { { 2, 4 }, { 1, 3 }, { 3, 3 }, { 4, 1 }, { 4, 0 } });
    for (auto a : answers)
    {
        std::cout << a << std::endl;
    }
}

