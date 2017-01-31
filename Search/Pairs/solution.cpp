/*
 * HackerRank - Pairs
 * https://www.hackerrank.com/challenges/pairs
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    uint32_t N, K;
    std::cin >> N >> K;
    std::vector<uint32_t> data(N);
    for (auto i = 0u; i < N; ++i)
    {
        std::cin >> data[i];
    }
    std::sort(data.begin(), data.end());
    auto first = 0u, second = 0u, result = 0u;
    while (true)
    {
        while (second < N && data[second] < data[first] + K)
        {
            ++second;
        }
        if (second == N)
        {
            break;
        }
        if (data[second] == data[first] + K)
        {
            ++result;
            ++second;
        }
        ++first;
    }
    LOG(result);
    return 0;
}
