/*
 *
 *
 * Author: Rafal Kozik
 */

#include <set>
#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int calculate_mex(std::set<int> set)
{
    int mex = 0;
    for (auto value : set)
    {
        if (value != mex)
        {
            break;
        }
        ++mex;
    }
    return mex;
}

int calculate_nimber(std::vector<std::vector<int>>& chessboard, int x, int y)
{
    if (chessboard[x][y] == -1)
    {
        std::set<int> set;
        std::vector<std::pair<int,int>> deltas{ {-2, 1}, {-2, -1}, {1, -2}, {-1, -2} };
        for (auto delta : deltas)
        {
            int new_x = x + delta.first;
            int new_y = y + delta.second;
            if (new_x > 0 && new_x <= 15 && new_y > 0 && new_y <= 15)
            {
                set.insert(calculate_nimber(chessboard, new_x, new_y));
            }
        }
        chessboard[x][y] = calculate_mex(set);
    }
    return chessboard[x][y];
}

void calculate_nimbers(std::vector<std::vector<int>>& chessboard)
{
    chessboard[1][1] = 0;
    chessboard[1][2] = 0;
    chessboard[2][1] = 0;
    chessboard[2][2] = 0;
    for (int x = 1; x <= 15; ++x)
    {
        for (int y = 1; y <= 15; ++y)
        {
            calculate_nimber(chessboard, x, y);
        }
    }
}

int main()
{
    int T;
    std::cin >> T;
    std::vector<std::vector<int>> chessboard(16, std::vector<int>(16, -1));
    calculate_nimbers(chessboard);
    while (T--)
    {
        int k;
        std::cin >> k;
        int result = 0;
        for (int i = 0; i < k; ++i)
        {
            int x, y;
            std::cin >> x >> y;
            result ^= chessboard[x][y];
        }
        LOG((result == 0 ? "Second" : "First"));
    }
}

