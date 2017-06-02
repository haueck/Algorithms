/*
 * HackerRank - The Power Sum
 * https://www.hackerrank.com/challenges/the-power-sum
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <cmath>

#define LOG(x) std::cout << x << std::endl

void find_factors(std::vector<int>& factors, std::size_t position, int value, int& count)
{
    if (value < 0)
    {
        return;
    }
    else if (value == 0)
    {
        ++count;
        return;
    }
    if (position == factors.size())
    {
        return;
    }
    find_factors(factors, position + 1, value, count);
    find_factors(factors, position + 1, value - factors[position], count);
}

int main()
{
    int X, N;
    std::cin >> X >> N;
    std::vector<int> factors;
    int number = 1;
    while (true)
    {
        int power = std::pow(number, N);
        if (power > X)
        {
            break;
        }
        factors.push_back(power);
        number++;
    }
    int count = 0;
    find_factors(factors, 0, X, count);
    LOG(count);
}

