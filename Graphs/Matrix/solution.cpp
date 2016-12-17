/*
 * HackerRank - Matrix
 * Graphs
 * https://www.hackerrank.com/challenges/matrix
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

class Edge
{
public:

    Edge(int t, int w) : to(t), weight(w) { }
    int to;
    int weight;
    bool good{true};
};

class Node
{
public:

    std::vector<Edge> edges;
    bool visited{false};
    bool machine{false};

    void add(int to, int weight)
    {
        edges.emplace_back(to, weight);
    }

    void destroy(Edge& edge)
    {
        edge.good = false;
    }

    void destroy(int to)
    {
        for (auto& edge : edges)
        {
            if (edge.to == to)
            {
                edge.good = false;
                return;
            }
        }
    }

};

int remove(std::vector<Node>& nodes, int n, int min, int& result)
{
    Node& node = nodes[n];
    node.visited = true;
    for (auto& edge : node.edges)
    {
        if (edge.good && !nodes[edge.to].visited)
        {
            int local_min = min < edge.weight ? min : edge.weight;
            if (nodes[edge.to].machine)
            {
                // This edge leads to another machine,
                // we can begin the journey back
                local_min = -local_min;
            }
            else
            {
                local_min = remove(nodes, edge.to, local_min, result);
            }
            if (local_min < 0)
            {
                // We are on our journey back, looking for the edge
                // with the minimal weight
                if (edge.weight + local_min == 0)
                {
                    node.destroy(edge);
                    nodes[edge.to].destroy(n);
                    result += edge.weight;
                    min = std::numeric_limits<int>::min();
                }
                else
                {
                    min = local_min;
                }
                break;
            }
        }
    }
    node.visited = false;
    return min;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, K;
    std::cin >> N >> K;
    std::vector<int> machines(K, 0);
    std::vector<Node> nodes(N, Node());
    for (int i = 0; i < N - 1; ++i)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        nodes[a].add(b, c);
        nodes[b].add(a, c);
    }
    for (int i = 0; i < K; ++i)
    {
        std::cin >> machines[i];
        nodes[machines[i]].machine = true;
    }

    int result = 0;
    for (uint32_t i = 0; i < machines.size();)
    {
        bool found = remove(nodes, machines[i], std::numeric_limits<int>::max(), result) < 0;
        if (!found)
        {
            ++i;
        }
    }
    LOG(result);
    return 0;
}

