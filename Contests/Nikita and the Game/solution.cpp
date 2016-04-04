/*
 * HackerRank - Nikita and the Game
 * Contests - arrays
 * https://www.hackerrank.com/contests/hourrank-7/challenges/array-splitting
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

int middle(const std::vector<uint64_t>& data, std::vector<uint64_t>& sums, int from, int to)
{
    auto tmp = sums[from] - data[from];
    auto sum = sums[to] - tmp;
    uint64_t half = sum / 2;
    if (2 * half != sum)
    {
        return -1;
    }
    auto position = from;
    int size = sums.size();
    while (position < size && sums[position] - tmp < half)
    {
        position++;
    }
    return position < size && sums[position] - tmp == half ? position : -1;
}

int max(const std::vector<uint64_t>& data, std::vector<uint64_t>& sums, int from, int to)
{
    if (from == to)
    {
        return 0;
    }
    int mid = middle(data, sums, from, to);
    if (mid == -1)
    {
        return 0;
    }
    else
    {
        int left = max(data, sums, from, mid);
        int right = max(data, sums, mid + 1, to);
        return 1 + (left > right ? left : right);
    }
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N, T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> N;
        std::vector<uint64_t> data(N, 0);
        std::vector<uint64_t> sums(N, 0);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> data[i];
        }
        sums[0] = data[0];
        for (int i = 1; i < N; ++i)
        {
            sums[i] = sums[i - 1] + data[i];
        }
        LOG(max(data, sums, 0, N - 1));
    }
    return 0;
}

