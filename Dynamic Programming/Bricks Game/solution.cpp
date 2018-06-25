/*
 * HackerRank - Bricks Game
 * https://www.hackerrank.com/challenges/play-game/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl

int64_t play(std::vector<int64_t>& bricks, std::vector<int64_t[2]>& dp, uint32_t position, bool myself)
{
    if (position >= bricks.size())
    {
        return 0;
    }
    if (dp[position][myself] == 0)
    {
        auto score = myself ? std::numeric_limits<int64_t>::min() : std::numeric_limits<int64_t>::max();
        auto taken = 0;
        for (auto take = 0; take < 3; ++take)
        {
            if (position + take < bricks.size())
            {
                taken += bricks[position + take];
                if (myself)
                {
                    score = std::max(score, play(bricks, dp, position + take + 1, false) + taken);
                }
                else
                {
                    score = std::min(score, play(bricks, dp, position + take + 1, true) - taken);
                }
            }
        }
        dp[position][myself] = score;
    }
    return dp[position][myself];
}

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int n;
        std::cin >> n;
        int64_t sum = 0;
        std::vector<int64_t> bricks(n);
        std::vector<int64_t[2]> dp(n);
        for (auto i = 0; i < n; ++i)
        {
            std::cin >> bricks[i];
            sum += bricks[i];
        }
        auto score = play(bricks, dp, 0, true);
        LOG((sum + score) / 2);
    }
}

