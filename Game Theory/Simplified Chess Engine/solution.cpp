/*
 * HackerRank - Simplified Chess Engine
 * Game Theory
 * https://www.hackerrank.com/challenges/simplified-chess-engine
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <cctype>

#define LOG(x) std::cout << x << std::endl;

const int SIZE = 4;

enum class Color
{
    White,
    Black
};

class Move
{
public:

    int8_t row_from;
    int8_t col_from;
    int8_t row_to;
    int8_t col_to;

    Move(int rf, int cf, int rt, int ct) : row_from(rf), col_from(cf), row_to(rt), col_to(ct) { }
};

bool is_off_board(int row, int col)
{
    return row < 0 || row > 3 || col < 0 || col > 3;
}

bool is_empty(char piece)
{
    return piece == ' ';
}

Color get_color(char piece)
{
    return piece >= 'a' ? Color::Black : Color::White;
}

std::vector<Move> rook_bishop(std::vector<std::string>& board, int r, int c, std::vector<std::vector<int>> vectors)
{
    std::vector<Move> retval;
    for (std::vector<int> vec : vectors)
    {
        int row = r;
        int col = c;
        while (true)
        {
            row += vec[0];
            col += vec[1];
            if (is_off_board(row, col))
            {
                break;
            }
            else if (is_empty(board[row][col]))
            {
                retval.emplace_back(Move(r, c, row, col));
            }
            else if (get_color(board[r][c]) != get_color(board[row][col]))
            {
                retval.emplace_back(Move(r, c, row, col));
                break;
            }
            else
            {
                break;
            }
        }
    }
    return retval;
}

std::vector<Move> rook(std::vector<std::string>& board, int r, int c)
{
    return rook_bishop(board, r, c, {{1, 0}, {0, 1}, {0, -1}, {-1, 0}});
}

std::vector<Move> bishop(std::vector<std::string>& board, int r, int c)
{
    return rook_bishop(board, r, c, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
}

std::vector<Move> queen(std::vector<std::string>& board, int r, int c)
{
    auto m1 = rook(board, r, c);
    auto m2 = bishop(board, r, c);
    m1.insert(m1.begin(), m2.begin(), m2.end());
    return m1;
}

std::vector<Move> knight(std::vector<std::string>& board, int r, int c)
{
    std::vector<Move> retval;
    std::vector<std::vector<int>> vectors{{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
    for (auto& vec : vectors)
    {
        int row = r + vec[0];
        int col = c + vec[1];
        if (is_off_board(row, col))
        {
            continue;
        }
        else if (is_empty(board[row][col]) || get_color(board[r][c]) != get_color(board[row][col]))
        {
            retval.emplace_back(Move(r, c, row, col));
        }
    }
    return retval;
}

std::vector<Move> calc_moves(std::vector<std::string>& board, Color color)
{
    std::vector<Move> retval;
    for (int r = 0; r < SIZE; ++r)
    {
        for (int c = 0; c < SIZE; ++c)
        {
            if (!is_empty(board[r][c]) && get_color(board[r][c]) == color)
            {
                std::vector<Move> m;
                switch(std::tolower(board[r][c]))
                {
                    case 'q':
                        m = queen(board, r, c);
                        break;
                    case 'n':
                        m = knight(board, r, c);
                        break;
                    case 'b':
                        m = bishop(board, r, c);
                        break;
                    case 'r':
                        m = rook(board, r, c);
                        break;
                    default:
                        std::abort();
                }
                retval.insert(retval.end(), m.begin(), m.end());
            }
        }
    }
    return retval;
}

char make_move(std::vector<std::string>& board, Move move)
{
    auto captured = board[move.row_to][move.col_to];
    board[move.row_to][move.col_to] = board[move.row_from][move.col_from];
    board[move.row_from][move.col_from] = ' ';
    return captured;
}

void undo_move(std::vector<std::string>& board, Move move, char captured)
{
    board[move.row_from][move.col_from] = board[move.row_to][move.col_to];
    board[move.row_to][move.col_to] = captured;
}

bool lost(std::vector<std::string>& board, Color color)
{
    for (int r = 0; r < SIZE; ++r)
    {
        for (int c = 0; c < SIZE; ++c)
        {
            if (std::tolower(board[r][c]) == 'q' && get_color(board[r][c]) == color)
            {
                return false;
            }
        }
    }
    return true;
}

bool win_or_lose(std::vector<std::string>& board, Color color, int limit)
{
    if (lost(board, color))
    {
        return false;
    }
    if (limit == 0)
    {
        return color == Color::Black;
    }
    auto moves = calc_moves(board, color);
    for (auto& move : moves)
    {
        auto captured = make_move(board, move);
        auto win = !win_or_lose(board, color == Color::White ? Color::Black: Color::White, limit - 1);
        undo_move(board, move, captured);
        if (win)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int G;
    std::cin >> G;
    for (int g = 0; g < G; ++g)
    {
        int w, b, m;
        std::vector<std::string> board(SIZE, std::string(SIZE, ' '));
        std::cin >> w >> b >> m;
        for (int i = 0; i < w; ++i)
        {
            int row;
            char piece, column;
            std::cin >> piece >> column >> row;
            board[row - 1][column - 'A'] = piece;
        }
        for (int i = 0; i < b; ++i)
        {
            int row;
            char piece, column;
            std::cin >> piece >> column >> row;
            board[row - 1][column - 'A'] = std::tolower(piece);
        }
        LOG((win_or_lose(board, Color::White, m) ? "YES" : "NO"));
    }
    return 0;
}

