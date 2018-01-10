/*
 * HackerRank - Fun Game
 * https://www.hackerrank.com/challenges/fun-game-1/problem
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        std::cin >> n;
        std::vector<int> A(n), B(n);
        for (int i = 0; i < n; ++i)
        {
            std::cin >> A[i];
        }
        for (int i = 0; i < n; ++i)
        {
            std::cin >> B[i];
        }
        std::vector<std::pair<int,int>> sums(n);
        for (int i = 0; i < n; ++i)
        {
            sums[i].first = A[i] + B[i];
            sums[i].second = A[i];
        }
        int a_score = 0, b_score = 0;
        bool a_turn = true;
        std::sort(sums.begin(), sums.end());
        for (int i = n - 1; i >= 0; --i)
        {
            if (a_turn)
            {
                a_score += sums[i].second;
            }
            else
            {
                b_score += sums[i].first - sums[i].second;
            }
            a_turn = !a_turn;
        }
        if (a_score == b_score)
        {
            LOG("Tie");
        }
        else if (a_score < b_score)
        {
            LOG("Second");
        }
        else
        {
            LOG("First");
        }
    }
}

