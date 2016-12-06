/*
 * HackerRank - Even Tree
 * Graphs
 * https://www.hackerrank.com/challenges/even-tree
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class Node
{
public:
    std::vector<int> edges;
    bool visited{false};
    void add(int n)
    {
        edges.push_back(n);
    }
};

int cut(std::vector<Node>& tree, int current, int& result)
{
    auto count = 1;
    tree[current].visited = true;
    for (auto nb : tree[current].edges)
    {
        if (!tree[nb].visited)
        {
            auto children = cut(tree, nb, result);
            if (children > 0 && children % 2 == 0)
            {
                ++result;
            }
            else
            {
                count += children;
            }
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, M;
    std::cin >> N >> M;
    std::vector<Node> tree(N, Node());
    for (int i = 0; i < M; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        tree[a - 1].add(b - 1);
        tree[b - 1].add(a - 1);
    }
    int result = 0;
    cut(tree, 0, result);
    LOG(result);
    return 0;
}

