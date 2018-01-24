/*
 * HackerRank - Insertion Sort Advanced Analysis
 * https://www.hackerrank.com/challenges/insertion-sort/problem
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl

class AVL
{

    struct Node
    {
        Node(int v) : value(v) { }
        int value;
        int height{0};
        int count{1};
        int right_count{0};
        Node* left{nullptr};
        Node* right{nullptr};

        ~Node()
        {
            delete left;
            delete right;
        }
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
        root->right_count += node->count + node->right_count;
        node->left->right = node;
        node->left = temp;
        update_height(node);
        update_height(root);
        return root;
    }

    Node* left_rotate(Node* node)
    {
        auto root = node->right;
        auto temp = node->right->left;
        node->right_count -= (root->count + root->right_count);
        node->right->left = node;
        node->right = temp;
        update_height(node);
        update_height(root);
        return root;
    }

    Node* balance_subtree(Node* node, Child child, Child grandchild)
    {
        if (!is_balanced(node))
        {
            if (child == Child::Left && grandchild == Child::Left)
            {
                return right_rotate(node);
            }
            else if (child == Child::Right && grandchild == Child::Right)
            {
               return left_rotate(node);
            }
            else if (child == Child::Left && grandchild == Child::Right)
            {
                node->left = left_rotate(node->left);
                return right_rotate(node);
            }
            else if (child == Child::Right && grandchild == Child::Left)
            {
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

    Node* insert(Node* node, int value, Child& child, Child& grandchild, int& greater)
    {
        if (node->value == value)
        {
            node->count++;
            greater += node->right_count;
        }
        else if (node->value > value)
        {
            greater += node->right_count + node->count;
            if (node->left == nullptr)
            {
                node->left = new Node(value);
            }
            else
            {
                node->left = insert(node->left, value, child, grandchild, greater);
            }
            grandchild = child;
            child = Child::Left;
        }
        else
        {
            if (node->right == nullptr)
            {
                node->right = new Node(value);
            }
            else
            {
                node->right = insert(node->right, value, child, grandchild, greater);
            }
            node->right_count++;
            grandchild = child;
            child = Child::Right;
        }
        return balance_subtree(node, child, grandchild);
    }

public:

    int insert(int value)
    {
        int greater = 0;
        if (root == nullptr)
        {
            root = new Node(value);
        }
        else
        {
            Child child, grandchild;
            root = insert(root, value, child, grandchild, greater);
        }
        return greater;
    }

    ~AVL()
    {
        delete root;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        AVL tree;
        int N;
        uint64_t result = 0;
        std::cin >> N;
        for (int i = 0; i < N; ++i)
        {
            int value;
            std::cin >> value;
            result += tree.insert(value);
        }
        LOG(result);
    }
}

