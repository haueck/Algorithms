/*
 * Codeforces - Three Pieces
 * http://codeforces.com/contest/1065/problem/D
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

class Problem
{
public:

    int n;
    std::vector<std::vector<std::pair<int,int>>> dp;
    std::vector<std::pair<int,int>> square_to_pos;
    std::vector<std::vector<int>> pos_to_square;

    struct State
    {
        int square;
        int piece;
        int steps;
        int switches;
    };

    Problem(int n) : n(n), dp(n * n, std::vector<std::pair<int,int>>(3, { INT32_MAX, INT32_MAX })), square_to_pos(n * n), pos_to_square(n, std::vector<int>(n))
    {
        for (int i = 0; i < 3; ++i)
        {
            dp[0][i].first = 0;
            dp[0][i].second = 0;
        }
    }

    void set_square(int i, int j, int value)
    {
        square_to_pos[value - 1].first = i;
        square_to_pos[value - 1].second = j;
        pos_to_square[i][j] = value - 1;
    }

    std::vector<int> get_squares(int square, int piece)
    {
        std::vector<int> squares;
        auto i = square_to_pos[square].first;
        auto j = square_to_pos[square].second;
        if (piece == 0)
        {
            auto primitives = std::vector<std::pair<int,int>>({ {1, 1}, {1, -1}, {-1, 1}, {-1, -1} });
            for (auto primitive : primitives)
            {
                auto ii = i + primitive.first;
                auto jj = j + primitive.second;
                while (ii < n && jj < n && ii >= 0 && jj >= 0)
                {
                    squares.push_back(pos_to_square[ii][jj]);
                    ii += primitive.first;
                    jj += primitive.second;
                }
            }
        }
        else if (piece == 1)
        {
            auto primitives = std::vector<std::pair<int,int>>({ {0, 1}, {0, -1}, {-1, 0}, {1, 0} });
            for (auto primitive : primitives)
            {
                auto ii = i + primitive.first;
                auto jj = j + primitive.second;
                while (ii < n && jj < n && ii >= 0 && jj >= 0)
                {
                    squares.push_back(pos_to_square[ii][jj]);
                    ii += primitive.first;
                    jj += primitive.second;
                }
            }
        }
        else if (piece == 2)
        {
            auto primitives = std::vector<std::pair<int,int>>{ {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2} };
            for (auto primitive : primitives)
            {
                auto ii = i + primitive.first;
                auto jj = j + primitive.second;
                if (ii < n && jj < n && ii >= 0 && jj >= 0)
                {
                    squares.push_back(pos_to_square[ii][jj]);
                }
            }
        }
        return squares;
    }

    void bfs(int start)
    {
        auto target_square = start + 1;
        for (int target_piece = 0; target_piece < 3; ++target_piece)
        {
            for (int starting_piece = 0; starting_piece < 3; ++starting_piece)
            {
                std::vector<std::vector<int>> visited(n * n, std::vector<int>(3, INT32_MAX));
                std::queue<State> queue;
                queue.emplace(State{ start, starting_piece, dp[start][starting_piece].first, dp[start][starting_piece].second });
                visited[start][starting_piece] = dp[start][starting_piece].second;
                while (!queue.empty())
                {
                    auto current = queue.front();
                    queue.pop();
                    if (current.steps > dp[target_square][target_piece].first)
                    {
                        break;
                    }
                    else if (current.square == target_square && current.piece == target_piece)
                    {
                        if (current.steps < dp[target_square][target_piece].first)
                        {
                            dp[current.square][current.piece].first = current.steps;
                            dp[current.square][current.piece].second = current.switches;
                        }
                        else if (current.steps == dp[target_square][target_piece].first)
                        {
                            dp[current.square][current.piece].second = std::min(current.switches, dp[current.square][current.piece].second);
                        }
                    }
                    else
                    {
                        for (int new_piece = 0; new_piece < 3; ++new_piece)
                        {
                            if (new_piece != current.piece && current.switches + 1 < visited[current.square][new_piece])
                            {
                                queue.emplace(State{ current.square, new_piece, current.steps + 1, current.switches + 1 });
                                visited[current.square][new_piece] = current.switches + 1;
                            }
                        }
                        auto squares = get_squares(current.square, current.piece);
                        for (auto square : squares)
                        {
                            if (current.switches < visited[square][current.piece])
                            {
                                queue.emplace(State{ square, current.piece, current.steps + 1, current.switches });
                                visited[square][current.piece] = current.switches;
                            }
                        }
                    }
                }
            }
        }
    }

    void solve()
    {
        for (int i = 0; i < n * n - 1; ++i)
        {
            bfs(i);
        }
        int steps = INT32_MAX;
        int switches = 0;
        for (int i = 0; i < 3; ++i)
        {
            if (dp.back()[i].first < steps)
            {
                steps = dp.back()[i].first;
                switches = dp.back()[i].second;
            }
            else if (dp.back()[i].first == steps)
            {
                switches = std::min(switches, dp.back()[i].second);
            }
        }
        LOG(steps << " " << switches);
    }

};

int main()
{
    int n;
    std::cin >> n;
    Problem pbl(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int value;
            std::cin >> value;
            pbl.set_square(i, j, value);
        }
    }
    pbl.solve();
}

