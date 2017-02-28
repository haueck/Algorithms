/*
 * HackerRank - Richie Rich
 * https://www.hackerrank.com/challenges/richie-rich
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <string>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int n, k;
    std::string number;
    std::cin >> n >> k >> number;
    int required = 0;
    int left = 0;
    int right = number.size() - 1;
    while (left < right)
    {
        if (number[left] != number[right])
        {
            ++required;
        }
        ++left;
        --right;
    }
    if (required > k)
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        int current = 0;
        int bonus = k - required;
        while (current < number.size())
        {
            int matching = number.size() - 1 - current;
            if (current == matching)
            {
                if (bonus >= 1)
                {
                    number[matching] = '9';
                    --bonus;
                }
            }
            else if (number[current] == number[matching])
            {
                if (number[current] != '9' && bonus >= 2)
                {
                    number[current] = '9';
                    number[matching] = '9';
                    bonus -= 2;
                }
            }
            else
            {
                if (std::max(number[current], number[matching]) != '9' && bonus >= 1)
                {
                    number[current] = '9';
                    number[matching] = '9';
                    --bonus;
                }
                else if (number[current] < number[matching])
                {
                    number[current] = number[matching];
                }
            }
            ++current;
        }
        std::cout << number << std::endl;
    }
    return 0;
}

