/*
 * HackerRank - The Coin Change Problem
 * Dynamic Programming
 * https://www.hackerrank.com/challenges/coin-change
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

/*
 *        {1,2,3},4
 *        /       \
 *   {1,2},4     {1,2,3},(4-3=1)
 *   /     \          ....
 * {1},4  {1,2},2
 *  ...   /     \
 *     {1},2   ({1,2},0)=1
 *      ...
 */


uint64_t change(int amount, int n, const std::vector<int>& coins, std::vector<std::vector<uint64_t>>& cache)
{
    // There is always one solution when amount is equal to 0 - do not include any coins
    if (amount == 0)
    {
        return 1;
    }
    if (n <= 0 || amount < 0)
    {
        return 0;
    }
    if (cache[amount][n] == std::numeric_limits<uint64_t>::max())
    {
        // Solutions without n-th coin plus solutions with at least one n-th coin
        cache[amount][n] = change(amount, n - 1, coins, cache) + change(amount - coins[n - 1], n, coins, cache);
    }
    return cache[amount][n];
}

int main()
{
    std::ios::sync_with_stdio(false);
    int N = 0, M = 0;
    std::cin >> N >> M;
    std::vector<int> coins(M, 0);
    std::vector<std::vector<uint64_t>> cache(N + 1, std::vector<uint64_t>(M + 1, std::numeric_limits<uint64_t>::max()));
    for (int i = 0; i < M; ++i)
    {
        std::cin >> coins[i];
    }
    LOG(change(N, M, coins, cache));
    return 0;
}
