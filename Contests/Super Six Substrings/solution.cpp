/*
 * HackerRank - Super Six Substrings
 * https://www.hackerrank.com/contests/hourrank-18/challenges/super-six-substrings
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>

std::vector<std::vector<int>> cache;
    
uint64_t even_divisible_by_3_with_reminder(std::size_t i, int reminder, const std::string& digits)
{
    if (i == digits.size())
    {
        return 0; 
    }
    if (cache[i][reminder] == -1)
    {
        auto  value = digits[i] - '0';
        auto sum_modulo_3 = (value + reminder) % 3;
        // Is the number ending with the current digit divisible by 6?
        auto current = sum_modulo_3 == 0 && value % 2 == 0;
        // Count other numbers ending at positions i + 1, i + 2, etc.
        auto others = even_divisible_by_3_with_reminder(i + 1, sum_modulo_3, digits);
        cache[i][reminder] = current + others;
	}
    return cache[i][reminder];
}

int main()
{
    std::string digits;
    std::cin >> digits;
    uint64_t answer = 0;
    cache = std::vector<std::vector<int>>(digits.size(), std::vector<int>(3, -1));
    for (auto i = 0u; i < digits.size(); ++i)
    {
        if (digits[i] == '0')
        {
            answer++; 
        }
        else
        {
            // A number is divisible by 3 if the sum of its digits is divisible by 3.
            // However, when we add a digit to a number we don't need the sum of the existing digits,
            // it is enough that we know (sum % 3). For example, we have 1000 digits and we calculate
            // numbers starting with a digit at position 0, 1, 2, etc. When we reach position 100,
            // (sum % 3) can have only 3 unique values - 0, 1, 2. The total sum would be always
            // different and there would be no way to memoize anything.
            answer += even_divisible_by_3_with_reminder(i, 0, digits);
        }
    }
    std::cout << answer << std::endl; 
}
