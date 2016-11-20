/*
 * HackerRank - The Coin Change Problem
 * Dynamic Programming
 * https://www.hackerrank.com/challenges/coin-change
 * Author: Rafal Kozik
 */

#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

int sth(int n, std::vector<int>& v, std::vector<int>& coins)
{
    if (n < 0)
    {
        return std::numeric_limits<int>::max();
    }
    if (v[n] >= 0)
    {
        return v[n];
    }
    int min = std::numeric_limits<int>::max();
    for (auto coin : coins)
    {
        int s = sth(n - coin, v, coins);
        if (s < min - 1)
        {
            min = s + 1;
        }
    }
    v[n] = min;
    return v[n];
}

TEST(Coins, Test)
{
    std::vector<int> coins1{1, 3, 5};
    std::vector<int> coins2{3, 5};
    std::vector<int> v(11 + 1, -1);
    v[0] = 0;
    EXPECT_EQ(3, sth(11, v, coins1));
    std::vector<int> v1(11 + 1, -1);
    v1[0] = 0;
    EXPECT_EQ(3, sth(11, v1, coins2));
}
