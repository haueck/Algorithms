/*
 * HackerRank - Alice and Bob's Silly Game
 * 101 Hack 44
 * https://www.hackerrank.com/contests/101hack44/challenges/alice-and-bobs-silly-game
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

void sift(std::vector<bool>& sieve)
{
    int i = 0;
    int is = 0;;
    int size = sieve.size();
    while (is < size)
    {
        if (sieve[i])
        {
            for (int j = is; j < size; j += i + i + 3)
            {
                sieve[j] = false;
            }
        }
        ++i;
        is = 2 * i * (i + 3) + 3;
    }
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    std::vector<bool> sieve(100001 / 2, true);
    sift(sieve);
    for (int t = 0; t < T; ++t)
    {
        int N;
        std::cin >> N;
        int count = N > 1 ? 1 : 0;
        for (int i = 0; i + i + 3 <= N; ++i)
        {
            if (sieve[i])
            {
                ++count;
            }
        }
        LOG((count & 1 ? "Alice" : "Bob"));
    }
    return 0;
}

