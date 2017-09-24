/*
 * HackerRank - Lego Blocks
 * https://www.hackerrank.com/challenges/lego-blocks
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

int64_t mod(int64_t n)
{
    return ((n + 1000000007) % 1000000007);
}

std::vector<int64_t> calculate_all_walls(int width, int height)
{
    std::vector<int64_t> result{1, 1, 2, 4};
    result.resize(width + 1);
    /*
     * For example, to compute the total number of possible walls with width 7,
     * we sum the number of possible walls with widths:
     * - 6 (we add a brick of length 1 to them to make a wall of width 7),
     * - 5 (we add a brick of length 2 to them to make a wall of width 7),
     * - 4 (we add a brick of length 3 to them to make a wall of width 7),
     * - 3 (we add a brick of length 4 to them to make a wall of width 7)
     */
    for (int i = 4; i <= width; ++i)
    {
        result[i] = mod(result[i - 1] + result[i - 2] + result[i - 3] + result[i - 4]);
    }
    for (int i = 2; i <= width; ++i)
    {
        auto power = result[i];
        for (int j = 1; j < height; ++j)
        {
            power = mod(power * result[i]);
        }
        result[i] = power;
    }
    return result;
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N, M;
        std::cin >> N >> M;
        std::vector<int64_t> stable_walls(M + 1);
        std::vector<int64_t> all_walls = calculate_all_walls(M, N);
        stable_walls[1] = 1;
        /*
         * A(X) - number of ways to build a wall of length X
         * S(Y) - number of solid walls of length Z
         * P(Z) - number of ways to build a wall with a crack in Y
         * P(Z1^Z2) - number of wall with a crack in Z1 and Z2
         * P(Z1vZ2) - number of wall with a crack in Z1 or in Z2
         * We use inclusion-exclusion principle to calculate P(Z1vZ2)
         * 
         * Wall of length 1
         * S(1) = A(1)
         * Wall of length 2
         * S(2) = A(2) - P(1) = A(2) - A(1)*A(1)
         * Wall of length 3
         * S(3) = A(3) - P(1v2) = A(3) - [P(1) + P(2) - P(1^2)] = A(3) - [A(1)A(2) + A(2)A(1) - A(1)A(1)A(1)] =
         *      = A(3) - [A(1)A(2) + [A(2) - A(1)A(1)]A(1)] = A(3) - [S(1)A(2) + S(2)A(1)]
         * S(Y) = A(Y) - sum(L = 1 .. Y - 1)[S(L)A(Y - L)]
         */
        for (int i = 2; i <= M; ++i)
        {
            stable_walls[i] = all_walls[i];
            for (int j = 1; j < i; ++j)
            {
                stable_walls[i] = mod(stable_walls[i] - mod(stable_walls[j] * all_walls[i - j]));
            }
        }
        LOG(stable_walls[M]);
    }
}

