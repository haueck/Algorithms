#include <iostream>
#include <vector>

static int top(int* a, int N)
{
    int max = 10;
    for (int i = 0; i < N; ++i)
    {
        while (a[i] > max)
        {
            max *= 10;
        }
    }
    return max;
}

void radixsort(int* a, int N)
{
    int t = top(a, N);
    for (int m = 10; m <= t; m *= 10)
    {
        std::vector<std::vector<int>> vec(10, std::vector<int>());
        int n = m / 10;
        for (int i = 0; i < N; ++i)
        {
            vec[(a[i] % m) / n].push_back(a[i]);
        }
        int index = 0;
        for (int i = 0; i < 10; ++i)
        {
            for (auto el : vec[i])
            {
                a[index++] = el;
            }
        }
    }
}
