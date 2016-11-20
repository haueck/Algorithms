#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

/*
 * A*Search
 */


class Board
{
public:
    std::vector<std::vector<int>> board;
    std::size_t fp{0};
    int ei{0}, ej{0}, depth{0};

    Board(std::vector<std::vector<int>> b) : board(b)
    {
        int m = 1;
        for (auto i = 0u; i < board.size(); ++i)
        {
            for (auto j = 0u; j < board[i].size(); ++j)
            {
                if (board[i][j] == 0)
                {
                    ei = i;
                    ej = j;
                }
                fp += m * board[i][j];
                m *= 10;
            }
        }
    }

    int evaluate(Board goal) const
    {
        auto misplaced = 0;
        for (auto i = 0u; i < board.size(); ++i)
        {
            for (auto j = 0u; j < board[i].size(); ++j)
            {
                if (board[i][j] != 0 && board[i][j] != goal.board[i][j])
                {
                    ++misplaced;
                }
            }
        }
        return misplaced + depth;
    }

    Board move(int i, int j)
    {
        auto copy = board;
        copy[ei][ej] = copy[i][j];
        copy[i][j] = 0;
        return copy;
    }

    bool valid(int i, int j)
    {
        if (i > 2 || i < 0 || j > 2 || j < 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    std::vector<Board> moves()
    {
        std::vector<Board> legit;
        if (valid(ei + 1, ej))
        {
            legit.push_back(move(ei + 1, ej));
        }
        if (valid(ei - 1, ej))
        {
            legit.push_back(move(ei - 1, ej));
        }
        if (valid(ei, ej + 1))
        {
            legit.push_back(move(ei, ej + 1));
        }
        if (valid(ei, ej - 1))
        {
            legit.push_back(move(ei, ej - 1));
        }
        return legit;
    }

    bool operator==(const Board& rhs) const
    {
        return fp == rhs.fp;
    }

    void dump()
    {
        for (auto i = 0u; i < board.size(); ++i)
        {
            std::cout << board[i][0] << board[i][1] << board[i][2] << std::endl;
        }
        std::cout << std::endl;
    }
};

namespace std
{
    template<>
    struct hash<Board>
    {
        size_t operator()(const Board& board) const
        {
            return board.fp;
        }
    };
}

Board minimal(std::unordered_set<Board>& opened, Board goal)
{
    std::unordered_set<Board>::iterator found;
    int minimal = std::numeric_limits<int>::max();
    for (auto it = opened.begin(); it != opened.end(); ++it)
    {
        int value = it->evaluate(goal);
        if (value < minimal)
        {
            found = it;
            minimal = value;
        }
    }
    Board retval = *found;
    opened.erase(found);
    return retval;
}

int asearch(Board current, Board goal)
{
    std::unordered_set<Board> opened;
    std::unordered_set<Board> closed;
    opened.insert(current);
    while (!opened.empty())
    {
        Board current = minimal(opened, goal);
        closed.insert(current);
        if (current == goal)
        {
            return current.depth;
        }
        for (auto move : current.moves())
        {
            move.depth = current.depth + 1;
            auto found = closed.find(move);
            if (found == closed.end())
            {
                opened.insert(move);
            }
            else if (move.evaluate(goal) < found->evaluate(goal))
            {
                closed.erase(found);
                opened.insert(move);
            }
        }
    }
    return 0;
}

TEST(BestFirstSearch, Test1)
{
    Board start({ { 8, 1, 3 }, { 0, 4, 5 }, { 2, 7, 6 } });
    Board goal ({ { 1, 2, 3 }, { 8, 0, 4 }, { 7, 6, 5 } });
    EXPECT_EQ(asearch(start, goal), 9);
}

TEST(BestFirstSearch, Test2)
{
    Board start({ { 1, 4, 8 }, { 7, 3, 0 }, { 6, 5, 2 } });
    Board goal ({ { 1, 2, 3 }, { 8, 0, 4 }, { 7, 6, 5 } });
    EXPECT_EQ(asearch(start, goal), 13);
}

