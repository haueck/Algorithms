/*
 * HackerRank - Balanced Forest
 * https://www.hackerrank.com/challenges/balanced-forest/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl

struct Node
{
    int parent{0};
    int64_t value{0};
    int64_t subtree{0};
    std::vector<int> nbs;
};

void precompute(std::vector<Node>& tree, int current, int parent)
{
    tree[current].parent = parent;
    tree[current].subtree = tree[current].value;
    for (auto nb : tree[current].nbs)
    {
        if (nb != parent)
        {
            precompute(tree, nb, current);
            tree[current].subtree += tree[nb].subtree;
        }
    }
}

void modify(std::vector<Node>& tree, int current, int64_t value)
{
    if (current >= 0)
    {
        tree[current].subtree += value;
        modify(tree, tree[current].parent, value);
    }
}

int64_t second_split(std::vector<Node>& tree, int current, int skip, int64_t this_subtree, int64_t other_subtree)
{
    auto result = std::numeric_limits<int64_t>::max();
    auto parent = tree[current].parent;
    for (auto nb : tree[current].nbs)
    {
        if (nb != parent && nb != skip)
        {
            auto first = tree[nb].subtree;
            auto second = this_subtree - first;
            if (first == second && other_subtree <= first)
            {
                result = std::min(result, first - other_subtree);
            }
            else if (first == other_subtree && second < first)
            {
                result = std::min(result, first - second);
            }
            else if (second == other_subtree && first < second)
            {
                result = std::min(result, second - first);
            }
            result = std::min(result, second_split(tree, nb, skip, this_subtree, other_subtree));
        }
    }
    return result;
}

int64_t first_split(std::vector<Node>& tree, int current, int64_t total)
{
    auto result = std::numeric_limits<int64_t>::max();
    auto parent = tree[current].parent;
    for (auto nb : tree[current].nbs)
    {
        if (nb != parent)
        {
            auto first = tree[nb].subtree;
            auto second = total - first;
            if (std::min(first, second) >= total / 3 && std::max(first, second) <= (2 * total) / 3)
            {
                if (first > second)
                {
                    result = std::min(result, second_split(tree, nb, -1, first, second));
                }
                else if (first < second)
                {
                    modify(tree, current, -first);
                    result = std::min(result, second_split(tree, 0, nb, second, first));
                    modify(tree, current, first);
                }
                else
                {
                    result = std::min(result, first);
                }
            }
            result = std::min(result, first_split(tree, nb, total));
        }
    }
    return result;
}

int main()
{
    int q;
    std::cin >> q;
    while (q--)
    {
        int n;
        std::cin >> n;
        std::vector<Node> tree(n);
        for (auto& node : tree)
        {
            std::cin >> node.value;
        }
        for (auto i = 0; i < n - 1; ++i)
        {
            int a, b;
            std::cin >> a >> b;
            tree[a - 1].nbs.push_back(b - 1);
            tree[b - 1].nbs.push_back(a - 1);
        }
        precompute(tree, 0, -1);
        auto result = first_split(tree, 0, tree[0].subtree);
        LOG((result == std::numeric_limits<int64_t>::max() ? -1 : result));
    }
}

