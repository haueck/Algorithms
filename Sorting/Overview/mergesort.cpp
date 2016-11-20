#include <iostream>

static void merge(int* a, int* helper, int left, int middle, int right)
{
   int il = left;
   int ir = middle + 1;
   
   for (int i = left; i <= right; ++i)
   {
      helper[i] = a[i];
   }

   int index = left;
   while (il <= middle && ir <= right)
   {
      if (helper[il] < helper[ir])
      {
         a[index++] = helper[il++];
      }
      else
      {
         a[index++] = helper[ir++];
      }
   }

   while (il <= middle)
   {
      a[index++] = helper[il++];
   }
}

static void split(int* a, int* helper, int left, int right)
{
   if (left < right)
   {
      int middle = (right + left) / 2;
      split(a, helper, left, middle);
      split(a, helper, middle + 1, right);
      merge(a, helper, left, middle, right);
   }
}

void mergesort(int* a, int N)
{
    int* helper = new int[N];
    split(a, helper, 0, N - 1);
}

