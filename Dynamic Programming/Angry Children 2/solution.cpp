/*
 * HackerRank - Angry Children 2
 * https://www.hackerrank.com/challenges/angry-children-2
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int N, K;
    std::cin >> N >> K;
    std::vector<uint64_t> candies(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> candies[i];
    }
    std::sort(candies.begin(), candies.end());
    std::vector<uint64_t> acc(N + 1);
    acc[1] = candies[0];
    for (int i = 2; i < N + 1; i++)
    {
        acc[i] = acc[i - 1] + candies[i - 1];
    }
    uint64_t unfairness = 0;
    for (int k = 1; k < K; k++)
    {
        unfairness += candies[k] * k - acc[k];
    }
    auto result = unfairness;
    for (int i = K; i < N; i++)
    {
        unfairness += K * candies[i] - (acc[i] - acc[i - K]);
        unfairness -= (acc[i + 1] - acc[i - K + 1]) - K * candies[i - K];
        result = std::min(result, unfairness);
    }
    LOG(result);
}

