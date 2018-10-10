/*
 * HackerRank - Find the Running Median
 * https://www.hackerrank.com/challenges/find-the-running-median/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <iomanip>

#define LOG(x) std::cout << x << std::endl;

template <class Comparator>
class Heap
{
    std::vector<int> heap;
    Comparator comp;

public:

    Heap(int size) { heap.reserve(size); }

    int root()
    {
        return heap[0];
    }

    void add(int n)
    {
        heap.push_back(n);
        int idx = heap.size() - 1;
        int prnt = parent(idx);
        // maxheap: heap[idx] > heap[prnt]
        // minheap: heap[idx] < heap[prnt]
        while (idx > 0 && comp(heap[idx], heap[prnt]))
        {
            swap(idx, prnt);
            idx = prnt;
            prnt = parent(idx);
        }
    }

    int extract()
    {
        swap(0, heap.size() - 1);
        int retval = heap.back();
        heap.pop_back();
        heapify(0);
        return retval;
    }

    void heapify(unsigned int idx)
    {
        auto left = 2 * idx + 1;
        auto right = 2 * idx + 2;
        auto extremal = idx;

        // maxheap: heap[left] > heap[idx]
        // minheap: heap[left] < heap[idx]
        if (left < heap.size() && comp(heap[left], heap[idx]))
        {
            extremal = left;
        }
        if (right < heap.size() && comp(heap[right], heap[extremal]))
        {
            extremal = right;
        }
        if (extremal != idx)
        {
            swap(extremal, idx);
            heapify(extremal);
        }
    }

    int parent(int idx)
    {
        return (idx - 1) / 2;
    }

    void swap(int a, int b)
    {
        auto tmp = heap[a];
        heap[a] = heap[b];
        heap[b] = tmp;
    }
};

using MaxHeap = Heap<std::greater<int>>;
using MinHeap = Heap<std::less<int>>;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N = 0, value = 0;
    bool odd = false;
    float median = 0.0;
    std::cin >> N;
    MaxHeap maxheap((N + 1) / 2);
    MinHeap minheap((N + 1) / 2);

    for (int i = 0; i < N; ++i)
    {
        std::cin >> value;
        if (i == 0)
        {
            median = value;
            odd = true;
        }
        else
        {
            if (odd)
            {
                if (median > value)
                {
                    minheap.add(median);
                    maxheap.add(value);
                }
                else
                {
                    minheap.add(value);
                    maxheap.add(median);
                }
                median = (minheap.root() + maxheap.root()) / 2.0;
                odd = false;
            }
            else
            {
                if (value > minheap.root())
                {
                    median = minheap.extract();
                    minheap.add(value);
                }
                else if (value < maxheap.root())
                {
                    median = maxheap.extract();
                    maxheap.add(value);
                }
                else
                {
                    median = value;
                }
                odd = true;
            }
        }
        LOG(std::fixed << std::setprecision(1) << median);
    }
    return 0;
}

