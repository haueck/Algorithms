/*
 * HackerRank - Clique
 * https://www.hackerrank.com/challenges/clique
 * Author: Rafal Kozik
 */

#include <iostream>
#include <cmath>

#define LOG(x) std::cout << x << std::endl;

template <class C>
int partition(int first, int last, C c)
{
    while (last >= first)
    {
        auto count = last - first + 1;
        auto middle = first + (count >> 1);
        if (c(middle))
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return first;
}

class Turan
{
public:
    Turan(int n, int m) : n(n), m(m) { }
    bool operator()(int k) const
    {
        int nk_ceil = std::ceil(static_cast<float>(n) / k);
        int nk_floor = std::floor(static_cast<float>(n) / k);
        int mod = n % k;
        return m <= (n * n - mod * nk_ceil * nk_ceil - (k - mod) * nk_floor * nk_floor) / 2;
    }
    int n, m;
};

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int N, M;
        std::cin >> N >> M;
        LOG(partition(1, N, Turan(N, M)));
    }
}

