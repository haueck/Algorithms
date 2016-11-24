/*
 * HackerRank - Sansa and XOR
 * Bit Manipulation
 * https://www.hackerrank.com/challenges/sansa-and-xor
 * Author: Rafal Kozik
 */

/*
 *     0 1 2 3 4 5 6 7 8 
 * 01: 1 1 1 1 1 1 1 1 1 
 * 02: 1 0 0 0 0 0 0 0 1 
 * 03: 1 0 1 1 1 1 1 0 1 
 * 04: 1 0 1 0 0 0 1 0 1 
 * 05: 1 0 1 0 1 0 1 0 1 
 * 06: 1 0 1 0 0 0 1 0 1 
 * 07: 1 0 1 1 1 1 1 0 1 
 * 08: 1 0 0 0 0 0 0 0 1 
 * 09: 1 1 1 1 1 1 1 1 1 
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

bool odd(int n)
{
    return n & 1;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T = 0;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int N;
        std::cin >> N;
        std::vector<int> data(N);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> data[i];
        }
        if (odd(N))
        {
            int result = 0;
            for (int i = 0; i < N / 2; i = i + 2)
            {
                result = result ^ data[i];
                result = result ^ data[N - 1 - i];
            }
            int mid = N / 2;
            if (!odd(mid))
            {
                result = result ^ data[mid];
            }
            LOG(result);
        }
        else
        {
            LOG(0);
        }
    }
    return 0;
}
