#include <iostream>

static void swap(int* a, int i1, int i2)
{
    int tmp = a[i1];
    a[i1] = a[i2];
    a[i2] = tmp;
}

static int pivot1(int* a, int left, int right)
{
    int p = (left + right) / 2;
    swap(a, p, right);
    int store = left;
    for (int i = left; i < right; ++i)
    {
        if (a[i] <= a[right])
        {
            swap(a, store, i);
            ++store;
        }
    }
    swap(a, store, right);
    return store;
}

static int pivot2(int* a, int left, int right)
{
   int p = a[(left + right) / 2];
   while (left <= right)
   {
      while (a[left] < p)
      {
         ++left;
      }
      while (a[right] > p)
      {
         --right;
      }
      
      if (left <= right)
      {
         swap(a, left++, right--);
      }
   }
   return left;
}

void quicksort1(int* a, int left, int right)
{
    int p = pivot1(a, left, right);
    if (p - 1 > left)
    {
        quicksort1(a, left, p - 1);
    }
    if (p + 1 < right)
    {
        quicksort1(a, p + 1, right);
    }
}

void quicksort2(int* a, int left, int right)
{
    int p = pivot2(a, left, right);
    if (p - 1 > left)
    {
        quicksort2(a, left, p - 1);
    }
    if (p < right)
    {
        quicksort2(a, p, right);
    }
}

void quicksort(int* a, int N)
{
   quicksort2(a, 0, N - 1);
}
