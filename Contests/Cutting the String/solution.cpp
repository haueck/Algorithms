/*
 * HackerRank - Cutting the String
 * https://www.hackerrank.com/contests/101hack50/challenges/cutting-the-string/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <string.h>

#define LOG(x) std::cout << x << std::endl

uint64_t arithmetic_series_floor(int begin, int end, int divisor)
{
    if (begin >= end)
    {
        return 0;
    }
    int lowest_first = (begin + (divisor - 1)) / divisor;
    int highest_last = end / divisor - 1;
    int head = (end % divisor);
    int tail = (divisor - (begin % divisor)) % divisor;
    if (lowest_first <= highest_last)
    {
        // airtmetic_series_floor(4, 13, 3)
        // 4 / 3 + 5 / 3 + 6 / 3 + 7 / 3 + 8 / 3 + 9 / 3 + 10 / 3 + 11 / 3 + 12 / 3 =
        // 1 + 1 + 2 + 2 + 2 + 3 + 3 + 3 + 4 = 11
        //         ^                   ^
        //    lowest_first       highest_last
        // There are all three 2s and 3s so we can compute airthetic series and multiply it by 3
        // sum = 3 * (2 + 3)
        uint64_t sum = divisor * (highest_last - lowest_first + 1) * ((lowest_first + highest_last) / 2.0);
        // Add those two 1 and one 4
        return tail * ((end - 1) / divisor) + sum + head * (begin / divisor);
    }
    else if (lowest_first - highest_last == 1)
    {
        // airtmetic_series_floor(4, 8, 3)
        // 4 / 3 + 5 / 3 + 6 / 3 + 7 / 3 = 1 + 1 + 2 + 2 = 6
        //                                     ^   ^
        //                          highest_last   lowest_first       
        return lowest_first * head + tail * highest_last;
    }
    else
    {
        // airtmetic_series_floor(11, 13, 5)
        // 0 * (9 / 5) + 0 * (10 / 5) + 11 / 5 + 12 / 5 + 0 * (13 / 5) + 0 * (14 / 5) + 0 * (15 / 5) =
        // 0 * 1 + 0 * 2 + 2 + 2 + 0 * 2 + 0 * 2 + 0 * 3 = 10
        //     ^                                       ^
        // highest_last                           lowest_first
        return ((head + tail) % divisor) * (lowest_first - 1);
    }
}

uint64_t count_composites(std::vector<std::vector<bool>>& visited, int position, int size, int count, int base_size)
{
    if (size < 2)
    {
        return 0;
    }
    uint64_t result = 0;
    auto max = std::min(1 + count - size, size);
    // For example, we found a group of 7 "a" (count = 7, base_size = 1)
    // This loop will iterate over following groups of "aaa" (size = 3)
    for (int i = 0; i < max; ++i)
    {
        // aaaaaaa - initial string
        // aaaaaa  - i = 0, fitting = 2
        //  aaaaaa - i = 1, fitting = 2
        //   aaa   - i = 2, fitting = 1
        int fitting = (count - i) / size;
        result += fitting * fitting;
        for (int j = 0; j < fitting; ++j)
        {
            visited[position + i * base_size + j * size * base_size][size * base_size] = true;
        }
        // I forgot why I needed this arithemtic series
        result += 2 * fitting * arithmetic_series_floor(count - max + 1, count - (i + 1) + 1, size);
    }
    return result + count_composites(visited, position, size - 1, count, base_size);
}

uint64_t count(const std::string& s)
{
    uint64_t result = 0;
    std::vector<std::vector<bool>> visited(s.size(), std::vector<bool>(s.size() + 1, false));
    // We are only interested in repeating patterns, we can exchange them without changing the whole string
    // For example, in s = "abababab" we can take any "ab" and put it in 4 different places
    for (size_t i = 0; i < s.size(); ++i)
    {
        for (auto size = 1; i + size <= s.size(); ++size)
        {
            if (!visited[i][size])
            {
                int count = 1;
                // For i = 0 (current position in s) and size = 2 this loop will find that "ab" is repeated 4 times
                // As we count all possible cuts and inserts for this group, we mark "ab" at positions 2, 4 and 6 as visited
                while (count * size + i + size <= s.size() && strncmp(&s[i], &s[count * size + i], size) == 0)
                {
                    visited[count * size + i][size] = true;
                    ++count;
                }
                // (count * count) counts all moves of each "ab" to positions of all "ab"s, including its own position.
                // If we have a group of repeating strings, we can create other groups of repeating strings from it.
                // For example, from four "ab" we can create two "abab", lets count them.
                result += count * count + count_composites(visited, i, count - 1, count, size);
            }
        }
    }
    return result;
}

int main()
{
    std::string s;
    std::cin >> s;
    LOG(count(s));
}

