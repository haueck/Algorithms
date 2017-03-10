/*
 * HackerRank - New Year Chaos
 * https://www.hackerrank.com/challenges/new-year-chaos
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <numeric>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N, bribes = 0;
        std::cin >> N;
        std::vector<int> input(N);
        std::vector<int> expected(N);
        std::iota(expected.begin(), expected.end(), 0);
        for (int i = 0; i < N; i++)
        {
            std::cin >> input[i];
            --input[i];
        }
        for (int i = 0; i < N; i++)
        {
            if (expected[i] == input[i])
            {
                continue;
            }
            if (i + 2 < N && input[i] == expected[i + 2])
            {
                std::swap(expected[i + 1], expected[i + 2]);
                ++bribes;
            }
            if (i + 1 < N && input[i] == expected[i + 1])
            {
                std::swap(expected[i], expected[i + 1]);
                ++bribes;
            }
            else
            {
                bribes = -1;
                break;
            }
        }
        bribes >= 0 ? LOG(bribes) : LOG("Too chaotic");
    }
}

