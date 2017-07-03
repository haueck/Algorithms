/*
 * HackerRank - Cut Tree
 * https://www.hackerrank.com/challenges/cuttree
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <cstring>

#define LOG(x) std::cout << x << std::endl

int64_t dp[50][50][50][2];

void graph_to_tree(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& tree, std::vector<bool>& visited, int current)
{
    visited[current] = true;
    for (auto neighbour : graph[current])
    {
        if (!visited[neighbour])
        {
            tree[current].push_back(neighbour);
            graph_to_tree(graph, tree, visited, neighbour);
        }
    }
}

int64_t count_subtrees(std::vector<std::vector<int>>& tree, int current, int children, int cuts, bool current_included)
{
    if (cuts < 0)
    {
        return 0;
    }
    if (children == 0)
    {
        if (cuts == 0)
        {
            // This function count subtrees with exactly 'cuts' number of cuts between a subtree and a remaining graph.
            // So when we reach a leaf, the number of 'cuts' has to be 0.
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (dp[current][children][cuts][current_included] == -1)
    {
        int64_t count = 0;
        if (current_included)
        {
            // The last child is not included. Count subtrees when the last child is cut off.
            count += count_subtrees(tree, current, children - 1, cuts - 1, true);
            // The last child is included. There are 'cuts' ways to split remaining cuts between the last child and all remaining children.
            auto last_child = tree[current][children - 1];
            for (int i = 0; i <= cuts; ++i)
            {
                count += count_subtrees(tree, current, children - 1, cuts - i, true) * count_subtrees(tree, last_child, tree[last_child].size(), i, true);
            }
        }
        else if (cuts == 0)
        {
            // If this node is not included and we have no more cuts available, we won't be able to include any of its descendands.
            // This is because including a child while its parent is not included, means cutting an edge between them.
            // We return 1 saying that in this is case we can only create one empty set.
            count = 1;
        }
        else
        {
            for (int i = 0; i < children; ++i)
            {
                auto child = tree[current][i];
                // This child is not included. The current one is not included either, so number of cuts remains the same.
                count += count_subtrees(tree, child, tree[child].size(), cuts, false);
                // This child is included. As the current one is not included, the number of cuts decreases by one.
                count += count_subtrees(tree, child, tree[child].size(), cuts - 1, true);
            }
        }
        dp[current][children][cuts][current_included] = count;
    }
    return dp[current][children][cuts][current_included];
}

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> graph(n);
    std::vector<std::vector<int>> tree(n);
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
    int64_t count = 0;
    std::vector<bool> visited(n);
    std::memset(dp, ~0, sizeof(dp));
    graph_to_tree(graph, tree, visited, 0);
    for (int cuts = 0; cuts <= k; ++cuts)
    {
        count += count_subtrees(tree, 0, tree[0].size(), cuts, false);
        count += count_subtrees(tree, 0, tree[0].size(), cuts, true);
    }
    LOG(count);
}

