/*
 * GekkesForGeeks - Find the Maximum Flow
 * http://practice.geeksforgeeks.org/problems/find-the-maximum-flow/0
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define LOG(x) std::cout << x << std::endl

struct Edge
{
    int to;
    int capacity;
    int flow;
};

struct Path
{
    int from;
    int flow;
    bool forward;
};

class Node
{
public:
    std::vector<Edge> forward;
    std::vector<Edge> backward;

    void increase_forward(int to, int flow)
    {
        for (auto& edge : forward)
        {
            if (edge.to == to)
            {
                edge.flow += flow;
                return;
            }
        }
    }

    void increase_backward(int to, int flow)
    {
        for (auto& edge : backward)
        {
            if (edge.to == to)
            {
                edge.flow += flow;
                return;
            }
        }
    }

    void add_forward(int to, int capacity)
    {
        for (auto& edge : forward)
        {
            if (edge.to == to)
            {
                edge.capacity += capacity;
                return;
            }
        }
        forward.emplace_back(Edge{to, capacity, 0});
    }

    void add_backward(int to)
    {
        for (auto& edge : backward)
        {
            if (edge.to == to)
            {
                return;
            }
        }
        backward.emplace_back(Edge{to, 0, 0});
    }

};

bool find_augmenting_path(std::vector<Node>& graph, int S, int T, std::vector<Path>& path)
{
    std::vector<bool> visited(graph.size());
    std::queue<int> queue;
    queue.emplace(S);
    visited[S] = true;
    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();
        for (auto edge : graph[current].forward)
        {
            if (!visited[edge.to] && edge.capacity - edge.flow > 0)
            {
                queue.emplace(edge.to);
                visited[edge.to] = true;
                path[edge.to] = Path{current, edge.capacity - edge.flow, true};
                if (edge.to == T)
                {
                    return true;
                }
            }
        }
        for (auto edge : graph[current].backward)
        {
            if (!visited[edge.to] && edge.flow > 0)
            {
                queue.emplace(edge.to);
                visited[edge.to] = true;
                path[edge.to] = Path{current, edge.flow, false};
                if (edge.to == T)
                {
                    return true;
                }
            }
        }

    }
    return false;
}

void process_path(std::vector<Node>& graph, int S, int T, std::vector<Path>& path)
{
    int flow = std::numeric_limits<int>::max();
    int current = T;
    while (current != S)
    {
        flow = std::min(flow, path[current].flow);
        current = path[current].from;
    }
    current = T;
    while (current != S)
    {
        if (path[current].forward)
        {
            graph[path[current].from].increase_forward(current, flow);
            graph[current].increase_backward(path[current].from, flow);
        }
        else
        {
            graph[path[current].from].increase_backward(current, -1 * flow);
            graph[current].increase_forward(path[current].from, -1 * flow);
        }
        current = path[current].from;
    }
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N, M;
        std::cin >> N >> M;
        std::vector<Node> graph(N);
        for (int i = 0; i < M; ++i)
        {
            int a, b, c;
            std::cin >> a >> b >> c;
            graph[a - 1].add_forward(b - 1, c);
            graph[b - 1].add_forward(a - 1, c);
            graph[a - 1].add_backward(b - 1);
            graph[b - 1].add_backward(a - 1);
        }
        while (true)
        {
            std::vector<Path> path(N);
            bool found = find_augmenting_path(graph, 0, N - 1, path);
            if (!found)
            {
                break;
            }
            process_path(graph, 0, N - 1, path);
        }
        int result = 0;
        for (auto edge : graph[0].forward)
        {
            result += edge.flow;
        }
        LOG(result);
    }
}

