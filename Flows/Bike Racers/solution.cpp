/*
 * HackerRank - Bike Racers
 * Network Flows - Bipartite Matching, Ford-Fulkerson
 * https://www.hackerrank.com/challenges/bike-racers
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

int N, M, K, S, T;

struct Path
{
    int from;
    int to;
    int flow;
    int64_t cost;
    bool forward;
    bool operator<(const Path& c) const { return cost > c.cost; }

    Path() { }

    Path(int to, int64_t cost) : to(to), cost(cost) { }

    void set(int p_from, int p_flow, int64_t p_cost, bool p_forward)
    {
        from = p_from;
        flow = p_flow;
        cost = p_cost;
        forward = p_forward;
    }
};

struct Edge
{
    int to;
    int capacity;
    int flow{0};
    int64_t cost;

    Edge(int to, int capacity, int64_t cost) : to(to), capacity(capacity), cost(cost) { }
};

struct Vertex
{
    std::vector<Edge> forward;
    std::vector<Edge> backward;

    void addForward(int to, int capacity, int64_t cost)
    {
        forward.emplace_back(to, capacity, cost);
    }

    void addBackward(int to, int capacity, int64_t cost)
    {
        backward.emplace_back(to, capacity, cost);
    }

    void increase(std::vector<Edge>& edges, int to, int by)
    {
        for (auto& edge : edges)
        {
            if (edge.to == to)
            {
                edge.flow += by;
                return;
            }
        }
    }

    void increaseForward(int to, int by)
    {
        increase(forward, to, by);
    }

    void increaseBackward(int to, int by)
    {
        increase(backward, to, by);
    }
};

struct Point
{
    Point(int x, int y) : x(x), y(y) { }
    int x;
    int y;
};

void input(std::vector<Point>& v, int size)
{
    for (int i = 0; i < size; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        v.emplace_back(x, y);
    }
}

void add(std::vector<Vertex>& vertices, int from, int to, int capacity, int64_t cost)
{
    vertices[from].addForward(to, capacity, cost);
    vertices[to].addBackward(from, capacity, cost);
}

int64_t distance(Point p1, Point p2)
{
    int64_t d1 = p1.x - p2.x;
    int64_t d2 = p1.y - p2.y;
    return d1 * d1 + d2 * d2;
}

bool augmenting(std::vector<Vertex>& vertices, std::vector<Path>& path)
{
    std::priority_queue<Path> queue;
    std::vector<int64_t> costs(vertices.size(), std::numeric_limits<int64_t>::max());
    queue.emplace(S, 0.0);
    costs[S] = 0;

    while (!queue.empty())
    {
        auto current = queue.top().to;
        queue.pop();

        if (costs[current] < 0)
        {
            continue;
        }
        if (current == T)
        {
            return true;
        }

        for (auto& edge : vertices[current].forward)
        {
            auto cost = costs[current] + edge.cost;
            if (edge.capacity > edge.flow && costs[edge.to] > cost)
            {
                costs[edge.to] = cost;
                queue.emplace(edge.to, cost);
                path[edge.to].set(current, edge.capacity - edge.flow, edge.cost, true);
            }
        }

        for (auto& edge : vertices[current].backward)
        {
            auto cost = costs[current] - edge.cost;
            if (edge.flow > 0 && costs[edge.to] > cost)
            {
                costs[edge.to] = cost;
                queue.emplace(edge.to, cost);
                path[edge.to].set(current, edge.flow, edge.cost, false);
            }
        }

        costs[current] = -1;
    }
    return false;
}

void process(std::vector<Vertex>& vertices, const std::vector<Path>& path)
{
    int current = T;
    int flow = std::numeric_limits<int>::max();
    while (current != S)
    {
        auto& node = path[current];
        if (node.flow < flow)
        {
            flow = node.flow;
        }
        current = node.from;
    }
    current = T;
    while (current != S)
    {
        auto& node = path[current];
        if (node.forward)
        {
            vertices[node.from].increaseForward(current, flow);
            vertices[current].increaseBackward(node.from, flow);
        }
        else
        {
            vertices[node.from].increaseBackward(current, -1 * flow);
            vertices[current].increaseForward(node.from, -1 * flow);
        }
        current = node.from;
    }
}

std::vector<Vertex> initialize(int64_t max, const std::vector<Point>& bikers, const std::vector<Point>& bikes)
{
    std::vector<Vertex> vertices(N + M + 3, Vertex());
    add(vertices, 0, 1, K, 0);
    for (int i = 0; i < N; ++i)
    {
        add(vertices, 1, 2 + i, 1, 0);
    }
    for (int i = 0; i < M; ++i)
    {
        add(vertices, 2 + N + i, T, 1, 0);
    }
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            auto d = distance(bikers[i], bikes[j]);
            if (d <= max)
            {
                add(vertices, 2 + i, 2 + N + j, 1, d);
            }
        }
    }
    return vertices;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    std::cin >> N >> M >> K;
    S = 0;
    T = 2 + N + M;
    std::vector<Vertex> vertices(T + 1, Vertex());
    std::vector<Point> bikers;
    std::vector<Point> bikes;
    bikers.reserve(N);
    bikes.reserve(M);
    input(bikers, N);
    input(bikes, M);

    int64_t low = 0;
    int64_t high = 1000000000000000;
    while (low < high)
    {
        int64_t mid = (low + high) / 2;
        auto vertices = initialize(mid, bikers, bikes);
        while (true)
        {
            std::vector<Path> path(vertices.size(), Path());
            auto found = augmenting(vertices, path);
            if (!found)
            {
                break;
            }
            process(vertices, path);
        }
        if (vertices[0].forward[0].flow == K)
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    LOG(low);
    return 0;
}

