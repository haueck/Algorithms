/*
 * HackerRank - Goodland Electricity
 * https://www.hackerrank.com/challenges/pylons
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n, k;
    std::cin >> n >> k;
    int last_tower = -1 * k;
    int last_switched_on = last_tower;
    int switched_on = 0;
    for (int i = 0; i < n; ++i)
    {
        int tower;
        std::cin >> tower;
        if (tower == 1)
        {
            last_tower = i;
        }
        if (last_switched_on + 2 * k - 1 == i)
        {
            if (last_switched_on == last_tower)
            {
                LOG(-1);
                return 0;
            }
            else
            {
                last_switched_on = last_tower;
                switched_on++;
            }
        }
    }
    if (last_switched_on + k < n)
    {
        if (last_tower + k < n)
        {
            LOG(-1);
        }
        else
        {
            switched_on++;
        }
    }
    LOG(switched_on);
}

