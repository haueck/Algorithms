/*
 * HackerRank - Cut the Tree
 * https://www.hackerrank.com/challenges/cut-the-tree
 * Author: Rafal Kozik
 */

#include <limits>
#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

struct Node
{
    std::vector<int> children;
    int data{0};
    int subtree{0};
    bool visited{false};
};

int calculate_sums(std::vector<Node>& nodes, int current)
{
    auto& node = nodes[current];
    node.subtree = node.data;
    node.visited = true;
    for (auto child : node.children)
    {
        if (!nodes[child].visited)
        {
            node.subtree += calculate_sums(nodes, child);
        }
    }
    node.visited = false;
    return node.subtree;
}

void find_best_cut(std::vector<Node>& nodes, int current, int total, int& result)
{
    nodes[current].visited = true;
    for (auto child : nodes[current].children)
    {
        if (!nodes[child].visited)
        {
            result = std::min(result, std::abs((total - nodes[child].subtree) - nodes[child].subtree));
            find_best_cut(nodes, child, total, result);
        }
    }
    nodes[current].visited = false;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<Node> nodes(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> nodes[i].data;
    }
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        nodes[a - 1].children.push_back(b - 1);
        nodes[b - 1].children.push_back(a - 1);
    }
    auto total = calculate_sums(nodes, 0);
    int result = std::numeric_limits<int>::max();
    find_best_cut(nodes, 0, total, result);
    LOG(result);
}

