/*
 * HackerRank - The Chosen One
 * https://www.hackerrank.com/contests/101hack45/challenges/the-chosen-one
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

uint64_t gcd(uint64_t a, uint64_t b)
{
    if (b > a)
    {
        std::swap(a, b);
    }
    while (b != 0)
    {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    std::vector<uint64_t> data(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> data[i];
    }
    if (N == 1)
    {
        LOG(data[0] + 1);
        return 0;
    }
    std::vector<uint64_t> gcd_0_to_i(N);
    std::vector<uint64_t> gcd_i_to_n(N);
    for (int i = 0; i < N - 1; ++i)
    {
        gcd_0_to_i[i + 1] = gcd(data[i], gcd_0_to_i[i]);
        gcd_i_to_n[N - 2 - i] = gcd(data[N - 1 - i], gcd_i_to_n[N - 1 - i]);
    }
    for (int i = 0; i < N; ++i)
    {
        auto global_gcd = gcd(gcd_0_to_i[i], gcd_i_to_n[i]);
        if (data[i] % global_gcd != 0)
        {
            LOG(global_gcd);
            return 0;
        }
    }
    return 0;
}

