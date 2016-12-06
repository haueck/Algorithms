/*
 * HackerRank - Flipping The Matrix
 * Constructive algorithms
 * https://www.hackerrank.com/challenges/flipping-the-matrix
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T = 0;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int N = 0;
        std::cin >> N;
        std::vector<std::vector<int>> matrix(N + N, std::vector<int>(N + N, 0));
        for (int y = 0; y < N + N; ++y)
        {
            for (int x = 0; x < N + N; ++x)
            {
                std::cin >> matrix[x][y];
            }
        }
        int result = 0;
        for (int y = 0; y < N; ++y)
        {
            for (int x = 0; x < N; ++x)
            {
                auto max1 = std::max(matrix[x][N + N - 1 - y], matrix[N + N - 1 - x][y]);
                auto max2 = std::max(matrix[x][y], matrix[N + N - 1 - x][N + N - 1 - y]);
                result += std::max(max1, max2);
            }
        }
        LOG(result);
    }
    return 0;
}

