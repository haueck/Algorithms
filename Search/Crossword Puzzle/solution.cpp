/*
 * HackerRank - Crossword Puzzle
 * https://www.hackerrank.com/challenges/crossword-puzzle
 * Author: Rafal Kozik
 */

#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

struct Beginning
{
    int x;
    int y;
    uint32_t length;
    bool horizontal;
    Beginning(int x, int y, uint32_t length, bool horizontal) : x(x), y(y), length(length), horizontal(horizontal) { }
};

class Board
{
public:

    std::string board[10];
    std::vector<std::string> words;
    std::vector<Beginning> beginnings;
    std::vector<std::pair<int,int>> solution;

    void scan()
    {
        for (int i = 0; i < 10; ++i)
        {
            int count = 0;
            for (int j = 0; j < 10; ++j)
            {
                if (board[i][j] == '-')
                {
                    ++count;
                }
                else
                {
                    if (count > 1)
                    {
                        beginnings.emplace_back(i, j - count, count, true);
                    }
                    count = 0;
                }
            }
            if (count > 1)
            {
                beginnings.emplace_back(i, 10 - count, count, true);
            }
        }
        for (int j = 0; j < 10; ++j)
        {
            int count = 0;
            for (int i = 0; i < 10; ++i)
            {
                if (board[i][j] == '-')
                {
                    ++count;
                }
                else
                {
                    if (count > 1)
                    {
                        beginnings.emplace_back(i - count, j, count, false);
                    }
                    count = 0;
                }
            }
            if (count > 1)
            {
                beginnings.emplace_back(10 - count, j, count, false);
            }
        }
    }

    void add(std::string word)
    {
        words.push_back(word);
    }

    void print()
    {
        for (auto line : board)
        {
            LOG(line);
        }
    }

    bool insert(int word, int position)
    {
        auto start_x = beginnings[position].x;
        auto start_y = beginnings[position].y;
        auto length = beginnings[position].length;
        auto horizontal = beginnings[position].horizontal;
        for (uint32_t i = 0; i < length; ++i)
        {
            int x = horizontal ? start_x : start_x + i;
            int y = horizontal ? start_y + i : start_y;
            if (words[word][i] != board[x][y] && board[x][y] != '-')
            {
                return false;
            }
        }
        for (uint32_t i = 0; i < length; ++i)
        {
            int x = horizontal ? start_x : start_x + i;
            int y = horizontal ? start_y + i : start_y;
            board[x][y] = words[word][i];
        }
        return true;
    }

    void clear(int position)
    {
        auto start_x = beginnings[position].x;
        auto start_y = beginnings[position].y;
        auto length = beginnings[position].length;
        auto horizontal = beginnings[position].horizontal;
        for (uint32_t i = 0; i < length; ++i)
        {
            int x = horizontal ? start_x : start_x + i;
            int y = horizontal ? start_y + i : start_y;
            board[x][y] = '-';
        }
    }

    void repaint()
    {
       for (auto move : solution)
       {
           insert(move.first, move.second);
       }
    }

    bool solve(uint32_t word)
    {
        if (word == words.size())
        {
            return true;
        }
        for (uint32_t position = 0; position < beginnings.size(); ++position)
        {
            if (words[word].size() == beginnings[position].length)
            {
                bool inserted = insert(word, position);
                if (inserted)
                {
                    solution.emplace_back(word, position);
                    auto success = solve(word + 1);
                    if (success)
                    {
                        return true;
                    }
                    else
                    {
                        solution.pop_back();
                        clear(position);
                        repaint();
                    }
                }
            }
        }
        return false;
    }
};

int main()
{
    Board board;
    for (int i = 0; i < 10; ++i)
    {
        std::cin >> board.board[i];
    }
    std::string words;
    std::cin >> words;
    auto start = 0;
    while (true)
    {
        auto position = words.find(';', start + 1);
        if (position == std::string::npos)
        {
            std::string word(words, start);
            board.add(word);
            break;
        }
        else
        {
            std::string word(words, start, position - start);
            board.add(word);
            start = position + 1;
        }
    }
    board.scan();
    board.solve(0);
    board.print();
}

