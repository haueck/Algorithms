/*
 * HackerRank - Tile Painting: Revisited!
 * Contests
 * https://www.hackerrank.com/contests/hourrank-7/challenges/tile-painting-revisited
 * Author: Rafal Kozik
 */

#include <iostream>
#include <cmath>

#define LOG(x) std::cout << x << std::endl;

/*
 * It is way too slow, it is O(N^2) but could be modified to be O(N)
 * To pass all test cases it has to be O(sqrt(N))
 */
int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        uint64_t N, count = 0;
        std::cin >> N;
        for (uint64_t s = 0; s < N; ++s)
        {
            // One tile at the given s
            ++count;
            for (uint64_t d = 1; d < N - s; ++d)
            {
                count += std::ceil(static_cast<double>(N - s) / d) - 1;
            }
        }
        LOG(count % 1000000007);
    }

    return 0;
}

