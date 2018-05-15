/*
 * Codeforces - Cyclic Components
 * http://codeforces.com/contest/977/problem/E
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

struct Node
{
    std::vector<int> nbs;
    bool visited{false};
    bool start{false};
    int start_reached{0};
};

bool dfs(std::vector<Node>& nodes, int parent, int current)
{
    bool success = true;
    nodes[current].visited = true;
    for (auto nb : nodes[current].nbs)
    {
        if (nb != parent)
        {
            if (nodes[nb].start)
            {
                nodes[nb].start_reached++;
            }
            else if (nodes[nb].visited)
            {
                if (!nodes[current].start)
                {
                    success = false;
                }
            }
            else
            {
                if (!dfs(nodes, current, nb))
                {
                    success = false;
                }
            }
        }
    }
    if (nodes[current].nbs.size() == 1)
    {
        success = false;
    }
    return success;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<Node> nodes(n);
    for (auto i = 0; i < m; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        nodes[a - 1].nbs.push_back(b - 1);
        nodes[b - 1].nbs.push_back(a - 1);
    }
    int count = 0;
    for (auto i = 0; i < n; ++i)
    {
        if (!nodes[i].visited)
        {
            nodes[i].start = true;
            nodes[i].visited = true;
            auto success = dfs(nodes, i, i);
            if (nodes[i].start_reached != 1)
            {
                success = false;
            }
            if (nodes[i].nbs.size() != 2)
            {
                success = false;
            }
            if (success)
            {
                ++count;
            }
        }
    }
    LOG(count);
}
