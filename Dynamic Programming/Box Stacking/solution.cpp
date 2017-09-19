/*
 * GeeksForGeeks - Box Stacking
 * http://practice.geeksforgeeks.org/problems/box-stacking/1
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <tuple>

#define LOG(x) std::cout << x << std::endl

std::tuple<int,int,int> get_dimensions(int height[], int width[], int length[], int i, int pose)
{
    if (pose == 0) return std::make_tuple(height[i], width[i], length[i]);
    else if (pose == 1) return std::make_tuple(height[i], length[i], width[i]);
    else if (pose == 2) return std::make_tuple(width[i], height[i], length[i]);
    else if (pose == 3) return std::make_tuple(width[i], length[i], height[i]);
    else if (pose == 4) return std::make_tuple(length[i], width[i], height[i]);
    else return std::make_tuple(length[i], height[i], width[i]);
}

int count(int height[], int width[], int length[], int n, int box, int pose, std::vector<int[6]>& dp)
{
    if (dp[box][pose] == 0)
    {
        auto current = get_dimensions(height, width, length, box, pose);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                auto next = get_dimensions(height, width, length, i, j);
                if (std::get<0>(next) < std::get<0>(current) && std::get<1>(next) < std::get<1>(current))
                {
                    dp[box][pose] = std::max(dp[box][pose], count(height, width, length, n, i, j, dp));
                }
            }
        }
        dp[box][pose] += std::get<2>(current);
    }
    return dp[box][pose];
}

int maxHeight(int height[], int width[], int length[], int n)
{
    int max = 0;
    std::vector<int[6]> dp(n);
    for (int box = 0; box < n; ++box)
    {
        for (int pose = 0; pose < 6; ++pose)
        {
            max = std::max(max, count(height, width, length, n, box, pose, dp));
        }
    }
    return max;
}

int main()
{
    int height1[4] = { 4, 1, 4, 10 };
    int width1[4] = { 6, 2, 5, 12 };
    int length1[4] = { 7, 3, 6, 32 };
    LOG(maxHeight(height1, width1, length1, 4));
    int height2[4] = { 1, 4, 3 };
    int width2[4] = { 2, 5, 4 };
    int length2[4] = { 3, 6, 1 };
    LOG(maxHeight(height2, width2, length2, 3));
}

