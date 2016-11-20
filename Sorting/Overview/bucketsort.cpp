#include <iostream>
#include <vector>
#include "sorting.hpp"

static int bucket(int v, int size)
{
   return v / size;
}

void debug(const std::vector<std::vector<int>>& buckets)
{

}

void bucketsort(int* a, int N, int max, int size)
{
   std::vector<std::vector<int>> buckets(1 + max / size, std::vector<int>());
   for (int i = 0; i < N; ++i)
   {
      buckets[bucket(a[i], size)].push_back(a[i]);
   }
   int i = 0;
   for (auto& bucket : buckets)
   {
      for (auto el : bucket)
      {
         a[i++] = el;
      }
   }

   // A common optimization is to put the unsorted elements of the buckets back in the original array first,
   // then run insertion sort over the complete array; because insertion sort's runtime is based on how far each element is from its final position,
   // the number of comparisons remains relatively small, and the memory hierarchy is better exploited by storing the list contiguously in memory

   insertsort(a, N);
}
