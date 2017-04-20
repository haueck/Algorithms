/*
 * HackerRank - KnightL on a Chessboard
 * https://www.hackerrank.com/challenges/knightl-on-chessboard
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <queue>

struct Square
{
    Square(int file, int rank) : file(file), rank(rank) { }
    int file;
    int rank;
};

struct Knight
{
    Knight(int a, int b) : a(a), b(b) { }
    int a;
    int b;
};

bool is_valid(int n, Square square)
{
    return square.file >= 0 && square.file < n && square.rank >= 0 && square.rank < n;
}

std::vector<Square> get_moves(int n, Square start, Knight knight)
{
    std::vector<Square> result;
    for (auto h : { -1, 1 })
    {
        for (auto v : { -1, 1 })
        {
            Square s1(start.file + knight.a * h, start.rank + knight.b * v);
            if (is_valid(n, s1))
            {
                result.push_back(s1);
            }
            Square s2(start.file + knight.b * h, start.rank + knight.a * v);
            if (is_valid(n, s2))
            {
                result.push_back(s2);
            }
        }
    }
    return result;
}

int search(int n, Knight knight)
{
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n));
    std::queue<std::pair<int,Square>> queue;
    queue.emplace(0, Square(0, 0));
    visited[0][0] = true;
    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();
        if (current.second.file == n - 1 && current.second.rank == n - 1)
        {
            return current.first;
        }
        auto sqaures = get_moves(n, current.second, knight);
        for (auto square : sqaures)
        {
            if (!visited[square.file][square.rank])
            {
                queue.emplace(current.first + 1, square);
                visited[square.file][square.rank] = true;
            }
        }
    }
    return -1;
}

int main()
{
    int n;
    std::cin >> n;
    for (int a = 1; a < n; ++a)
    {
        for (int b = 1; b < n; ++b)
        {
            Knight knight(a, b);
            auto result = search(n, knight);
            std::cout << result << " ";
        }
        std::cout << std::endl;
    }
}

