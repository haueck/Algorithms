/*
 * Maximum Xor
 * https://www.hackerrank.com/challenges/maximum-xor/problem
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl

struct Node
{
    Node* zero{nullptr};
    Node* one{nullptr};
    int count{0};
    int last{0};
};

void index(Node* node, int value, int position)
{
    node->count++;
    node->last = value;
    if (position < 0)
    {
        return;
    }
    if (value & (1 << position))
    {
        if (node->one == nullptr)
        {
            node->one = new Node;
        }
        index(node->one, value, position - 1);
    }
    else
    {
        if (node->zero == nullptr)
        {
            node->zero = new Node;
        }
        index(node->zero, value, position - 1);
    }
}

int search(Node* node, int value, int position)
{
    if (node->count == 1 || position < 0)
    {
        return node->last;
    }
    if (value & (1 << position))
    {
        return search(node->zero == nullptr ? node->one : node->zero, value, position - 1);
    }
    else
    {
        return search(node->one == nullptr ? node->zero : node->one, value, position - 1);
    }
}

int main()
{
    int n, m;
    std::cin >> n;
    Node root;
    for (auto i = 0; i < n; ++i)
    {
        int value;
        std::cin >> value;
        index(&root, value, 29);
    }
    std::cin >> m;
    for (auto i = 0; i < m; ++i)
    {
        int value;
        std::cin >> value;
        LOG((value ^ search(&root, value, 29)));
    }
}
