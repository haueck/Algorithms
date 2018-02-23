/*
 * HackerRank - LCS Returns
 * https://www.hackerrank.com/challenges/tutzki-and-lcs/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>

#define LOG(x) std::cout << x << std::endl

int main()
{
    std::string a, b;
    std::cin >> a >> b;
    std::vector<std::vector<int>> dpl(a.size() + 1, std::vector<int>(b.size() + 1));
    auto dpr = dpl;
    /*
     * a = "aa"
     * b = "baaa"
     *
     *         b   a   a   a
     *     0   0   0   0   0
     * a   0   0   1   1   1
     * a   0   0   1   2   2
     *
     * dpl[i][j] tells what is the lcs of a[0 .. i - 1] and b[0 .. j - 1]
     */
    for (auto i = 1u; i < a.size() + 1; ++i)
    {
        for (auto j = 1u; j < b.size() + 1; ++j)
        {
            if (a[i - 1] == b[j - 1])
            {
                dpl[i][j] = dpl[i - 1][j - 1] + 1;
            }
            else
            {
                dpl[i][j] = std::max(dpl[i - 1][j], dpl[i][j - 1]);
            }
        }
    }
    /*
     *       b   a   a   a   
     *   a   2   2   2   1   0
     *   a   1   1   1   1   0
     *       0   0   0   0   0
     *
     * dpr[i][j] tells what is the lcs of a[i .. end] and b[j .. end]
     */

    for (auto i = a.size(); i > 0; --i)
    {
        for (auto j = b.size(); j > 0; --j)
        {
            if (a[i - 1] == b[j - 1])
            {
                dpr[i - 1][j - 1] = dpr[i][j] + 1;
            }
            else
            {
                dpr[i - 1][j - 1] = std::max(dpr[i - 1][j], dpr[i][j - 1]);
            }
        }
    }
    auto lcs = dpr[0][0];
    uint64_t result = 0;
    std::set<char> counted;
    /*
     * At every position in a (first loop) we will try to insert
     * a character that will match a character in b (second loop).
     * Let's say we try to insert a character at position 2 in a
     * that matches character at position 3 in b.
     * If sum of lcs(a[0 .. 1], b[0 .. 2]) and lcs(a[2 .. end], b[4 .. end])
     * is equal to lcs(a, b) then by inserting this character we
     * will increase the lcs(a', b) by one.
     */
    for (auto i = 0u; i < a.size() + 1; ++i)
    {
        counted.clear();
        for (auto j = 0u; j < b.size(); ++j)
        {
            if (dpl[i][j] + dpr[i][j + 1] == lcs)
            {
                // We need to count each character inserted at i only once
                if (counted.find(b[j]) == counted.end())
                {
                    ++result;
                    counted.insert(b[j]);
                }
            }
        }
    }
    LOG(result);
}

