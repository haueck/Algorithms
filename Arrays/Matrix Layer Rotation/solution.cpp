/*
 * Matrix Layer Rotation
 * https://www.hackerrank.com/challenges/matrix-rotation-algo/problem
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

std::pair<int,int> find_next(int M, int N, int r)
{
    int row = 0;
    int column = 0;
    if (r < M)
    {
        return { r, column };
    }
    else
    {
        r -= M - 1;
        row = M - 1;
    }
    if (r < N)
    {
        return { row, r };
    }
    else
    {
        r -= N - 1;
        column = N - 1;
    }
    if (row - r >= 0)
    {
        return { row - r, column };
    }
    else
    {
        r -= M - 1;
        row = 0;
    }
    return { row, column - r };
}

int main()
{
    int M, N, rr;
    std::cin >> M >> N >> rr;
    std::vector<std::vector<int>> matrix(M, std::vector<int>(N));
    for (auto& row : matrix)
    {
        for (auto& cell : row)
        {
            std::cin >> cell;
        }
    }
    int offset = 0;
    while (M > 0 && N > 0)
    {
        int length = 2 * M + 2 * N - 4;
        int r = rr % length;
        int steps = std::gcd(length, r);
        for (auto step = 0; step < steps; ++step)
        {
            auto start = find_next(M, N, step);
            auto value = matrix[offset + start.first][offset + start.second];
            auto counter = 1;
            while (true)
            {
                auto next = find_next(M, N, (step + counter * r) % length);
                std::swap(value, matrix[offset + next.first][offset + next.second]);
                if (next == start)
                {
                    break;
                }
                ++counter;
            }
        }
        ++offset;
        M -= 2;
        N -= 2;
    }
    for (auto& row : matrix)
    {
        for (auto cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

