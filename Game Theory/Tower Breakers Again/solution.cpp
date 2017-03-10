/*
 * HackerRank - Tower Breakers, Again!
 * https://www.hackerrank.com/challenges/tower-breakers-again-1
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

/*
 * Even number of towers with the same height can be removed from the game.
 * Whoever starts playing with those tower will lose, because another player
 * will simply mirror all moves.
 *
 * Possible scenarios for a tower of height 15:
 * - Scenario 1:
 *  a) reduce height to 5 (3 towers of height 5, 2 of them cancel out)
 *  b) reduce height to 1 (5 towers of height 1, 4 of them cancel out)
 * - Scenario 2:
 *  a) reduce height to 3 (5 towers of height 3, 4 of them cancel out)
 *  b) reduce height to 1 (3 towers of height 1, 2 of them cancel out)
 * - Scenario 3:
 *  a) reduce height to 1 (15 towers of height 1, 14 of them cancel out)
 *
 * So the grundy number is 2 - the number of odd prime factors.
 * It is equivalent to a Nim tower of height 2 (we can take 1 or 2 stones).
 * Scenarios 1 and 2 are mutually exclusive.
 *
 * Possible scenarios for a tower of height 12:
 * - Scenario 1:
 *  a) reduce height to 4 (3 towers of height 4, 2 of them cancel out)
 *  b) remove the tower altogether (4 towers of height 1)
 * - Scenario 2:
 *  a) reduce height to 4 (3 towers of height 4, 2 of them cancel out)
 *  b) remove the tower altogether (2 towers of height 1)
 * - Scenario 3, 4, 5, 6:
 *  a) remove the tower altogether (12x1, 6x2, 4x3, 2x6)
 *
 * So the grundy number is also 2 - the number of odd prime factors plus one scenario
 * for all even divisors when we remove the tower altogether.
 * Scenarios 1, 2 and 3, 4, 5, 6 are mutually exclusive.
 */

std::vector<int> sift(int max)
{
    int size = (max + 1) / 2;
    std::vector<bool> sieve(size, true);
    std::vector<int> primes(1, 2);
    int i = 0;
    int is = 3;
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
    for (int i = 0; i < size ; ++i)
    {
        if (sieve[i])
        {
            primes.push_back(i + i + 3);
        }
    }
    return primes;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    auto primes = sift(1000000);
    for (int t = 0; t < T; ++t)
    {
        int N;
        std::cin >> N;
        std::vector<int> nim(N);
        for (int i = 0; i < N; ++i)
        {
            int M, K, count = 0;
            std::cin >> M;
            auto upper = std::reverse_iterator<std::vector<int>::iterator>(std::upper_bound(primes.begin(), primes.end(), M));
            bool even = M % 2 == 0;
            std::vector<int> factors;
            for (auto it = upper; it != primes.rend(); ++it)
            {
                while (*it > 2 && M % *it == 0)
                {
                    M = M / *it;
                    ++count;
                }
            }
            nim[i] = count + (even ? 1 : 0);
        }
        int result = 0;
        for (int i = 0; i < N; ++i)
        {
            result ^= nim[i];
        }
        LOG((result == 0 ? 2 : 1));
    }
    return 0;
}

