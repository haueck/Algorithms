/*
 * HackerRank - Kingdom Division
 * https://www.hackerrank.com/challenges/kingdom-division
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

const int mod{1000000007};

class Node
{
public:
    std::vector<int> edges;
    bool group{false};
    bool betty{false};
    bool leaf{false};
};

void mark(std::vector<Node>& nodes, int current, int parent)
{
    auto& node = nodes[current];
    if (node.edges.size() == 1)
    {
        if (!node.group)
        {
            nodes[node.edges[0]].group = true;
            node.leaf = 1;
        }
    }
    for (auto nb : node.edges)
    {
        if (nb != parent)
        {
            mark(nodes, nb, current);
        }
    }
}

int64_t count(std::vector<Node>& nodes, std::vector<int[2][2]>& dp, int current, int parent, bool betty)
{
    auto& cache = dp[current][betty][nodes[parent].betty];
    if (cache == 0)
    {
        auto& node = nodes[current];
        int64_t result = 1;
        node.betty = betty;
        for (auto edge : node.edges)
        {
            if (edge != parent && !nodes[edge].leaf)
            {
                result = (result * (count(nodes, dp, edge, current, true) + count(nodes, dp, edge, current, false))) % mod;
            }
        }
        if (!node.group && betty != nodes[parent].betty)
        {
            // The invalid variable tells the number of combination in which
            // the current node belongs to one child and all neighbours belong
            // to the other child. We need to substract them from all possible
            // combinations.
            int64_t invalid = 1;
            for (auto edge : node.edges)
            {
                if (edge != parent && !nodes[edge].leaf)
                {
                    invalid = (invalid * dp[edge][!betty][betty]) % mod;
                }
            }
            cache = result - invalid;
            if (cache < 0)
            {
                cache += mod;
            }
        }
        else
        {
            cache = result;
        }
    }
    return cache;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<Node> nodes(n);
    std::vector<int[2][2]> dp(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u;
        int v;
        std::cin >> u >> v;
        nodes[u - 1].edges.push_back(v - 1);
        nodes[v - 1].edges.push_back(u - 1);
    }
    // Mark leaves and groups. A node marked as a group has a leaf
    // attached to it, so it can change independently. If a node is not
    // marked as a group, we need to check for invalid combinations.
    mark(nodes, 0, 0);
    for (int i = 0; i < n; i++)
    {
        if (nodes[i].group)
        {
            LOG((count(nodes, dp, 0, 0, true) + count(nodes, dp, 0, 0, false)) % mod);
            return 0;
        }
    }
}

