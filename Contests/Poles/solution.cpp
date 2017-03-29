/*
 * HackerRank - Poles
 * https://www.hackerrank.com/contests/w30/challenges/poles
 * Author: Rafal Kozik
 *
 * TODO: This solution is not finished, it gives correct results but it is too slow.
 * Its complexity is O(kn^2) and it has to be optimized to O(kn) using convex hull trick.
 * http://codeforces.com/blog/entry/8219
 * http://wcipeg.com/wiki/Convex_hull_trick
 * https://apps.topcoder.com/forums/?module=Thread&threadID=608334&start=0&mc=14#1120736
 *
 * My idea was to change the problem and answer a following question:
 * how to insert k rectangles into a triangle so the sum of their areas is maximal?
 *
 *      /|
 *     /_|
 *    /| |
 *   /_|_|
 *  /|   |
 * /_|___|
 * 
 * The area of the triangle represents total effort of bringing all logs to the lowest level.
 * Each rectangle represents savings in effort if we decide to make a pile at height h.
 * So the answer is total effort minus maximal area of k rectangles.
 *
 * 1. Sort the rectangles so they meet the condition of applicability of convex hull trick
 * 2. Optionally change arrays alts and acc so they make more sense
 * 3. Optimize
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int main()
{
    std::ios::sync_with_stdio(false);
    int64_t n, k, total = 0;
    std::cin >> n >> k;
    std::vector<int64_t> alts(n);
    std::vector<int64_t> weights(n);
    std::vector<std::vector<int64_t>> S(n, std::vector<int64_t>(k + 1, 0));
    for (int i = 0; i < n; ++i)
    {
        std::cin >> alts[i] >> weights[i];
    }
    for (int i = 1; i < n; ++i)
    {
        alts[i] -= alts[0];
        total += alts[i] * weights[i];
    }
    std::vector<int64_t> acc(n);
    for (int i = 1; i < n; ++i)
    {
        acc[i] = acc[i - 1] + weights[n - i];
    }
    for (int h = 1; h < n; ++h)
    {
        int64_t max = 0;
        for (int w = h; w > 0; --w)
        {
            max = std::max(max, (acc[n - 1 - h + w] - acc[n - 1 - h]) * alts[1 + h - w]);
        }
        S[h][1] = max;
    }
    for (int h = 2; h < n; ++h)
    {
        for (int b = 2; b <= h && b < k; ++b)
        {
            for (int z = h - (b - 1); z > 0; --z)
            {
                int64_t m = -1 * alts[1 + h - z];
                int64_t x = acc[n - 1 - h];
                int64_t c = S[h - z][b - 1] + acc[n - 1 - h + z] * alts[1 + h - z];
                S[h][b] = std::max(S[h][b], m * x + c);
            }
        }
    }
    LOG(total - S[n - 1][k - 1]);
}

