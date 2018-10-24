/*
 * Codeforces - Labyrinth
 * http://codeforces.com/contest/1064/problem/D
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

struct State
{
    int i;
    int j;
    int left;
    int right;
    bool operator<(const State& o) const
    {
        return left + right < o.left + o.right;
    }
};

int traverse(std::vector<std::vector<bool>>& maze, int n, int m, int i, int j, int left, int right)
{
    std::vector<std::vector<int>> moves_left(n, std::vector<int>(m, -1));
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m));
    std::priority_queue<State> queue;
    queue.emplace(State{ i, j, left, right });
    while (!queue.empty())
    {
        auto c = queue.top();
        queue.pop();
        visited[c.i][c.j] = true;
        if (c.left + c.right < moves_left[c.i][c.j])
        {
            continue;
        }
        if (c.i + 1 < n && maze[c.i + 1][c.j] && c.left + c.right > moves_left[c.i + 1][c.j])
        {
            queue.emplace(State{ c.i + 1, c.j, c.left, c.right });
            moves_left[c.i + 1][c.j] = c.left + c.right;
        }
        if (c.i - 1 >= 0 && maze[c.i - 1][c.j] && c.left + c.right > moves_left[c.i - 1][c.j])
        {
            queue.emplace(State{ c.i - 1, c.j, c.left, c.right });
            moves_left[c.i - 1][c.j] = c.left + c.right;
        }
        if (c.right > 0 && c.j + 1 < m && maze[c.i][c.j + 1] && c.left + c.right - 1 > moves_left[c.i][c.j + 1])
        {
            queue.emplace(State{ c.i, c.j + 1, c.left, c.right - 1});
            moves_left[c.i][c.j + 1] = c.left + c.right - 1;
        }
        if (c.left > 0 && c.j - 1 >= 0 && maze[c.i][c.j - 1] && c.left + c.right - 1 > moves_left[c.i][c.j - 1])
        {
            queue.emplace(State{ c.i, c.j - 1, c.left - 1, c.right });
            moves_left[c.i][c.j - 1] = c.left + c.right - 1;
        }
    }
    int result = 0;
    for (auto k = 0; k < n; ++k)
    {
        for (auto l = 0; l < m; ++l)
        {
            result += visited[k][l];
        }
    }
    return result;
}

int main()
{
    int n, m, i, j, x, y;
    std::cin >> n >> m >> i >> j >> x >> y;
    std::vector<std::vector<bool>> maze(n, std::vector<bool>(m));
    for (auto k = 0; k < n; ++k)
    {
        for (auto l = 0; l < m; ++l)
        {
            char c;
            std::cin >> c;
            maze[k][l] = (c == '.');
        }
    }
    LOG(traverse(maze, n, m, i - 1, j - 1, x, y));
}

