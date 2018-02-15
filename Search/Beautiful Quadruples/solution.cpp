/*
 * hackerRank - Beautiful Quadruples
 * https://www.hackerrank.com/challenges/xor-quadruples/problem
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> abcd(4);
    std::cin >> abcd[0];
    std::cin >> abcd[1];
    std::cin >> abcd[2];
    std::cin >> abcd[3];
    std::sort(abcd.begin(), abcd.end());
    std::vector<std::vector<int>> xors(abcd[2] + 1, std::vector<int>(4096));
    std::vector<int> pairs(abcd[2] + 1);
    int64_t result = 0;
    for (int i = abcd[2]; i > 0; --i)
    {
        for (int j = i; j <= abcd[3]; ++j)
        {
            // Number of pairs where the first number is at least i
            ++pairs[i];
            // Number of pairs giving specific xor value, where
            // the first number is at least i
            ++xors[i][i ^ j];
        }
        pairs[i - 1] = pairs[i];
        xors[i - 1] = xors[i];
    }
    /*
     * A = 1, B = 2, C = 3, D = 4
     *
     * i = 1, j = 1
     * 1 1 1 1
     * 1 1 1 2
     * 1 1 1 3
     * 1 1 1 4
     * 1 1 2 2
     * 1 1 2 3
     * 1 1 2 4
     * 1 1 3 3
     * 1 1 3 4
     *
     * i = 1, j = 2
     * 1 2 2 2
     * 1 2 2 3
     * 1 2 2 4
     * 1 2 3 3
     * 1 2 3 4
     */
    for (int i = 1; i <= abcd[0]; ++i)
    {
        for (int j = i; j <= abcd[1]; ++j)
        {
            result += pairs[j];
            result -= xors[j][i ^ j];
        }
    }
    std::cout << result << std::endl;
}

