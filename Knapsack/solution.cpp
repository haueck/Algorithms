/*
 * HackerRank - Knapsack
 * Dynamic Programming
 * https://www.hackerrank.com/contests/bits-goa-day-3/challenges/knapsack-problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

void knapsack(const std::vector<int>& size, const std::vector<int>& value, std::vector<std::vector<int>>& helper, int i, int j)
{
    int idx = i - 1;
    if (size[idx] <= j)
    {
        int newval = value[idx] + helper[i - 1][j - size[idx]];
        if (newval > helper[i - 1][j])
        {
            helper[i][j] = newval;
        }
        else
        {
            helper[i][j] = helper[i - 1][j];
        }
    }
    else
    {
        helper[i][j] = helper[i - 1][j];
    }
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N = 0, S = 0;
    std::cin >> S >> N;
    std::vector<int> size(N, 0);
    std::vector<int> value(N, 0);
    std::vector<std::vector<int>> helper(N + 1, std::vector<int>(S + 1, 0));

    for (int i = 0; i < N; ++i)
    {
        std::cin >> size[i];
        std::cin >> value[i];
    }

    for (int i = 1; i < N + 1; ++i)
    {
        for (int j = 1; j < S + 1; ++j)
        {
            knapsack(size, value, helper, i, j);
        }
    }

    LOG(helper[N][S]);

    return 0;
}

