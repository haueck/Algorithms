/*
 * HackerRank - Knapsack
 * https://www.hackerrank.com/challenges/unbounded-knapsack
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N, K;
        std::cin >> N >> K;
        std::vector<int> data(N);
        std::vector<bool> is_this_sum_possible(K + 1);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> data[i];
        }
        is_this_sum_possible[0] = true;
        std::sort(data.begin(), data.end());
        for (int sum = 1; sum <= K; ++sum)
        {
            for (int i = 0; i < N; ++i)
            {
                if (data[i] > sum)
                {
                    break;
                }
                else if (sum - data[i] >= 0)
                {
                    if (is_this_sum_possible[sum - data[i]])
                    {
                        is_this_sum_possible[sum] = true;
                        break;
                    }
                }
            }
        }
        for (int i = K; i >= 0; --i)
        {
            if (is_this_sum_possible[i])
            {
                LOG(i);
                break;
            }
        }
    }
}

