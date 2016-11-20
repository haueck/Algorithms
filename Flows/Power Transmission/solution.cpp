/*
 * UVa Online Judge - Power Transmission
 * Ford-Fulkerson
 * https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1271
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

int dfs(int current, int target, std::vector<std::vector<int>>& matrix, std::vector<int>& path, int N)
{
    auto& c = matrix[current];
    int start = 1;
    int stop = N;
    if (current <= N && current > 0)
    {
        start = N + 1;
        stop = 2 * N;
    }
    else if (c[2 * N + 1] > 0)
    {
        return std::numeric_limits<int>::max();
    }
    for (int i = start; i <= stop; ++i)
    {
        if (c[i] > 0 && matrix[2 * N + 1][i] == 0)
        {
            matrix[2 * N + 1][i] = 1;
            if (int max = dfs(i, target, matrix, path, N))
            {
                path.push_back(i);
                return c[i] < max ? c[i] : max;
            }
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    while (true)
    {
        int N, M, B, D;
        if (feof(stdin) || scanf("%d", &N) != 1)
        {
            break;
        }
        std::vector<std::vector<int>> matrix(2 * N + 2, std::vector<int>(2 * N + 2, 0));
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d", &matrix[i][N + i]);
        }
        scanf("%d", &M);
        for (int i = 0; i < M; ++i)
        {
            int from, to, capacity;
            scanf("%d %d %d", &from, &to, &capacity);
            matrix[N + from][to] = capacity;
        }
        scanf("%d %d", &B, &D);
        for (int i = 0; i < B; ++i)
        {
            int entry;
            scanf("%d", &entry);
            matrix[0][entry] = std::numeric_limits<int>::max();
        }
        for (int i = 0; i < D; ++i)
        {
            int entry;
            scanf("%d", &entry);
            matrix[N + entry][2 * N + 1] = std::numeric_limits<int>::max();
        }
        int result = 0;
        std::vector<int> path;
        while (true)
        {
            int max = dfs(0, 2 * N + 1, matrix, path, N);
            if (max == 0)
            {
                break;
            }
            for (int i = 1; i <= 2 * N; ++i)
            {
                matrix[2 * N + 1][i] = 0;
            }
            int previous = 0;
            for (int i = path.size() - 1; i >= 0; --i)
            {
                int p = path[i];
                matrix[previous][p] -= max;
                matrix[p][previous] += max;
                previous = p;
            }
            result += max;
            path.clear();
        }
        LOG(result);
    }
    return 0;
}

