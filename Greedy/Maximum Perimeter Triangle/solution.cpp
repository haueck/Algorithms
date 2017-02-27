/*
 * HackerRank - Maximum Perimeter Triangle
 * https://www.hackerrank.com/challenges/maximum-perimeter-triangle
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    std::vector<int> sticks(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> sticks[i];
    }
    std::sort(sticks.begin(), sticks.end(), std::greater<int>());
    for (int i = 0; i < N - 2; ++i)
    {
        // If stick i is too long to form a triangle,
        // we can skip. Other sticks are even shorter
        // than sticks i + 1 and i + 2 so there is no
        // need to check them. On the other hand, if
        // stick i is ok, then we found the triangle
        // with maximum perimeter.
        if (sticks[i] < sticks[i + 1] + sticks[i + 2])
        {
            LOG(sticks[i + 2] << " " << sticks[i + 1] << " " << sticks[i]);
            return 0;
        }
    }
    LOG(-1);
}

