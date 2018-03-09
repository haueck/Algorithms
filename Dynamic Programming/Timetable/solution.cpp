/*
 * Codeforce - Timetable
 * http://codeforces.com/problemset/problem/946/D
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> dp1(n, std::vector<int>(k + 1));
    std::vector<std::vector<int>> dp2(n, std::vector<int>(k + 1, std::numeric_limits<int>::max()));
    for (auto i = 0; i < n; ++i)
    {
        std::string day;
        std::cin >> day;
        std::vector<std::vector<int>> freed(m, std::vector<int>(m, std::numeric_limits<int>::max()));
        int classes = 0;
        for (auto hour = 0; hour < m; ++hour)
        {
            if (day[hour] == '1')
            {
                ++classes;
                int skipped = 0;
                for (auto later = hour; later < m; ++later)
                {
                    if (day[later] == '1')
                    {
                        freed[hour][skipped] = later - hour + 1;
                        ++skipped;
                    }
                }
            }
        }
        for (auto skipped = classes - 1; skipped >= 0; --skipped)
        {
            auto inverted = classes - 1 - skipped;
            if (inverted > k)
            {
                break;
            }
            dp1[i][inverted] = std::numeric_limits<int>::max();
            for (auto row = 0; row < m; ++row)
            {
               dp1[i][inverted] = std::min(freed[row][skipped], dp1[i][inverted]);
            }
        }
    }
    for (auto skipped = 0; skipped < k + 1; ++skipped)
    {
        dp2[0][skipped] = dp1[0][skipped];
    }
    for (auto day = 1; day < n; ++day)
    {
        for (auto skipped = 0; skipped < k + 1; ++skipped)
        {
            for (auto skipped_today = 0; skipped_today <= skipped; ++skipped_today)
            {
                dp2[day][skipped] = std::min(dp2[day][skipped], dp2[day - 1][skipped - skipped_today] + dp1[day][skipped_today]);
            }
        }
    }
    LOG(dp2[n - 1][k]);
}

