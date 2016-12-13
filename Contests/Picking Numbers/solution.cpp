/*
 * HackerRank - Picking Numbers
 * 101 Hack 44
 * https://www.hackerrank.com/contests/101hack44/challenges/picking-numbers
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    std::vector<int> count(101, 0);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int a;
        std::cin >> a;
        count[a]++;
    }
    int max = 0;
    for (int i = 1; i < 101; ++i)
    {
        if (count[i-1] + count[i] > max)
        {
            max = count[i-1] + count[i];
        }
    }
    LOG(max);
    return 0;
}

