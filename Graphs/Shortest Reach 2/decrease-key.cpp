/*
 * HackerRank - Dijkstra: Shortest Reach 2
 * Graphs
 * https://www.hackerrank.com/challenges/dijkstrashortreach 
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <numeric>

#define LOG(x) std::cout << x << std::endl;

class MinHeap
{
public:

    class Element
    {
    public:

        int key;
        int pos;

        Element(int pos) : key(std::numeric_limits<int>::max()), pos(pos) { }

        bool operator<(const Element& e) const
        {
            return key < e.key;
        }
    };

private:

    std::vector<int> pos;
    std::vector<Element> heap;

    void downheap(int idx)
    {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;
        int size = heap.size();

        if (left < size && heap[smallest].key > heap[left].key)
        {
            smallest = left;
        }
        if (right < size && heap[smallest].key > heap[right].key)
        {
            smallest = right;
        }

        if (smallest != idx)
        {
            swap(idx, smallest);
            downheap(smallest);
        }
    }

    void upheap(int idx)
    {
        if (idx == 0)
        {
            return;
        }
        int parent = (idx - 1) / 2;
        if (heap[parent].key > heap[idx].key)
        {
            swap(parent, idx);
            upheap(parent);
        }
    }

    void swap(int i1, int i2)
    {
        pos[heap[i1].pos] = i2;
        pos[heap[i2].pos] = i1;
        auto tmp = heap[i1];
        heap[i1] = heap[i2];
        heap[i2] = tmp;
    }

public:

    MinHeap(int size) : pos(size), heap(size, std::numeric_limits<int>::max())
    {
        std::iota(pos.begin(), pos.end(), 0);
        std::iota(heap.begin(), heap.end(), 0);
    }

    bool empty()
    {
        return heap.empty();
    }

    int key(int idx)
    {
        return pos[idx] < static_cast<int>(heap.size()) ? heap[pos[idx]].key : -1;
    }

    Element smallest()
    {
        swap(0, heap.size() - 1);
        auto retval = heap.back();
        heap.pop_back();
        downheap(0);
        return retval;
    }

    void decrease(int id, int value)
    {
        int idx = pos[id];
        heap[idx].key = value;
        upheap(idx);
    }
};

class Distance
{
public:
    Distance(int to, int distance) : to(to), distance(distance) { }
    int to;
    int distance;
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
            MinHeap queue(N);
            queue.decrease(S - 1, 0);

            while (!queue.empty())
            {
                auto smallest = queue.smallest();
                if (smallest.key == std::numeric_limits<int>::max())
                {
                    std::cout << "-1 ";
                    break;
                }
                if (smallest.pos == i)
                {
                    std::cout << smallest.key << " ";
                    break;
                }
                for (auto edge : vertices[smallest.pos].edges)
                {
                    int distance = smallest.key + edge.distance;
                    if (queue.key(edge.to) > distance)
                    {
                        queue.decrease(edge.to, distance);
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    return 0;
}

