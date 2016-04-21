/*
 * HackerRank - Beautiful Pairs
 * Greedy
 * https://www.hackerrank.com/challenges/beautiful-pairs
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    std::vector<int> a(N, 0), b(N, 0);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> a[i];
    }
    for (int i = 0; i < N; ++i)
    {
        std::cin >> b[i];
    }
    int count = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (a[i] == b[j])
            {
                b[j] *= -1;
                ++count;
                break;
            }
        }
    }
    LOG((count == N ? count - 1 : count + 1));
    return 0;
}

