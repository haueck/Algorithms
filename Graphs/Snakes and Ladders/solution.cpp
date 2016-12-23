/*
 * HackerRank - Snakes and Ladders: The Quickest Way Up
 * Graphs
 * https://www.hackerrank.com/challenges/the-quickest-way-up
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

#define LOG(x) std::cout << x << std::endl;

class Edge
{
public:
    int to;
    int distance{1};
    Edge(int to) : to(to) { }
    bool operator==(const Edge& other)
    {
        return to == other.to;
    }
};

class Distance
{
public:
    int to;
    int distance;
    Distance(int t, int d) : to(t), distance(d) { }
    bool operator<(const Distance& other) const
    {
        return distance > other.distance;
    }
};

class Node
{
public:
    std::vector<Edge> forward_edges;
    std::vector<Edge> backward_edges;

    void add_forward(int e)
    {
        forward_edges.emplace_back(e);
    }

    void add_backward(int e)
    {
        backward_edges.emplace_back(e);
    }

    void remove_forward(int e)
    {
        forward_edges.erase(std::remove(forward_edges.begin(), forward_edges.end(), Edge(e)), forward_edges.end());
    }
};

int find_shortest_path(std::vector<Node>& nodes, int start, int target)
{
    std::priority_queue<Distance> queue;
    std::vector<int> distances(nodes.size(), std::numeric_limits<int>::max());
    queue.emplace(start, 0);
    while (!queue.empty())
    {
        Distance current = queue.top();
        queue.pop();
        if (current.to == target)
        {
            return current.distance;
        }
        for (auto& edge : nodes[current.to].forward_edges)
        {
            int new_distance = current.distance + edge.distance;
            if (distances[edge.to] > new_distance)
            {
                distances[edge.to] = new_distance;
                queue.emplace(edge.to, new_distance);
            }
        }
        distances[current.to] = -1;
    }
    return -1;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        std::vector<Node> nodes(101, Node());
        for (int i = 1; i <= 99; ++i)
        {
            for (int j = 1; j <= 6 && i + j <= 100; ++j)
            {
                nodes[i].add_forward(i + j);
                nodes[i + j].add_backward(i);
            }
        }
        int N, M;
        std::cin >> N;
        for (int i = 0; i < N; ++i)
        {
            int from, to;
            std::cin >> from >> to;
            for (auto& edge : nodes[from].backward_edges)
            {
                nodes[edge.to].remove_forward(from);
                nodes[edge.to].add_forward(to);
                nodes[to].add_backward(edge.to);
            }
            nodes[from].backward_edges.clear();
        }
        std::cin >> M;
        for (int i = 0; i < M; ++i)
        {
            int from, to;
            std::cin >> from >> to;
            for (auto& edge : nodes[from].backward_edges)
            {
                nodes[edge.to].remove_forward(from);
                if (edge.to != to)
                {
                    nodes[edge.to].add_forward(to);
                    nodes[to].add_backward(edge.to);
                }
            }
            nodes[from].backward_edges.clear();
        }
        LOG(find_shortest_path(nodes, 1, 100));
    }
    return 0;
}

