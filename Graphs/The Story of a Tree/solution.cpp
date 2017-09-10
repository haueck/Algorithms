/*
 * HackerRank - The Story of a Tree
 * https://www.hackerrank.com/challenges/the-story-of-a-tree
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

template <class T>
T gcd(T a, T b)
{
    while (b != T(0))
    {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

struct Node
{
    std::vector<std::pair<int,bool>> edges;
    int64_t sum{0};
};

int calculate_one_node(std::vector<Node>& nodes, int current, int parent)
{
    int value = 0;
    for (auto edge : nodes[current].edges)
    {
        if (edge.first != parent)
        {
            value += calculate_one_node(nodes, edge.first, current);
        }
        else if (edge.second)
        {
            value++;
        }
    }
    return value;
}

void calculate_all_nodes(std::vector<Node>& nodes, int current, int parent, bool guess)
{
    nodes[current].sum = nodes[parent].sum;
    if (guess)
    {
        nodes[current].sum++;
    }
    for (auto edge : nodes[current].edges)
    {
        if (edge.first == parent)
        {
            if (edge.second)
            {
                nodes[current].sum--;
                break;
            }
        }
    }
    for (auto edge : nodes[current].edges)
    {
        if (edge.first != parent)
        {
            calculate_all_nodes(nodes, edge.first, current, edge.second);
        }
    }
}

int main()
{
    int q;
    std::cin >> q;
    while (q--)
    {
        int n;
        std::cin >> n;
        std::vector<Node> nodes(n);
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            std::cin >> u >> v;
            nodes[u - 1].edges.emplace_back(v - 1, false);
            nodes[v - 1].edges.emplace_back(u - 1, false);
        }
        int g, k;
        std::cin >> g >> k;
        for (int i = 0; i < g; i++)
        {
            int u, v;
            std::cin >> u >> v;
            for (auto& edge : nodes[v - 1].edges)
            {
                if (edge.first == u - 1)
                {
                    edge.second = true;
                    break;
                }
            }
        }
        nodes[0].sum = calculate_one_node(nodes, 0, 0);
        calculate_all_nodes(nodes, 0, 0, false);
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (nodes[i].sum >= k)
            {
                ++count;
            }
        }
        auto divisor = gcd(n, count);
        LOG((count / divisor) << "/" << (n / divisor));
    }
}

