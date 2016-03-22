/*
 * HackerRank - Larry's Array
 * Arrays
 * https://www.hackerrank.com/contests/101hack35/challenges/larrys-array
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

int min(const std::vector<int>& v, int start)
{
    int m = start;
    int size = v.size();
    for (int i = start + 1; i < size; ++i)
    {
        if (v[i] < v[m])
        {
            m = i;
        }
    }
    return m;
}

void rotate(std::vector<int>& v, int pos)
{
    int tmp = v[pos - 1];
    v[pos - 1] = v[pos];
    v[pos] = v[pos + 1];
    v[pos + 1] = tmp;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T, N;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        std::cin >> N;
        std::vector<int> data(N, 0);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> data[i];
        }
        int current = 0;
        while (current < N - 2)
        {
            auto m = min(data, current);
            if (m == N - 1)
            {
                rotate(data, -1 + m--);
            }
            while (m > current)
            {
                rotate(data, m--);
            }
            ++current;
        }
        LOG((data[N - 1] > data[N - 2] ? "YES" : "NO"));
    }
    return 0;
}

