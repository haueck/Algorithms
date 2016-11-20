#include "gtest/gtest.h"
#include "sorting.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <functional>
#include <chrono>

#define SIZE 1000
#define MAX 300

class SortTest : public ::testing::Test
{
protected:
   static const int N{SIZE};
   int a[SIZE];
   int b[SIZE];
   std::default_random_engine generator;
   std::uniform_int_distribution<int> distribution;

   SortTest() : generator(std::chrono::high_resolution_clock::now().time_since_epoch().count()), distribution(0, MAX) { };

   virtual void SetUp()
   {
      auto dice = std::bind(distribution, generator);
      for (int i = 0; i < N; ++i)
      {
         a[i] = dice();
         b[i] = a[i];
      }
      std::sort(std::begin(b), std::end(b));
   };

   virtual void TearDown() {};

   void compare()
   {
      for (int i = 0; i < N; ++i)
      {
         ASSERT_EQ(a[i], b[i]);
      }
   };

   void dump()
   {
      for (int i = 0; i < N; ++i)
      {
         std::cout << a[i] << " ";
      }
      std::cout << std::endl;
   };
};

TEST_F(SortTest, Quicksort)
{
    quicksort(a, N);
    compare();
}

TEST_F(SortTest, Insertsort)
{
    insertsort(a, N);
    compare();
}

TEST_F(SortTest, BubbleSort)
{
    bubblesort(a, N);
    compare();
}

TEST_F(SortTest, MergeSort)
{
    mergesort(a, N);
    compare();
}

TEST_F(SortTest, BucketSort)
{
    bucketsort(a, N, MAX, 7);
    compare();
}

TEST_F(SortTest, RadixSort)
{
    radixsort(a, N);
    compare();
}

TEST_F(SortTest, HeapSort)
{
    heapsort(a, N);
    compare();
}

