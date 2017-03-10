/*
 * HackerRank - Crab Graphs
 * https://www.hackerrank.com/challenges/crab-graphs
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl

class Edge
{
public:
    int to;
    int capacity{0};
    int flow{0};
    Edge(int to, int capacity) : to(to), capacity(capacity) { }
};

class Node
{
public:
    std::vector<Edge> forward;
    std::vector<Edge> backward;
    int visited{0};

    void increase_forward(int to, int by)
    {
        for (auto& edge : forward)
        {
            if (edge.to == to)
            {
                edge.flow += by;
                return;
            }
        }
    }

    void increase_backward(int to, int by)
    {
        for (auto& edge : backward)
        {
            if (edge.to == to)
            {
                edge.flow += by;
                return;
            }
        }
    }

};

bool find_augmenting_path(std::vector<Node>& nodes, int current, int sink)
{
    nodes[current].visited = true;
    if (current == sink)
    {
        return true;
    }

    for (auto& edge : nodes[current].forward)
    {
        if (!nodes[edge.to].visited && edge.capacity - edge.flow > 0)
        {
            auto found = find_augmenting_path(nodes, edge.to, sink);
            if (found)
            {
                nodes[current].increase_forward(edge.to, 1);
                nodes[edge.to].increase_backward(current, 1);
                return true;
            }
        }
    }

    for (auto& edge : nodes[current].backward)
    {
        if (!nodes[edge.to].visited && edge.flow > 0)
        {
            auto found = find_augmenting_path(nodes, edge.to, sink);
            if (found)
            {
                nodes[current].increase_backward(edge.to, -1);
                nodes[edge.to].increase_forward(current, -1);
                return true;
            }
        }
    }

    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int C, N, M;
        std::cin >> N >> C >> M;
        std::vector<Node> nodes(2 * N + 2);
        int source = 2 * N;
        int sink = 2 * N + 1;
        for (int i = 0; i < M; ++i)
        {
            int a, b;
            std::cin >> a >> b;
            // a is a head, b is a foot
            nodes[2 * (a - 1)].forward.emplace_back(2 * (b - 1) + 1, 1);
            nodes[2 * (b - 1) + 1].backward.emplace_back(2 * (a - 1), 1);
            // b is a head, a is a foot
            nodes[2 * (b - 1)].forward.emplace_back(2 * (a - 1) + 1, 1);
            nodes[2 * (a - 1) + 1].backward.emplace_back(2 * (b - 1), 1);
        }
        for (int i = 0; i < N; ++i)
        {
            // Link the source to all heads
            nodes[source].forward.emplace_back(2 * i, std::min(C, (int)nodes[2 * i].forward.size()));
            // Link all feet to the sink
            nodes[2 * i + 1].forward.emplace_back(sink, 1);
        }
        // Finding maximum flow in this new graph will tell us what number
        // of nodes will be covered by crabs. It doesn't find actual crabs,
        // as this problem is NP-Complete.
        int covered_nodes = 0;
        while (true)
        {
            bool found = find_augmenting_path(nodes, source, sink);
            if (!found)
            {
                break;
            }
            for (auto& node : nodes)
            {
                node.visited = false;
            }
            ++covered_nodes;
        }
        LOG(covered_nodes);
    }
}

