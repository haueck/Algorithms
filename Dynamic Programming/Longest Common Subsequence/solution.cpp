/*
 * HackerRank - The Longest Common Subsequence
 * https://www.hackerrank.com/challenges/dynamic-programming-classics-the-longest-common-subsequence/problem
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>

int lcs(std::vector<int>& A, std::vector<int>& B, std::vector<std::vector<int>>& dp, int i, int j)
{
    if (i < 0 || j < 0)
    {
        return 0;
    }
    if (dp[i][j] == -1)
    {
        if (A[i] == B[j])
        {
            dp[i][j] = lcs(A, B, dp, i - 1, j - 1) + 1;
        }
        else
        {
            dp[i][j] = std::max(lcs(A, B, dp, i - 1, j), lcs(A, B, dp, i, j - 1));
        }
    }
    return dp[i][j];
}

void print(std::vector<int>& A, std::vector<int>& B, std::vector<std::vector<int>>& dp, int i, int j)
{
    if (A[i] == B[j])
    {
        if (dp[i][j] > 1)
        {
            print(A, B, dp, i - 1, j - 1);
        }
        std::cout << A[i] << " ";
    }
    else if (i == 0)
    {
        print(A, B, dp, i, j - 1);
    }
    else if (j == 0)
    {
        print(A, B, dp, i - 1, j);
    }
    else if (dp[i - 1][j] > dp[i][j - 1])
    {
        print(A, B, dp, i - 1, j);
    }
    else
    {
        print(A, B, dp, i, j - 1);
    }
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> A(n), B(m);
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, -1));
    for (int i = 0; i < n; ++i)
    {
        std::cin >> A[i];
    }
    for (int i = 0; i < m; ++i)
    {
        std::cin >> B[i];
    }
    lcs(A, B, dp, n - 1, m - 1);
    print(A, B, dp, n - 1, m - 1);
    std::cout << std::endl;
}

