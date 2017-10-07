/*
 * Collatz Sequence Sum
 * https://www.hackerrank.com/contests/optimization-oct17/challenges/collatz-sequence-sum
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

int collatzSequenceLen(int n, std::vector<int>& dp)
{
    if (dp[n] == 0)
    {
        if (n & 1)
        {
            dp[n] = 1 + collatzSequenceLen(3 * n + 1, dp);
        }
        else
        {
            dp[n] = 1 + collatzSequenceLen(n / 2, dp);
        }
    }
    return dp[n];
}

int collatzSequenceSum(int T, int A, int B)
{
    int n = 0;
    int result = 0;
    int last_computed = 0;
    std::vector<int> dp(8153621);
    std::vector<std::pair<int,int>> computed(5003);
    dp[1] = 1;
    while (T--)
    {
        n = (A * n + B) % 5003;
        if (n > last_computed)
        {
            for (int k = last_computed + 1; k <= n; ++k)
            {
                int cur_len = collatzSequenceLen(k, dp);
                if (cur_len >= computed[k - 1].first)
                {
                    computed[k].first = cur_len;
                    computed[k].second = k;
                }
                else
                {
                    computed[k] = computed[k - 1];
                }
            }
            last_computed = n;
        }
        result += computed[n].second;
    }
    return result;
}

int main()
{
    std::cout << collatzSequenceSum(3, 1, 4) << std::endl;
}
