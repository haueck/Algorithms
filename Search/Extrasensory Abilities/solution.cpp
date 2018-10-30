/*
 * Codeforces - Dwarves, Hats and Extrasensory Abilities
 * http://codeforces.com/contest/1064/problem/E
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

bool is_white()
{
    std::string color;
    std::cin >> color;
    return color == "white";
}

int main()
{
    int n;
    std::cin >> n;
    LOG("1 1");
    auto white_on_the_left = is_white();
    // There are two lines going through (0,0) - left and right
    // The line that we look for lies between those two lines
    auto left_line_slope = 1.0;
    auto right_line_slope = 0.0;
    for (int i = 1; i < n; ++i)
    {
        // Point (x,y) lies on a line that bisects an angle created by left and right line
        int x = 1 << i;
        int y = 0.5 + (left_line_slope * x + right_line_slope * x) / 2;
        LOG(x << " " << y);
        if (is_white() ^ white_on_the_left)
        {
            right_line_slope = static_cast<double>(y) / x;
        }
        else
        {
            left_line_slope = static_cast<double>(y) / x;
        }
    }
    int x = 1e9;
    int y = 0.5 + (left_line_slope * x + right_line_slope * x) / 2;
    LOG("0 0 " << x << " " << y);
}

