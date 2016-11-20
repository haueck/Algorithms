/*
 * UVa Online Judge - Deciding Victory in Go
 * Graph traversing
 * https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=152&page=show_problem&problem=793
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <cstring>

#define LOG(x) std::cout << x << std::endl;

class Stats
{
public:
    int white{0};
    int black{0};
    int empty{0};
    void print()
    {
        std::cout << "Black " << black << " White " << white <<std::endl;
    };
};

int moves[81][4];

class Board
{
    char b[81];
public:
    void set(char board[])
    {
        std::memcpy(b, board, 81 * sizeof(char));
    }

    Stats traverse()
    {
        Stats stats;
        for (int i = 0; i < 81; ++i)
        {
            switch (b[i])
            {
                case 'E':
                {
                    Stats found;
                    dfs(i, found);
                    if (found.black == 0)
                    {
                        stats.white += found.empty;
                    }
                    else if (found.white == 0)
                    {
                        stats.black += found.empty;
                    }
                    break;
                }
                case 'X':
                    ++stats.black;
                    b[i] = 'x';
                    break;
                case 'O':
                    ++stats.white;
                    b[i] = 'o';
                    break;
            };
        }
        return stats;
    };

    void dfs(int pos, Stats& found)
    {
        b[pos] = 'e';
        ++found.empty;
        for (int i = 0; i < 4; ++i)
        {
            int c = (int)moves[pos][i];
            if (c == pos)
            {
                continue;
            }
            switch (b[c])
            {
                case 'O':
                case 'o':
                    ++found.white;
                    break;
                case 'X':
                case 'x':
                    ++found.black;
                    break;
                case 'E':
                    dfs(c, found);
                    break;
            };
        }
    };
};

void init()
{
    for (int i = 0; i < 81; ++i)
    {
        moves[i][0] = i;
        moves[i][1] = i;
        moves[i][2] = i + 1;
        moves[i][3] = i - 1;
        if (i > 8)
        {
            moves[i][0] = i - 9;
        }
        if (i < 72)
        {
            moves[i][1] = i + 9;
        }
        if (0 == i % 9)
        {
            moves[i][3] = i;
        }
        if (8 == i % 9)
        {
            moves[i][2] = i;
        }
    }
}

int main(int argc, char **argv)
{
    int N;
    scanf("%d", &N);
    std::vector<Board> boards(N);
    init();
    for (int i = 0; i < N; ++i)
    {
        char board[81];
        int count = 0;
        while (count < 81)
        {
            char c = fgetc(stdin);
            switch (c)
            {
                case 'O':
                case 'X':
                    board[count++] = c;
                    break;
                case '.':
                    board[count++] = 'E';
                    break;
            };
        }
        boards[i].set(board);
    }
    for (int i = 0; i < N; ++i)
    {
        Stats stats = boards[i].traverse();
        stats.print();
    }
    return 0;
}

