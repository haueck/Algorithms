/*
 * Find Maximum Index Product
 * https://www.hackerrank.com/challenges/find-maximum-index-product/problem
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

class AVL
{

    struct Node
    {
        Node(int v, int i) : value(v), index(i), right_min(i), right_max(i), subtree_min(i), subtree_max(i) { }
        int value;
        int index;
        int height{0};
        int right_min;
        int right_max;
        int subtree_min;
        int subtree_max;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    enum class Child
    {
        Left,
        Right
    };

    Node* root{nullptr};

    bool is_balanced(Node* node)
    {
        auto left_subtree = node->left ? node->left->height: -1;
        auto right_subtree = node->right ? node->right->height : -1;
        auto balance_factor = std::abs(right_subtree - left_subtree);
        return balance_factor <= 1;
    }

    void update_height(Node* node)
    {
        auto left_subtree = node->left ? node->left->height: -1;
        auto right_subtree = node->right ? node->right->height : -1;
        node->height = std::max(left_subtree, right_subtree) + 1;
    }

    Node* right_rotate(Node* node)
    {
        auto root = node->left;
        auto temp = node->left->right;
        node->left->right = node;
        node->left = temp;
        update_height(node);
        update_height(root);
        root->right_max = std::max(root->right_max, node->right_max);
        root->right_min = std::min(root->right_min, node->right_min);
        root->subtree_max = std::max(root->subtree_max, node->subtree_max);
        root->subtree_min = std::min(root->subtree_min, node->subtree_min);
        auto left_max = node->left == nullptr ? INT32_MIN : node->left->subtree_max;
        auto left_min = node->left == nullptr ? INT32_MAX : node->left->subtree_min;
        auto right_max = node->right == nullptr ? INT32_MIN : node->right->subtree_max;
        auto right_min = node->right == nullptr ? INT32_MAX : node->right->subtree_min;
        node->subtree_max = std::max({ node->index, left_max, right_max });
        node->subtree_min = std::min({ node->index, left_min, right_min });
        return root;
    }

    Node* left_rotate(Node* node)
    {
        auto root = node->right;
        auto temp = node->right->left;
        node->right->left = node;
        node->right = temp;
        update_height(node);
        update_height(root);
        root->subtree_max = std::max(root->subtree_max, node->subtree_max);
        root->subtree_min = std::min(root->subtree_min, node->subtree_min);
        auto left_max = node->left == nullptr ? INT32_MIN : node->left->subtree_max;
        auto left_min = node->left == nullptr ? INT32_MAX : node->left->subtree_min;
        auto right_max = node->right == nullptr ? INT32_MIN : node->right->subtree_max;
        auto right_min = node->right == nullptr ? INT32_MAX : node->right->subtree_min;
        node->right_max = std::max(node->index, right_max);
        node->right_min = std::min(node->index, right_min);
        node->subtree_max = std::max({ node->index, left_max, right_max });
        node->subtree_min = std::min({ node->index, left_min, right_min });
        return root;
    }

    Node* balance_subtree(Node* node, Child child, Child grandchild)
    {
        if (!is_balanced(node))
        {
            if (child == Child::Left && grandchild == Child::Left)
            {
                /*        z                                      y 
                 *       / \                                   /   \
                 *       y   T4      Right Rotate (z)          x      z
                 *      / \          - - - - - - - - ->      /  \    /  \
                 *     x   T3                               T1  T2  T3  T4
                 *    / \
                 *  T1   T2
                 */
                return right_rotate(node);
            }
            else if (child == Child::Right && grandchild == Child::Right)
            {
                /*     z                                y
                 *    /  \                            /   \
                 *   T1   y     Left Rotate(z)       z      x
                 *       /  \   - - - - - - - ->    / \    / \
                 *      T2   x                     T1  T2 T3  T4
                 *          / \
                 *         T3  T4
                 */
                return left_rotate(node);
            }
            else if (child == Child::Left && grandchild == Child::Right)
            {
                /*        z                               z                           x
                 *       / \                            /   \                        /  \
                 *      y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
                 *     / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
                 *   T1   x                          y    T3                    T1  T2 T3  T4
                 *       / \                        / \
                 *     T2   T3                    T1   T2
                 */
                node->left = left_rotate(node->left);
                return right_rotate(node);
            }
            else if (child == Child::Right && grandchild == Child::Left)
            {
                /*      z                            z                            x
                 *     / \                          / \                          /  \
                 *   T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
                 *       / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
                 *      x   T4                      T2   y                  T1  T2  T3  T4
                 *     / \                              /  \
                 *   T2   T3                           T3   T4
                 */
                node->right = right_rotate(node->right);
                return left_rotate(node);
            }
            else
            {
                throw std::runtime_error("Error");
            }
        }
        else
        {
            update_height(node);
            return node;
        }
    }

    Node* insert(Node* node, int value, int index, Child& child, Child& grandchild)
    {
        node->subtree_max = std::max(node->subtree_max, index);
        node->subtree_min = std::min(node->subtree_min, index);
        if (node->value > value)
        {
            if (node->left == nullptr)
            {
                node->left = new Node(value, index);
            }
            else
            {
                node->left = insert(node->left, value, index, child, grandchild);
            }
            grandchild = child;
            child = Child::Left;
        }
        else
        {
            node->right_max = std::max(node->right_max, index);
            node->right_min = std::min(node->right_min, index);
            if (node->right == nullptr)
            {
                node->right = new Node(value, index);
            }
            else
            {
                node->right = insert(node->right, value, index, child, grandchild);
            }
            grandchild = child;
            child = Child::Right;
        }
        return balance_subtree(node, child, grandchild);
    }

    int max_index(Node* node, int value)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else if (node->value <= value)
        {
            return max_index(node->right, value);
        }
        else
        {
            return std::max(node->right_max, max_index(node->left, value));
        }
    }

    int min_index(Node* node, int value)
    {
        if (node == nullptr)
        {
            return INT32_MAX;
        }
        else if (node->value <= value)
        {
            return min_index(node->right, value);
        }
        else
        {
            return std::min(node->right_min, min_index(node->left, value));
        }
    }

public:

    void insert(int value, int index)
    {
        if (root == nullptr)
        {
            root = new Node(value, index);
        }
        else
        {
            Child child, grandchild;
            root = insert(root, value, index, child, grandchild);
        }
    }

    int max_index(int value)
    {
        return max_index(root, value);
    }

    int min_index(int value)
    {
        auto index = min_index(root, value);
        return index == INT32_MAX ? 0 : index;
    }
};

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> data(N);
    for (auto& e : data)
    {
        std::cin >> e;
    }
    AVL avl1, avl2;
    std::vector<int64_t> left(N), right(N);
    for (auto i = 0; i < N; ++i)
    {
        left[i] = avl1.max_index(data[i]);
        avl1.insert(data[i], i + 1);
    }
    for (int i = N - 1; i >= 0; --i)
    {
        right[i] = avl2.min_index(data[i]);
        avl2.insert(data[i], i + 1);
    }
    int64_t result = 0;
    for (auto i = 0; i < N; ++i)
    {
        result = std::max(result, left[i] * right[i]);
    }
    LOG(result);
}

