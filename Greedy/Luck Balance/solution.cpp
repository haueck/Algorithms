/*
 * HackerRank - Luck Balance
 * Greedy
 * https://www.hackerrank.com/challenges/luck-balance
 * Author: Rafal Kozik
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, K, luck = 0;
    std::cin >> N >> K;
    std::vector<int> contests;
    for (int i = 0; i < N; ++i)
    {
        int L, T;
        std::cin >> L >> T;
        if (T == 0)
        {
            luck += L;
        }
        else
        {
            contests.push_back(L);
        }
    }
    std::sort(contests.begin(), contests.end());
    int won = static_cast<int>(contests.size()) - K < 0 ? 0 : contests.size() - K;
    luck -= std::accumulate(contests.begin(), contests.begin() + won, 0);
    luck += std::accumulate(contests.begin() + won, contests.end(), 0);
    LOG(luck);
    return 0;
}

