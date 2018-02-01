/*
 * Codeforces - Substring
 * http://codeforces.com/contest/919/problem/D
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

struct Node
{
    Node() : count('z' - 'a' + 1) { }
    std::vector<int> count;
    std::vector<int> edges;
    char letter{'a'};
    bool visiting{false};
    bool visited{false};
};

bool dfs(std::vector<Node>& nodes, int current)
{
    nodes[current].visiting = true;
    for (auto edge : nodes[current].edges)
    {
        if (nodes[edge].visiting)
        {
            return true;
        }
        if (!nodes[edge].visited)
        {
            if (dfs(nodes, edge))
            {
                return true;
            }
        }
        for (int i = 0; i < 'z' - 'a' + 1; ++i)
        {
            nodes[current].count[i] = std::max(nodes[current].count[i], nodes[edge].count[i]);
        }
    }
    nodes[current].count[nodes[current].letter - 'a']++;
    nodes[current].visited = true;
    nodes[current].visiting = false;
    return false;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<Node> nodes(n);
    std::string letters;
    std::cin >> letters;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        nodes[a - 1].edges.push_back(b - 1);
    }
    for (int i = 0; i < n; ++i)
    {
        nodes[i].letter = letters[i];
    }
    for (int i = 0; i < n; ++i)
    {
        if (!nodes[i].visited)
        {
            if (dfs(nodes, i))
            {
                LOG(-1);
                return 0;
            }
        }
    }
    int result = 0;
    for (int i = 0; i < n; ++i)
    {
        for (auto count : nodes[i].count)
        {
            result = std::max(count, result);
        }
    }
    LOG(result);
}

