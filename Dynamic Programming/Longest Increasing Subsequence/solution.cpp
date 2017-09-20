/*
 * GeeksForGeeks - Longest Increasing Subsequence
 * http://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        std::cin >> n;
        std::vector<int> data(n);
        std::vector<int> dp(n);
        for (int i = 0; i < n; ++i)
        {
            std::cin >> data[i];
        }
        int result = 0;
        for (int i = 0; i < n; ++i)
        {
            auto max = 0;
            for (int j = 0; j < i; ++j)
            {
                if (data[j] < data[i])
                {
                    max = std::max(max, dp[j]);
                }
            }
            dp[i] = max + 1;
            result = std::max(result, dp[i]);
        }
        LOG(result);
    }
}

