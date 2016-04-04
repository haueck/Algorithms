/*
 * HackerRank - Dijkstra: Shortest Reach 2
 * Graphs
 * https://www.hackerrank.com/challenges/dijkstrashortreach 
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
    int N, M, T, S;
    std::cin >> T;
    while (T--)
    {
        std::cin >> N >> M;
        std::vector<Vertex> vertices(N, Vertex());

        for (int i = 0; i < M; ++i)
        {
            int a, b, d;
            std::cin >> a >> b >> d;
            vertices[a - 1].edges.emplace_back(b - 1, d);
            vertices[b - 1].edges.emplace_back(a - 1, d);
        }

        std::cin >> S;

        for (int i = 0; i < N; ++i)
        {
            if (i == S - 1)
            {
                continue;
            }
            std::vector<int> distances(N, std::numeric_limits<int>::max());
            std::priority_queue<Distance> queue;
            queue.emplace(S - 1, 0);

            while (true)
            {
                auto current = queue.top();
                queue.pop();
                if (distances[current.to] < 0)
                {
                    continue;
                }
                if (current.to == i)
                {
                    std::cout << current.distance << " ";
                    break;
                }
                distances[current.to] = -1;
                for (auto edge : vertices[current.to].edges)
                {
                    int distance = current.distance + edge.distance;
                    if (distances[edge.to] > distance)
                    {
                        distances[edge.to] = distance;
                        queue.emplace(edge.to, distance);
                    }
                }
                if (queue.empty())
                {
                    std::cout << "-1 ";
                    break;
                }
            }
        }
        std::cout << std::endl;
    }

    return 0;
}

