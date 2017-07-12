/*
 * HackerRank - Arithmetic Expressions
 * https://www.hackerrank.com/challenges/arithmetic-expressions
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int math_modulo(int a)
{
    int r = a % 101;
    return r < 0 ? r + 101 : r;
}

bool find_first_divisible_by_101(std::vector<int>& data, std::vector<std::vector<bool>>& helper, int current)
{
    for (int i = 1; i < 101; ++i)
    {
        if (helper[current - 1][i])
        {
            int addition = math_modulo(i + data[current]);
            int subtraction = math_modulo(i - data[current]);
            int multiplication = math_modulo(i * data[current]);
            if (addition == 0 || subtraction == 0 || multiplication == 0)
            {
                return true;
            }
            helper[current][addition] = true;
            helper[current][subtraction] = true;
            helper[current][multiplication] = true;
        }
    }
    return false;
}

char recreate_path(std::vector<int>& data, std::vector<std::vector<bool>>& helper, int current, int& current_modulo)
{
    for (int i = 1; i < 101; ++i)
    {
        if (helper[current - 1][i])
        {
            int addition = math_modulo(i + data[current]);
            int subtraction = math_modulo(i - data[current]);
            int multiplication = math_modulo(i * data[current]);
            if (addition == current_modulo)
            {
                current_modulo = i;
                return '+';
            }
            else if (subtraction == current_modulo)
            {
                current_modulo = i;
                return '-';
            }
            else if (multiplication == current_modulo)
            {
                current_modulo = i;
                return '*';
            }
        }
    }
    return '#';
}

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> data(N);
    // The helper array holds modulos of outcomes of all possible arithmetic expressions.
    // helper[7][2] = true means that it is possible to create an arithmetic expression
    // from first 8 (7 + 1) numbers which outcome modulo 101 will be 2.
    std::vector<std::vector<bool>> helper(N, std::vector<bool>(101));
    for (int i = 0; i < N; ++i)
    {
        std::cin >> data[i];
    }
    helper[0][data[0]] = true;
    // It is enough that we find a way to create a number divisible by 101 from K first numbers.
    // That number can be multiplied by the rest of the numbers and it will be still divisible by 101.
    int current = 0;
    bool found = false;
    while (!found)
    {
        ++current;
        found = find_first_divisible_by_101(data, helper, current);
    }
    std::string result(N - (current + 1), '*');
    // Now we know that we can create a number divisble by 101 from 'current' first numbers.
    // The helper array holds only modulos of outcomes of all possible arithmetic expressions,
    // so we need to recreate a path, how we got to that number.
    // current_modulo is 0 because the current number is divisible by 101.
    int current_modulo = 0;
    while (current > 0)
    {
        auto c = recreate_path(data, helper, current, current_modulo);
        result.push_back(c);
        --current;
    }
    std::reverse(result.begin(), result.end());
    for (int i = 0; i < N - 1; ++i)
    {
        std::cout << data[i] << result[i];
    }
    std::cout << data[N - 1] << std::endl;
}

