#include <iostream>

static void swap(int* a, int i1, int i2)
{
    int tmp = a[i1];
    a[i1] = a[i2];
    a[i2] = tmp;
}

static void is(int* a, int index, int value)
{
    int i = index - 1;
    while (i >= 0 && a[i] > value)
    {
        swap(a, i, i + 1);
        --i;
    }
}

void insertsort(int* a, int N)
{
    for (int i = 0; i < N; ++i)
    {
        is(a, i, a[i]);
    }
}
