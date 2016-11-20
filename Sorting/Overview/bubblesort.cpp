#include <iostream>

void bubblesort(int* a, int N)
{
   bool swapped = true;
   while (swapped)
   {
      swapped = false;
      for (int i = 0; i < N - 1; ++i)
      {
         if (a[i] > a[i + 1])
         {
            swapped = true;
            int temp = a[i];
            a[i] = a[i + 1];
            a[i + 1] = temp;
         }
      }
   }
}
