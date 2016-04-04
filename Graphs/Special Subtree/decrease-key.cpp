/*
 * HackerRank - Prim's (MST) : Special Subtree
 * Graphs
 * https://www.hackerrank.com/challenges/primsmstsub
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <numeric>

#define LOG(x) std::cout << x << std::endl;

class MinHeap
{
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

    int smallest()
    {
        swap(0, heap.size() - 1);
        auto retval = heap.back();
        heap.pop_back();
        downheap(0);
        return retval.pos;
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
    int N, M, S, total = 0;
    std::cin >> N >> M;
    std::vector<Vertex> vertices(N, Vertex());
    MinHeap queue(N);

    for (int i = 0; i < M; ++i)
    {
        int a, b, d;
        std::cin >> a >> b >> d;
        vertices[a - 1].edges.emplace_back(b - 1, d);
        vertices[b - 1].edges.emplace_back(a - 1, d);
    }

    std::cin >> S;
    queue.decrease(S - 1, 0);

    while (!queue.empty())
    {
        auto idx = queue.smallest();
        for (auto edge : vertices[idx].edges)
        {
            auto key = queue.key(edge.to);
            if (key > edge.distance)
            {
                if (key < std::numeric_limits<int>::max())
                {
                    total -= key;
                }
                queue.decrease(edge.to, edge.distance);
                total += edge.distance;
            }
        }
    }

    LOG(total);
    return 0;
}

