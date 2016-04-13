/*
 * HackerRank - Swap Nodes
 * Trees
 * https://www.hackerrank.com/challenges/swap-nodes-algo
 * Author: Rafal Kozik
 */

#include <iostream>
#include <queue>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class Node
{
    int value;
    Node* left{nullptr};
    Node* right{nullptr};

public:

    Node() = delete;

    Node(int n) : value(n) { }

    ~Node()
    {
        if (left != nullptr)
        {
            delete left;
        }
        if (right != nullptr)
        {
            delete right;
        }
    }

    int val()
    {
        return value;
    }

    Node* addLeft(int n)
    {
        return left = new Node(n);
    }

    Node* addRight(int n)
    {
        return right = new Node(n);
    }

    void inorder()
    {
        if (left != nullptr)
        {
            left->inorder();
        }
        std::cout << value << " ";
        if (right != nullptr)
        {
            right->inorder();
        }
    }

    void index(std::vector<std::vector<Node*>>& idx, unsigned int depth = 0)
    {
        if (depth == idx.size())
        {
            idx.emplace_back(1, this);
        }
        else
        {
            idx[depth].push_back(this);
        }
        if (left != nullptr)
        {
            left->index(idx, depth + 1);
        }
        if (right != nullptr)
        {
            right->index(idx, depth + 1);
        }
    }

    void swap()
    {
        auto tmp = left;
        left = right;
        right = tmp;
    }
};

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N = 0, S = 0;
    std::cin >> N;
    Node root(1);
    std::queue<Node*> queue;
    queue.push(&root);

    for (int i = 0; i < N; ++i)
    {
        int a, b;
        auto current = queue.front();
        queue.pop();
        std::cin >> a >> b;
        if (a >= 0)
        {
            queue.push(current->addLeft(a));
        }
        if (b >= 0)
        {
            queue.push(current->addRight(b));
        }
    }

    std::vector<std::vector<Node*>> index;
    root.index(index);
    std::cin >> S;

    for (int i = 0; i < S; ++i)
    {
        unsigned int k, s;
        std::cin >> s;
        k = s;
        while (k <= index.size())
        {
            for (auto n : index[k - 1])
            {
                n->swap();
            }
            k += s;
        }
        root.inorder();
        std::cout << std::endl;
    }

    return 0;
}

