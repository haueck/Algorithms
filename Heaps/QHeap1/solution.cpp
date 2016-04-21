/*
 * HackerRank - QHEAP1
 * Heaps
 * https://www.hackerrank.com/challenges/qheap1
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class Heap
{
    std::vector<int> heap;

public:

    Heap() { }

    int smallest()
    {
        return heap[0];
    }

    void add(int n)
    {
        heap.push_back(n);
        int inserted = heap.size() - 1;
        if (inserted > 0)
        {
            int parent = (inserted - 1) / 2;
            while (heap[parent] > heap[inserted])
            {
                swap(parent, inserted);
                inserted = parent;
                parent = (inserted - 1) / 2;
            }
        }
    }

    void remove(int n)
    {
        auto position = 0u;
        for (auto i = 0u; i < heap.size(); ++i)
        {
            if (heap[i] == n)
            {
                position = i;
                break;
            }
        }
        swap(position, heap.size() - 1);
        heap.pop_back();
        heapify(position);
    }

    void heapify(unsigned int position)
    {
        auto left = 2 * position + 1;
        auto right = 2 * position + 2;
        auto smallest = position;

        if (left < heap.size() && heap[position] > heap[left])
        {
            smallest = left;
        }
        if (right < heap.size() && heap[smallest] > heap[right])
        {
            smallest = right;
        }
        if (smallest != position)
        {
            swap(position, smallest);
            heapify(smallest);
        }
    }

    void swap(int e1, int e2)
    {
        auto tmp = heap[e1];
        heap[e1] = heap[e2];
        heap[e2] = tmp;
    }

};

int main(int argc, char **argv)
{
    Heap heap;
    int N = 0, op = 0, value = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d", &value);
            heap.add(value);
        }
        else if (op == 2)
        {
            scanf("%d", &value);
            heap.remove(value);
        }
        else
        {
            LOG(heap.smallest());
        }
    }
    return 0;
}

