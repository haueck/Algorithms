/*
 * HackerRank - Counting Special Sub-Cubes
 * https://www.hackerrank.com/challenges/counting-special-sub-cubes/problem
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        std::cin >> n;
        auto n2 = n * n;
        auto n3 = n * n * n;
        std::vector<int> a(n3);
        int result = 0;
        for (auto i = 0; i < n3; ++i)
        {
            std::cin >> a[i];
            if (a[i] == 1)
            {
                ++result;
            }
        }
        std::cout << result << " ";
        for (auto k = 2; k <= n; ++k)
        {
            result = 0;
            for (auto x = 0; x < n - k + 1; ++x)
            {
                for (auto y = 0; y < n - k + 1; ++y)
                {
                    for (auto z = 0; z < n - k + 1; ++z)
                    {
                        a[x * n2 + y * n + z] = std::max({
                            a[x * n2 + y * n + z], a[(x + 1) * n2 + y * n + z], a[x * n2 + (y + 1) * n + z],
                            a[x * n2 + y * n + z + 1], a[(x + 1) * n2 + (y + 1) * n + z], a[(x + 1) * n2 + y * n + z + 1],
                            a[x * n2 + (y + 1) * n + z + 1], a[(x + 1) * n2 + (y + 1) * n + z + 1]
                        });
                        if (a[x * n2 + y * n + z] == k)
                        {
                            ++result;
                        }
                    }
                }
            }
            std::cout << result << " ";
        }
        std::cout << std::endl;
    }
}

