/*
 * UVa Online Judge - Sending email
 * Shortes path - Dijkstra
 * https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1927
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <queue>

#define LOG(x) std::cout << x << std::endl;

struct Distance
{
    int node;
    int distance;
    Distance(int node, int distance) : node(node), distance(distance) { };
    bool operator<(const Distance& other) const { return other.distance < distance; };
};

struct Node 
{
    uint32_t distance{~0u};
    std::vector<Distance> edges;
};

int main(int argc, char **argv)
{
    int N = 0;
    scanf("%d", &N);
    for (int tc = 0; tc < N; ++tc)
    {
        int n, m, S, T;
        scanf("%d %d %d %d", &n, &m, &S, &T);
        std::vector<Node> nodes(n);
        for (int i = 0; i < m; ++i)
        {
            int n1, n2, w;
            scanf("%d %d %d", &n1, &n2, &w);
            nodes[n1].edges.emplace_back(n2, w);
            nodes[n2].edges.emplace_back(n1, w);
        }
        nodes[S].distance = 0;
        std::priority_queue<Distance> queue;
        queue.emplace(S, 0);
        while (true)
        {
            int n = queue.top().node;
            Node& node = nodes[n];
            queue.pop();
            if (n == T)
            {
                std::cout << "Case #" << 1 + tc << ": " << node.distance << std::endl;
                break;
            }
            for (auto& edge : node.edges)
            {
                Node& neighbour = nodes[edge.node];
                // If distance is zero, it means that it was already visited
                if (neighbour.distance != 0)
                {
                    uint32_t distance = node.distance + edge.distance;
                    // If a new path is shorter, update a distance
                    if (neighbour.distance > distance)
                    {
                        neighbour.distance = distance;
                        queue.emplace(edge.node, distance);
                    }
                }
            }
            if (queue.empty())
            {
                std::cout << "Case #" << 1 + tc << ": unreachable" << std::endl;
                break;
            }
            // Mark as visited
            node.distance = 0;
        }
    }
    return 0;
}

