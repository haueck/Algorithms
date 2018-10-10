/*
 * HackerRank - The Maximum Subarray
 * https://www.hackerrank.com/challenges/maxsubarray/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::cin >> N;
        std::vector<int> data(N, 0);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> data[i];
        }
        int sum = 0;
        int pos = 0;
        int max = std::numeric_limits<int>::min();
        for (int i = 0; i < N; ++i)
        {
            sum += data[i];
            if (sum > max)
            {
                max = sum;
            }
            if (sum < 0)
            {
                sum = 0;
            }
            if (data[i] > 0)
            {
                pos += data[i];
            }
        }
        if (pos == 0)
        {
            pos = max;
        }
        LOG(max << " " << pos);
    }
    return 0;
}

