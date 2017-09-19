/*
 * HackerRank - Abbreviation
 * https://www.hackerrank.com/challenges/abbr
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

bool find(std::string& a, std::string& b, int i, int j, std::vector<std::vector<bool>>& deadend)
{
    if (!deadend[i][j])
    {
        bool found;
        if (j == b.size())
        {
            found = true;
            for (int k = i; k < a.size(); ++k)
            {
                if (std::isupper(a[k]))
                {
                    found = false;
                }
            }
        }
        else if (i == a.size())
        {
            found = false;
        }
        else if (a[i] == b[j])
        {
            found = find(a, b, i + 1, j + 1, deadend);
        }
        else if (std::isupper(a[i]))
        {
            found = false;
        }
        else if (std::toupper(a[i]) == b[j])
        {
            found = find(a, b, i + 1, j + 1, deadend);
            if (!found)
            {
                found = find(a, b, i + 1, j, deadend);
            }
        }
        else
        {
            return find(a, b, i + 1, j, deadend);
        }
        if (!found)
        {
            deadend[i][j] = true;
        }
    }
    return deadend[i][j] ? false : true;
}

int main()
{
    int T;
    std::cin >> T;
    std::cin.ignore(1, '\n');
    while (T--)
    {
        std::string a, b;
        std::cin >> a >> b;
        std::vector<std::vector<bool>> deadend(a.size() + 1, std::vector<bool>(b.size() + 1));
        LOG((find(a, b, 0, 0, deadend) ? "YES" : "NO"));
    }
}

