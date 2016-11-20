/*
 * Dynamic Programming
 * Author: Rafal Kozik
 */

#include "gtest/gtest.h"
#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

/*
 *   T O F O O D I E
 * T 1 / / / / / / /
 * O / 2 / 1 1 / / /
 * O / 1 / 1 2 / / /
 * D / / / / / 3 / /
 * Y / / / / / / / /
 *
 */

int longest(const std::string& s1, const std::string& s2)
{
    std::vector<std::vector<int>> helper(s1.size() + 1, std::vector<int>(s2.size() + 1, 0));
    int size1 = s1.size();
    int size2 = s2.size();
    int max = 0;
    for (int i = 1; i <= size1; ++i)
    {
        for (int j = 1; j <= size2; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                int value = helper[i - 1][j - 1] + 1;
                helper[i][j] = value;
                if (value > max)
                {
                    max = value;
                }
            }
        }
    }
    return max;
}

TEST(Strings, Test)
{
    EXPECT_EQ(longest("TOODY", "TOFOODIE"), 3);
}
