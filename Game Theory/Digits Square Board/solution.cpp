/*
 * HackerRank - Digits Square Board
 * https://www.hackerrank.com/challenges/digits-square-board-1
 * Author: Rafal Kozik
 */

#include <iostream>
#include <cstring>
#include <vector>

#define LOG(x) std::cout << x << std::endl

struct Subgame
{
    int sx{0};
    int sy{0};
    int ex{0};
    int ey{0};
    bool valid{false};
    Subgame(int sx, int sy, int ex, int ey) : sx(sx), sy(sy), ex(ex), ey(ey) { }
};

class Board
{
public:

    std::vector<std::vector<int>> board;
    std::vector<bool> primes{false, false, true, true, false, true, false, true, false, false};

    Board(int size) : board(size, std::vector<int>(size)) { }

    bool is_valid(Subgame subgame)
    {
        int count = 0;
        int has_non_prime = false;
        for (int x = subgame.sx; x <= subgame.ex; ++x)
        {
            for (int y = subgame.sy; y <= subgame.ey; ++y)
            {
                ++count;
                has_non_prime = has_non_prime || !primes[board[x][y]];
                if (has_non_prime && count > 1)
                {
                    return true;
                }
            }
        }
        return false;
    }
};

int mex(std::vector<int> set)
{
    int i = 0;
    while (set[i] == 1)
    {
        ++i;
    }
    return i;
}

int calculate_grundy_number(Board& board, Subgame subgame, int dp[30][30][30][30])
{
    if (dp[subgame.sx][subgame.sy][subgame.ex][subgame.ey] == -1)
    {
        std::vector<int> grundy_numbers(2 * board.board.size());
        if (board.is_valid(subgame))
        {
            int width = subgame.ex - subgame.sx + 1;
            int height = subgame.ey - subgame.sy + 1;
            for (int w = 1; w < width; ++w)
            {
                auto subgame1 = subgame;
                auto subgame2 = subgame;
                subgame1.ex = subgame.sx + w - 1;
                subgame2.sx = subgame.sx + w;
                auto result1 = calculate_grundy_number(board, subgame1, dp);
                auto result2 = calculate_grundy_number(board, subgame2, dp);
                grundy_numbers[result1 ^ result2] = 1;
            }
            for (int h = 1; h < height; ++h)
            {
                auto subgame1 = subgame;
                auto subgame2 = subgame;
                subgame1.ey = subgame.sy + h - 1;
                subgame2.sy = subgame.sy + h;
                auto result1 = calculate_grundy_number(board, subgame1, dp);
                auto result2 = calculate_grundy_number(board, subgame2, dp);
                grundy_numbers[result1 ^ result2] = 1;
            }
        }
        dp[subgame.sx][subgame.sy][subgame.ex][subgame.ey] = mex(grundy_numbers);
    }
    return dp[subgame.sx][subgame.sy][subgame.ex][subgame.ey];
}

int main()
{
    int T;
    std::cin >> T;
    int dp[30][30][30][30];
    while (T--)
    {
        int N;
        std::cin >> N;
        Board board(N);
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                std::cin >> board.board[i][j];
            }
        }
        std::memset(dp, ~0, sizeof(dp));
        auto grundy_number = calculate_grundy_number(board, Subgame(0, 0, N - 1, N - 1), dp);
        LOG((grundy_number == 0 ? "Second" : "First"));
    }
}

