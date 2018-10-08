/*
 * Codeforces - Sequence Transformation
 * http://codeforces.com/contest/1059/problem/C
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> result;
    int gcd = 1;
    int max = n;
    while (n > 1)
    {
        int count = (n + 1) / 2;
        result.insert(result.end(), count, gcd);
        max = n * gcd;
        gcd *= 2;
        n /= 2;
    }
    result.push_back(max);
    for (auto e : result)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

