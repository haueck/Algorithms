/*
 * HackerRank - Tree: Level Order Traversal
 * Trees
 * https://www.hackerrank.com/challenges/tree-level-order-traversal
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <queue>

#define LOG(x) std::cout << x << std::endl;

void LevelOrder(node* root)
{
    std::queue<node*> queue;
    queue.push(root);

    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();
        if (current->left != nullptr)
        {
            queue.push(current->left);
        }
        if (current->right != nullptr)
        {
            queue.push(current->right);
        }
        std::cout << current->data << " ";
    }

    std::cout << std::endl;
}
