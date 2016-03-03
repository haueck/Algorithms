/*
 * HackerRank - 2D Arrays - DS
 * Arrays
 * https://www.hackerrank.com/challenges/2d-array
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    const int N = 6;
    int result = std::numeric_limits<int>::min();
    std::vector<std::vector<int>> input(N, std::vector<int>(N, 0));
    std::vector<std::pair<int,int>> hourglass{ {0, 0}, {0, 1}, {0, 2}, {1, 1}, {2, 0}, {2, 1}, {2, 2} };

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            (void)scanf("%d", &input[i][j]);
        }
    }

    for (int i = 0; i < N - 2; ++i)
    {
        for (int j = 0; j < N - 2; ++j)
        {
            int sum = 0;
            for (auto p : hourglass)
            {
                sum += input[i + p.first][j + p.second];
            }
            if (sum > result)
            {
                result = sum;
            }
        }
    }

    LOG(result);

    return 0;
}

