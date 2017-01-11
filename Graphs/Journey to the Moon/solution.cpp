/*
 * HackerRank - Journey to the Moon
 * Graph Theory
 * https://www.hackerrank.com/challenges/journey-to-the-moon
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class Node
{
public:
    int color{0};
    std::vector<int> edges;

    void add(int to)
    {
        edges.emplace_back(to);
    }
};

int dfs(std::vector<Node>& nodes, int current, int color)
{
    int count = 1;
    auto& node = nodes[current];
    node.color = color;
    for (auto edge : node.edges)
    {
        if (nodes[edge].color == 0)
        {
            count += dfs(nodes, edge, color);
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, I;
    std::cin >> N >> I;
    std::vector<Node> nodes(N, Node());
    for (auto i = 0; i < I; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        nodes[a].add(b);
        nodes[b].add(a);
    }
    int color = 0;
    int total = 0;
    uint64_t result = 0;
    for (auto i = 0; i < N; ++i)
    {
        if (nodes[i].color == 0)
        {
            int count = dfs(nodes, i, ++color);
            result += count * total;
            total += count;
        }
    }
    LOG(result);
    return 0;
}

