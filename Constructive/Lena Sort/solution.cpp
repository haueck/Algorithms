/*
 * HackerRank - Lena Sort
 * https://www.hackerrank.com/challenges/lena-sort
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

#define LOG(x) std::cout << x << std::endl

class Node
{
public:

    Node* left{nullptr};
    Node* right{nullptr};
    int children{0};

    ~Node()
    {
        delete left;
        delete right;
    }
};

class Tree
{
public:

    Node* root;
    int current_leaf_level;
    int current_level{1};
    int extra{0};
    int added{1};
    int nodes;
    std::vector<int> level_occupancy;

    Tree(int n) : root(new Node), current_leaf_level(n - 1), nodes(n), level_occupancy(20, 1) { }

    ~Tree() { delete root; }

    void print()
    {
        LOG("graph {");
        print(root);
        LOG("}");
    }

    void print(Node* node)
    {
        LOG('"' << node << '"' << "[label=\"" << node->children << "\"];");
        if (node->left != nullptr)
        {
            LOG('"' << node << '"' << " -- " << '"' << node->left << '"' << ";");
            print(node->left);
        }
        if (node->right!= nullptr)
        {
            LOG('"' << node << '"' << " -- " << '"' << node->right << '"' << ";");
            print(node->right);
        }
    }

    void build()
    {
        build(root, 1);
        auto current = root;
        auto depth = 1;
        while (added < nodes)
        {
            if (current->right == nullptr)
            {
                current->right = new Node;
                ++added;
            }
            if (extra == depth)
            {
                current->left= new Node;
                ++added;
            }
            current = current->right;
            ++depth;
        }
    }

    void build(Node* node, int depth)
    {
        if (depth > current_level)
        {
            return;
        }
        if (node->right == nullptr && level_occupancy[depth])
        {
            --level_occupancy[depth];
            node->right = new Node;
            ++added;
            build(node->right, depth + 1);
        }
        if (node->left == nullptr && level_occupancy[depth])
        {
            --level_occupancy[depth];
            node->left = new Node;
            ++added;
            build(node->left, depth + 1);
        }
    }

    int decrease_comparisons(uint64_t max)
    {
        if (static_cast<uint64_t>(current_leaf_level - current_level) > max)
        {
            extra = current_leaf_level - max;
            return max;
        }
        else
        {
            if ((1 << current_level) == level_occupancy[current_level])
            {
                ++current_level;
            }
             --current_leaf_level;
            ++level_occupancy[current_level];
            return current_leaf_level + 1 - current_level;
        }
    }

    void count_children() { count_children(root); }

    int count_children(Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int left = count_children(node->left);
        int right = count_children(node->right);
        node->children = left + right;
        return 1 + left + right;
    }

};

void unsort(Node* node, std::vector<int>& data, int left, int right)
{
    if (right - left > 1)
    {
        int pivot = left + (node->left == nullptr ? 0 : 1 + node->left->children);
        unsort(node->left, data, left, pivot - 1);
        unsort(node->right, data, pivot + 1, right);
        for (int i = pivot; i > left; --i)
        {
            std::swap(data[i], data[i - 1]);
        }
    }
}

uint64_t min_comparisons(int n)
{
    int result = 0;
    int levels = 1 + std::log2(n);
    for (int i = 1; i < levels; ++i)
    {
        result += (1 << i) * i;
    }
    int full_tree = (1 << levels) - 1;
    result -=  (full_tree - n) * (levels - 1);
    return result;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        uint64_t n, c;
        std::cin >> n >> c;
        /*
         * Number of comparisons is equal to the sum of depths of all nodes.
         * We get maximum number of comparisons when each node in a tree has one child,
         * it is the case when the arrays is already sorted.
         * To get the minimum number of comparisons the tree has to be complete.
         */
        uint64_t max_comparisons = ((1 + n - 1) * (n - 1)) / 2;
        if (c > max_comparisons || c < min_comparisons(n))
        {
            LOG(-1);
            continue;
        }
        auto comparisons = max_comparisons;
        Tree tree(n);
        /*
         * Move nodes up in the tree until we get required number of comparisons.
         * The tree is not built yet, now we only count number of nodes on each level.
         */
        while (c < comparisons)
        {
            comparisons -= tree.decrease_comparisons(comparisons - c);
        }
        /*
         * Build the tree and count children of each node.
         */
        tree.build();
        tree.count_children();
        std::vector<int> data(n);
        std::iota(data.begin(), data.end(), 1);
        /*
         * Use the tree to reorganize elements in the sorted array
         */
        unsort(tree.root, data, 0, n - 1);
        for (auto e : data)
        {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}

