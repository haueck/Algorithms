/*
 * Tarjan's algorithm for strongly connected components
 * Author: Rafal Kozik
 */

#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <stack>

#define LOG(x) std::cout << x << std::endl;

class Node
{
public:
    std::vector<int> edges;
    int index{0};
    int lowlink{0};
    bool stack = false;

    void add(int to)
    {
        edges.push_back(to);
    }
};

class Graph
{
public:
    std::vector<Node> nodes;
    std::stack<int> stack{};
    int index{1};

    Graph(int nodes) : nodes(nodes, Node()) { }

    void add(int from, int to)
    {
        nodes[from - 1].add(to - 1);
    }

    std::vector<std::vector<int>> scc()
    {
        std::vector<std::vector<int>> ret;
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            if (nodes[i].index == 0)
            {
                scc(i, ret);
            }
        }
        return ret;
    }

    void scc(int n, std::vector<std::vector<int>>& ret)
    {
        // Set the depth index for v to the smallest unused index
        Node& node = nodes[n];
        node.index = index;
        node.lowlink = index;
        node.stack = true;
        ++index;
        stack.push(n);
        for (auto w : node.edges)
        {
            Node& nb = nodes[w];
            if (nb.index == 0)
            {
                scc(w, ret);
                if (nb.lowlink < node.lowlink)
                {
                    node.lowlink = nb.lowlink;
                }
            }
            else if (nodes[w].stack)
            {
                // Successor w is in stack S and hence in the current SCC
                if (nb.index < node.lowlink)
                {
                    node.lowlink = nb.index;
                }
            }
        }

        // If v is a root node, pop the stack and generate an SCC
        if (node.index == node.lowlink)
        {
            std::vector<int> group;
            while (true)
            {
                int top = stack.top();
                stack.pop();
                group.push_back(top);
                nodes[top].stack = false;
                if (top == n)
                {
                    break;
                }
            }
            ret.push_back(group);
        }
    }
};

TEST(Test, Test)
{
    Graph g(8);
    g.add(1, 2);
    g.add(2, 3);
    g.add(3, 1);
    g.add(4, 2);
    g.add(4, 3);
    g.add(4, 5);
    g.add(5, 4);
    g.add(5, 6);
    g.add(6, 3);
    g.add(6, 7);
    g.add(7, 6);
    g.add(8, 5);
    g.add(8, 7);
    g.add(8, 8);
    auto scc = g.scc();
    ASSERT_EQ(scc.size(), 4);
    ASSERT_EQ(scc[0].size(), 3);
    ASSERT_EQ(scc[1].size(), 2);
    ASSERT_EQ(scc[2].size(), 2);
    ASSERT_EQ(scc[3].size(), 1);
    EXPECT_EQ(scc[3][0], 7);
}

