#include <iostream>

static void swap(int* a, int i1, int i2)
{
    int tmp = a[i1];
    a[i1] = a[i2];
    a[i2] = tmp;
}

static void heapify(int* a, int idx, int N)
{
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int largest = 0;

    if (left < N && a[left] > a[idx])
    {
        largest = left;
    }
    else
    {
        largest = idx;
    }
    if (right < N && a[right] > a[largest])
    {
        largest = right;
    }

    if (largest != idx)
    {
        swap(a, largest, idx);
        heapify(a, largest, N);
    }
}

static void buildheap(int* a, int N)
{
    for (int i = N / 2 - 1; i >= 0; --i)
    {
        heapify(a, i, N);
    }
}

void heapsort(int* a, int N)
{
    buildheap(a, N);
    for (int i = N - 1; i > 0; --i)
    {
        swap(a, 0, i);
        heapify(a, 0, i);
    }
}
