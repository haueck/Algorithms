/*
 * HackerRank - Fair Cut
 * https://www.hackerrank.com/challenges/fair-cut
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int k, n;
    std::cin >> n >> k;
    std::vector<int64_t> data(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data[i];
    }
    std::sort(data.begin(), data.end());
    /*
     * We will process one integer at the time and decide whether it sould be assigned to Lu or Li.
     * First index indicates how many integers have been processed.
     * Second index indicates how many integers has been assigned to Li.
     */
    std::vector<std::vector<int64_t>> dp(n + 1, std::vector<int64_t>(k + 2, std::numeric_limits<int64_t>::max()));
    /*
     * If we didn't assign any integers, then unfairness is 0.
     */
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i)
    {
        /*
         * j is equal to the number of integers assigned to Li.
         * Li wants at most k integers, so j is limited by k.
         * If Li wants k integers, then Lu will have n - k integers.
         * For example, n = 10, k = 5 and we are assigning 7th integer,
         * then j cannot be lower than 7 - (10 - 5) = 2.
         */
        for (int j = std::max(0, i - (n - k)); j <= std::min(i, k); ++j)
        {
            /*
             * Case 1 - assign ith integer to Lu.
             *
             * Let's say Li has two numbers 1, 2 and we are assigning 4.
             * So to calculate new unfairness, first we need to add 2 * 4,
             * bacause (4 - 1) + (4 - 2) = 2 * 4 - (1 + 2), ignoring 1 + 2 for the time being.
             */
            auto assign_to_lu = data[i] * j;
            /*
             * If Li has j integers now, it means that he will have k - j more in the future.
             * It also means that in the future we will subtract current integer that k - j times.
             * For example, Li has two integers but he wants 5. So for the remaining 3 we will
             * calculate unfairness like this (x - 4) + (y - 4) + (z - 4). It doesn't matter
             * what those integers are, it only matters that we are assigning 4 now and Li still
             * needs 3 more integers.
             */
            assign_to_lu -= data[i] * (k - j);
            /*
             * Finally, take minimal unfairness for the state from which we can get to the state,
             * where ith integers is assigned to Lu and Li has j integers.
             */
            assign_to_lu += dp[i][j];
            /*
             * There are many paths that lead to this state, check if this one has lower unfairness.
             */
            if (assign_to_lu < dp[i + 1][j])
            {
                 dp[i + 1][j] = assign_to_lu;
            }

            /*
             * Case 2 - assign ith integer to Li.
             *
             * If Li has j integers, then Lu has i - j. So the current integer data[i]
             * has to be added i - j times. For example, we are assigning 4th integer and
             * Li has 1 integer. Unfairness will change by (4 - x) + (4 - y) = 2 * 4 - (x + y).
             * Once again it doesn't matter what integers Lu has, only the number of those
             * integers counts.
             */
            auto assign_to_li = data[i] * (i - j);
            /*
             * If Lu has i - j integers now, it means that he will have n - k - (i - j) more in the future.
             * Let's subtract current integer from all those future integers.
             */
            assign_to_li -= data[i] * (n - k - (i - j));
            /*
             * Finally, take minimal unfairness for the state from which we can get to the state,
             * where ith integers is assigned to Li and Li has already j integers.
             */
            assign_to_li += dp[i][j];
            /*
             * There are many paths that lead to this state, check if this one has lower unfairness.
             */
            if (assign_to_li < dp[i + 1][j + 1])
            {
                 dp[i + 1][j + 1] = assign_to_li;
            }
        }
    }
    LOG(dp[n][k]);
}
