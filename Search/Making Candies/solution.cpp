/*
 * HackerRank - Making Candies
 * https://www.hackerrank.com/challenges/making-candies
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

#define LOG(x) std::cout << x << std::endl

void invest(uint64_t investment, uint64_t& m, uint64_t& w)
{
    uint64_t diff;
    if (m > w)
    {
        diff = std::min(investment, m - w);
        w += diff;
    }
    else
    {
        diff = std::min(investment, w - m);
        m += diff;
    }
    investment -= diff;
    auto half = investment / 2;
    w += half;
    m += investment - half;
}

uint64_t time_to_next_investment(uint64_t candies, uint64_t p, uint64_t m, uint64_t w)
{
    return candies < p ? std::ceil(static_cast<long double>(p - candies) / m / w) : 1;
}

uint64_t time_to_finish(uint64_t candies, uint64_t n, uint64_t m, uint64_t w)
{
    return candies < n ? std::ceil(static_cast<long double>(n - candies) / m / w) : 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    uint64_t m, w, p, n;
    uint64_t candies = 0;
    uint64_t time = 0;
    std::cin >> m >> w >> p >> n;
    while (true)
    {
        auto ttni = time_to_next_investment(candies, p, m, w);
        auto ttf = time_to_finish(candies, n, m, w);
        candies += ttni * m * w;
        auto investment = candies / p;
        candies -= investment * p;
        invest(investment, m, w);
        if (time + ttni + time_to_finish(candies, n, m, w) > time + ttf)
        {
            time += ttf;
            break;
        }
        else
        {
            time += ttni;
        }
    }
    LOG(time);
}

