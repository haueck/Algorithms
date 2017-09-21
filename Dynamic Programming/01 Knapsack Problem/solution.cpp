/*
 * GeeksForGeeks - 0 - 1 Knapsack Problem
 * http://practice.geeksforgeeks.org/problems/0-1-knapsack-problem/0
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

struct Item
{
    int weight{0};
    int value{0};
};

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N, W;
        std::cin >> N >> W;
        std::vector<int> dp(W + 1);
        std::vector<std::vector<bool>> used(W + 1, std::vector<bool>(N));
        std::vector<Item> items(N);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> items[i].value;
        }
        for (int i = 0; i < N; ++i)
        {
            std::cin >> items[i].weight;
        }
        for (int capacity = 1; capacity <= W; ++capacity)
        {
            // Maximum value if we don't add any new items for this capacity
            // If we do not any items, the solution is the same as for a lower capacity
            int value = dp[capacity - 1];
            int added = -1;
            for (int item = 0; item < N; ++item)
            {
                auto capacity_left = capacity - items[item].weight;
                if (capacity_left >= 0)
                {
                    if (!used[capacity_left][item])
                    {
                        if (dp[capacity_left] + items[item].value > value)
                        {
                            value = dp[capacity_left] + items[item].value;
                            added = item;
                        }
                    }
                }
            }
            if (added < 0)
            {
                // For this capacity we don't add any new items
                // So simply copy the solution for a lower capacity
                dp[capacity] = dp[capacity - 1];
                used[capacity] = used[capacity - 1];
            }
            else
            {
                dp[capacity] = value;
                used[capacity] = used[capacity - items[added].weight];
                used[capacity][added] = true;
            }
        }
        LOG(dp[W]);
    }
}

