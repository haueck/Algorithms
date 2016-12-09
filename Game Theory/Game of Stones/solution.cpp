/*
 * HackerRank - Game of Stones
 * Game Theory
 * https://www.hackerrank.com/challenges/game-of-stones-1
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

// Am I going to win?
bool win(int n, std::vector<bool>& cache)
{
    if (n < 0)
    {
        // Illegal move by my opponent, I win
        return true;
    }
    if (cache[n])
    {
        // This is a winning position, I win
        return true;
    }
    for (auto m : {2, 3, 5})
    {
        // Is there a move that makes my opponent lose?
        if (!win(n - m, cache))
        {
            // There is, I win
            cache[n] = true;
            return true;
        }
    }
    // No winning move, I lose
    return false;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    std::vector<bool> cache(101, false);
    for (int t = 0; t < T; ++t)
    {
        int n;
        std::cin >> n;
        LOG((win(n, cache) ? "First" : "Second"));
    }
    return 0;
}
