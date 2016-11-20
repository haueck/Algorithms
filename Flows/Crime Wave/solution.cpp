/*
 * UVa Online Judge - Crime Wave - The Sequel
 * Assignment problem solved with Ford-Fulkerson algorithm (Minimum Cost Maximum Flow class)
 * https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1687
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <cmath>

#define LOG(x) std::cout << x << std::endl;
#define INTMAX std::numeric_limits<int>::max()
#define SIZEMAX std::numeric_limits<size_t>::max()

class Edge
{
public:
    Edge(size_t to, int cost, int capacity) : to(to), cost(cost), capacity(capacity) { }
    size_t to;
    int cost;
    int capacity;
};

class Node
{
public:
    int pcapacity{INTMAX};
    int cost{INTMAX};
    size_t previous{SIZEMAX};
    std::vector<Edge> edges{};
    bool visited{false};

    int decrease(size_t to, int by)
    {
        for (auto& edge : edges)
        {
            if (edge.to == to)
            {
                edge.capacity -= by;
                return edge.cost;
            }
        }
        throw "Shouldn't be here";
    }

    void add(size_t to, int capacity, int cost)
    {
        for (auto& edge : edges)
        {
            if (edge.to == to)
            {
                edge.capacity += capacity;
                return;
            }
        }
        edges.emplace_back(to, cost, capacity);
    }

    int capacity(size_t to)
    {
        for (auto& edge : edges)
        {
            if (edge.to == to)
            {
                return edge.capacity;
            }
        }
        return -1;
    }

    void clean()
    {
        cost = INTMAX;
        visited = false;
        previous = SIZEMAX;
        pcapacity = INTMAX;
    }
};

class Problem
{
public:
    size_t n, m, source, sink;
    std::vector<Node> nodes;
    bool initialized{false};

    void initialize()
    {
        std::cin >> n >> m;
        if (m == 0 && n == 0)
        {
            initialized = false;
            return;
        }
        source = m + n;
        sink = m + n + 1;
        nodes = std::vector<Node>(n + m + 2, Node());
        /*
         * Police cars: 0 .. m - 1
         * Banks: m .. m + n - 1
         * Source: m + n
         * Sink: m + n + 1
         */
        for (auto i = 0u; i < n; ++i)
        {
            nodes[m + i].edges.emplace_back(sink, 0, 1);
            for (auto j = 0u; j < m; ++j)
            {
                float cost;
                std::cin >> cost;
                nodes[j].edges.emplace_back(m + i, (int)((cost + 0.005) * 100), 1);
            }
        }
        for (auto j = 0u; j < m; ++j)
        {
            nodes[source].edges.emplace_back(j, 0, 1);
        }
        initialized = true;
    }

    void bellman()
    {
        nodes[source].cost = 0;
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            for (size_t j = 0; j < nodes.size(); ++j)
            {
                Node& node = nodes[j];
                if (node.cost < INTMAX)
                {
                    for (auto& edge : node.edges)
                    {
                        if (edge.capacity > 0)
                        {
                            auto cost = node.cost + edge.cost;
                            Node& n = nodes[edge.to];
                            if (n.cost > cost)
                            {
                                if (i >= nodes.size() - 1)
                                {
                                    throw "Negative cycle";
                                }
                                n.cost = cost;
                                n.previous = j;
                                n.pcapacity = edge.capacity;
                            }
                        }
                    }
                }
            }
        }
    }

    std::vector<size_t> path()
    {
        std::vector<size_t> path;
        auto current = sink;
        while (current != source)
        {
            path.push_back(current);
            current = nodes[current].previous;
            if (current == SIZEMAX)
            {
                return std::vector<size_t>();
            }
        }
        path.push_back(source);
        return std::vector<size_t>(path.rbegin(), path.rend());
    }

    void process(std::vector<size_t> path)
    {
        for (auto i = 1u; i < path.size(); ++i)
        {
            auto cost = nodes[path[i - 1]].decrease(path[i], 1);
            nodes[path[i]].add(path[i - 1], 1, -cost);
        }
    }

    void answer()
    {
        std::vector<int> answer;
        for (auto i = 0u; i < m; ++i)
        {
            Node& node = nodes[i];
            for (auto j = 0u; j < node.edges.size(); ++j)
            {
                if (node.edges[j].capacity == 0)
                {
                    auto back = nodes[node.edges[j].to].capacity(i);
                    if (back == -1 || back == 1)
                    {
                        answer.push_back(node.edges[j].cost);
                    }
                }
            }
        }
        auto sum = 0;
        for (auto el : answer)
        {
            sum += el;
        }
        auto average = (int)(sum / (double)answer.size() + 0.5);
        printf("%.2lf\n", average / 100.0);
    }

    void clean()
    {
        for (auto& node : nodes)
        {
            node.clean();
        }
    }
};

int main()
{
    while (true)
    {
        Problem problem;
        /*
         * Convert the problem to a Minimum Cost Flow problem.
         * A source node will be connected with all police cars with cost (time) 0.
         * Connections between police cars and banks are read from the stdio.
         * All banks are connected to a sink. Ford-Fulkerson algorithm will
         * be used to find the maximimum flow at minimal cost.
         */
        problem.initialize();
        if (!problem.initialized)
        {
            break;
        }
        while (true)
        {
            /*
             * Use the Bellman-Ford algorithm to find the lowest cost path
             * from a source to a sink. It will be used as an augmenting
             * path for the Ford-Fulkerson agorithm.
             */
            problem.bellman();
            /*
             * Traverse the nodes to extract the found path.
             */
            auto path = problem.path();
            if (path.size() == 0)
            {
                /*
                 * Empty path means that augmenting path cannot be created.
                 */
                break;
            }
            /*
             * Apply the flow through the path to the graph.
             */
            problem.process(path);
            problem.clean();
        }
        problem.answer();
    }
}

