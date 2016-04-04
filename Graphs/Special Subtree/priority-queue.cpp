/*
 * HackerRank - Prim's (MST) : Special Subtree
 * Graphs
 * https://www.hackerrank.com/challenges/primsmstsub
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

#define LOG(x) std::cout << x << std::endl;

class Distance
{
public:
    Distance(int to, int distance) : to(to), distance(distance) { }
    int to;
    int distance;
    bool operator<(const Distance& d) const
    {
        return distance > d.distance;
    }
};

struct Vertex
{
    std::vector<Distance> edges;
};

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, M, S;
    std::cin >> N >> M;
    std::vector<Vertex> vertices(N + 1, Vertex());
    std::vector<int> keys(N + 1, std::numeric_limits<int>::max());

    for (int i = 0; i < M; ++i)
    {
        int a, b, d;
        std::cin >> a >> b >> d;
        vertices[a].edges.emplace_back(b, d);
        vertices[b].edges.emplace_back(a, d);
    }

    std::cin >> S;
    std::priority_queue<Distance> queue;
    queue.emplace(S, 0);
    int total = 0;
    keys[S] = 0;

    while (!queue.empty())
    {
        auto dist = queue.top();
        queue.pop();
        keys[dist.to] = -1;
        for (auto edge : vertices[dist.to].edges)
        {
            if (edge.distance < keys[edge.to])
            {
                if (keys[edge.to] < std::numeric_limits<int>::max())
                {
                    total -= keys[edge.to];
                }
                keys[edge.to] = edge.distance;
                queue.emplace(edge.to, edge.distance);
                total += edge.distance;
            }
        }
    }

    LOG(total);
    return 0;
}

