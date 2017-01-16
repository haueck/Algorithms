/*
 * HackerRank - A Chessboard Game
 * Game Theory
 * https://www.hackerrank.com/challenges/a-chessboard-game-1
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <utility>

#define LOG(x) std::cout << x << std::endl;

class Position
{
public:
    int x;
    int y;

    Position(int x, int y) : x(x), y(y) { }

    bool is_valid()
    {
        if (x < 1 || x > 15)
        {
            return false;
        }
        if (y < 1 || y > 15)
        {
            return false;
        }
        return true;
    }
};

std::vector<Position> get_moves(Position pos)
{
    auto result = std::vector<Position>();
    auto moves = std::vector<std::pair<int,int>>{ {-2, 1}, {-2, -1}, {1, -2}, {-1, -2} };
    for (auto& move : moves)
    {
        Position p(pos.x + move.first, pos.y + move.second);
        if (p.is_valid())
        {
            result.push_back(p);
        }
    }
    return result;
}

bool is_winner(Position pos)
{
    auto moves = get_moves(pos);
    for (auto move : moves)
    {
        if (!is_winner(move))
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int x, y;
        std::cin >> x >> y;
        Position start(x, y);
        LOG((is_winner(start) ? "First" : "Second"));
    }
    return 0;
}
