/*
 * HackerRank - Counter Game
 * Bit Manipulation
 * https://www.hackerrank.com/challenges/counter-game
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T = 0;
    uint64_t N = 0, one = 1;
    std::cin >> T;
    for (int i = 0; i < T; ++i)
    {
      std::cin >> N;
      bool louise = true;
      while (N > one)
      {
        if ((N & (N - one)) == 0)
        {
          // Power of two, divide by 2
          N >>= 1;
        }
        else
        {
          // Subtract largest and smaller than N power of 2
          int position = 1;
          while ((N >> position) != one)
          {
            ++position;
          }
          N -= N & (one << position);
        }
        louise = !louise;
      }
      LOG((louise ? "Richard" : "Louise"));
    }
    return 0;
}
