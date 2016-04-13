/*
 * HackerRank - Binary Search Tree : Insertion
 * Trees
 * https://www.hackerrank.com/challenges/binary-search-tree-insertion
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl;

node* create(int value)
{
    auto n = new node;
    n->data = value;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

node* insert(node* root, int value)
{
    auto current = &root;
    while (*current != nullptr)
    {
        if (value <= (*current)->data)
        {
            current = &((*current)->left);
        }
        else
        {
            current = &((*current)->right);
        }
    }
    *current = create(value);
    return root;
}

