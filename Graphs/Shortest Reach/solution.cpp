/*
 * HackerRank - Breadth First Search: Shortest Reach
 * Graphs
 * https://www.hackerrank.com/challenges/bfsshortreach
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <queue>

struct Node
{
    std::vector<int> edges;
    int distance{-1};
};

int main() {
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        int N, M, S;
        std::cin >> N >> M;
        std::vector<Node> nodes(N, Node());
        for (int i = 0; i < M; ++i)
        {
            int x, y;
            std::cin >> x >> y;
            nodes[x - 1].edges.push_back(y - 1);
            nodes[y - 1].edges.push_back(x - 1);
        }
        std::cin >> S;
        int source = S - 1;
        std::queue<int> queue;
        nodes[source].distance = 0;
        queue.push(source);
        while (!queue.empty())
        {
            int current = queue.front();
            int distance = nodes[current].distance;
            queue.pop();
            for (int nb : nodes[current].edges)
            {
                if (nodes[nb].distance < 0)
                {
                    queue.push(nb);
                    nodes[nb].distance = distance + 6;
                }
            }
        }
        for (int i = 0; i < N; ++i)
        {
            if (i != source)
            {
                std::cout << nodes[i].distance << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

