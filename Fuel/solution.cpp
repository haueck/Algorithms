/*
 * MAIN - Fuel
 * Furthest nodes in a graph
 * http://main.edu.pl/en/archive/pa/2011/pal
 * Author: Rafal Kozik
 */

#include <cstdio>
#include <stack>
#include <vector>

struct Distance
{
    Distance() : destination(0), distance(0) { };
    int destination;
    int distance;
};

class Graph
{
public:

    Graph(int n)
    {
        size = n;
        v.resize(n + 1, std::vector<int>());
        visited.resize(n + 1, 0);
    };

    void add(int k, int l)
    {
        v[k].push_back(l);
        v[l].push_back(k);
    };

    void reset()
    {
        for (int i = 0; i < size + 1; ++i)
        {
            visited[i] = 0;
        }
    };

    Distance furthest(int s)
    {
        std::stack<int> stack;
        stack.push(s);
        visited[s] = 1 + v[s].size();
        int distance = 0;
        Distance furthest;
        while (!stack.empty())
        {
            int top = stack.top();
            bool last = true;
            while (visited[top] > 1)
            {
                int c = v[top][--visited[top] - 1];
                if (visited[c] == 0)
                {
                    stack.push(c);
                    visited[c] = 1 + v[c].size();
                    last = false;
                    if (furthest.distance < ++distance)
                    {
                        furthest.distance = distance;
                        furthest.destination = c;
                    }
                    break;
                }
            }
            if (last)
            {
                --distance;
                stack.pop();
            }
        }
        return furthest;
    };

private:
    std::vector<std::vector<int>> v;
    std::vector<int> visited;
    int size;
};

int main(int argc, char **argv)
{
    int n, m, k, l;
    scanf("%d %d", &n, &m);
    Graph graph(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d", &k, &l);
        graph.add(k, l);
    }
    Distance end1 = graph.furthest(k);
    graph.reset();
    Distance end2 = graph.furthest(end1.destination);
    int longest = end2.distance;
    int result = m;
    if (longest < m)
    {
        int twoway = (m - longest) / 2;
        if (twoway > n - (longest + 1))
        {
            result = n - 1;
        }
        else
        {
            result = longest + twoway;
        }
    }
    printf("%d\n", result + 1);
}

