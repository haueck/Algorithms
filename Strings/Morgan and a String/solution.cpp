/*
 * HackerRank - Morgan and a String
 * https://www.hackerrank.com/challenges/morgan-and-a-string/problem
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int t;
    std::cin >> t;
    std::cin.ignore(1, '\n');
    while (t--)
    {
        std::string a, b;
        std::getline(std::cin, a);
        std::getline(std::cin, b);
        a.push_back('Z' + 1);
        b.push_back('Z' + 1);
        auto i = 0u;
        auto j = 0u;
        std::string result;
        while (i + 1 < a.size() || j + 1 < b.size())
        {
            if (a[i] < b[j])
            {
                result.push_back(a[i]);
                ++i;
            }
            else if (a[i] > b[j])
            {
                result.push_back(b[j]);
                ++j;
            }
            else
            {
                auto ii = i;
                auto jj = j;
                while (ii + 1 < a.size() && jj + 1 < b.size() && a[ii] == b[jj])
                {
                    ++ii;
                    ++jj;
                }
                auto remaining_a = a.size() - ii - 1;
                auto remaining_b = b.size() - jj - 1;
                if (remaining_b == 0)
                {
                    result.push_back(a[i]);
                    ++i;
                }
                else if (remaining_a == 0)
                {
                    result.push_back(b[j]);
                    ++j;
                }
                else if (a[ii] < b[jj])
                {
                    result.append(a, i, ii - i);
                    i = ii;
                }
                else
                {
                    result.append(b, j, jj - j);
                    j = jj;
                }
            }
        }
        LOG(result);
    }
}

