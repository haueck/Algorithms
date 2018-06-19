/*
 * Non-Divisible Subset
 * https://www.hackerrank.com/challenges/non-divisible-subset/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> S(n);
    for (auto i = 0; i < n; ++i)
    {
        std::cin >> S[i];
    }
    int result = 0;
    std::vector<int> modulos(k);
    for (auto s : S)
    {
        modulos[s % k]++;
    }
    if (modulos[0] > 0)
    {
        ++result;
    }
    if (k % 2 == 0 && modulos[k / 2] > 0)
    {
        ++result;
    }
    for (int i = 1; i < static_cast<int>((k + 1) / 2); ++i)
    {
        result += std::max(modulos[i], modulos[k - i]);
    }
    LOG(result);
}
