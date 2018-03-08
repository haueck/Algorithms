/*
 * HackerRank - Carpet Game
 * https://www.hackerrank.com/contests/101hack53/challenges/carpet-game/problem
 * Author: Rafal Kozik
 */

#include <algorithm>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

const int MOD = 1e9 + 7;

int64_t arithmetic_series(int64_t first, int64_t last, int64_t n)
{
    return (((first + last) * n) / 2) % MOD;
}

int main()
{
    int d;
    std::cin >> d;
    while (d--)
    {
        int n, m;
        int64_t k, result = 0;
        std::cin >> n >> m >> k;
        if (k == 1)
        {
            // Count number of ways a friend can sit to the east for each cell
            result = (result + arithmetic_series(1, n - 1, n - 1) * m) % MOD;
            // Count number of ways a friend can sit to the south for each cell
            result = (result + arithmetic_series(1, m - 1, m - 1) * n) % MOD;
            for (int i = 1; i < m; ++i)
            {
                // Count number of ways a friend can sit to the south-east and south-west for each row
                result = (result + 2 * arithmetic_series(std::max(0, (n - 1) - (i - 1)), n - 1, std::min(i, n))) % MOD;
            }
            // Switch positions of Jen and a friend
            result = (result * 2) % MOD;
        }
        else if (k < 4)
        {
            int64_t squares = 0;
            int64_t rotated_squares = 0;
            int64_t triangles = 0;
            for (int i = 1; i < m; ++i)
            {
                // Number of shapes with the bottom at row i
                /*
                 * x x
                 *
                 * x x
                 */
                squares = (squares + arithmetic_series(std::max(0, (n - 1) - (i - 1)), n - 1, std::min(i, n))) % MOD;
                /*
                 *  x
                 * x x
                 *  x
                 */
                rotated_squares = (rotated_squares + arithmetic_series((n - 2) - 2 * std::min((i - 2) / 2, (n - 3) / 2), n - 2, std::min(i / 2, (n - 1) / 2))) % MOD;
                /*
                 *  x
                 * x x
                 */
                triangles = (triangles + arithmetic_series((n - 2) - 2 * std::min(i - 1, (n - 3) / 2), n - 2, std::min(i, (n - 1) / 2))) % MOD;
                /*
                 *  x
                 * x
                 *  x
                 */
                triangles = (triangles + arithmetic_series((n - 1) - std::min((i - 2) / 2, n - 2), n - 1, std::min(i / 2, n - 1))) % MOD;
            }
            // Switch positions of all players
            result = (squares * 24) % MOD;
            if (k == 2)
            {
                // Switch positions of all players
                result = (result + (triangles * 12)) % MOD;
            }
            else if (k == 3)
            {
                // Switch positions of all players
                result = (result + (rotated_squares * 24)) % MOD;
            }
        }
        LOG(result);
    }
}

