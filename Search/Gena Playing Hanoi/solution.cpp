/*
 * HackerRank - Gena Playing Hanoi
 * https://www.hackerrank.com/challenges/gena/problem
 * Author: Rafal Kozik
 */

#include <queue>
#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

int move(int state, int disc, int rod)
{
    int clear = ~(3 << (2 * disc));
    int set = rod << (2 * disc);
    state = state & clear;
    state = state | set;
    return state;
}

std::vector<int> calc_next_states(int state, int N)
{
    std::vector<int> states;
    std::vector<int> rods(4, N);
    int bitmask = 3;
    for (int i = N - 1; i >= 0; i--)
    {
        int rod = (state >> (2 * i)) & bitmask;
        rods[rod] = i;
    }
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (rods[i] < rods[j])
            {
                states.push_back(move(state, rods[i], j));
            }
        }
    }
    return states;
}

int minimum_moves(int state, int N)
{
    std::queue<std::pair<int,int>> states;
    std::vector<bool> visited(1 << (2 * N));
    states.emplace(state, 0);
    visited[state] = true;
    while (!states.empty())
    {
        auto current = states.front();
        states.pop();
        auto next_states = calc_next_states(current.first, N);
        for (auto next : next_states)
        {
            if (!visited[next])
            {
                if (next == 0)
                {
                    return current.second + 1;
                }
                states.emplace(next, current.second + 1);
                visited[next] = true;
            }
        }
    }
    return 0;
}

int main()
{
    int N, state = 0;
    std::cin >> N;
    std::vector<int> discs(N);
    for (int i = 0; i < N; i++)
    {
        int rod;
        std::cin >> rod;
        state = state | ((rod - 1) << (2 * i));
    }
    LOG(minimum_moves(state, N));
}

