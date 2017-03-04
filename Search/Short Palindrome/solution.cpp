/*
 * HackerRank - Short Palindrome
 * https://www.hackerrank.com/challenges/short-palindrome
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <string>

#define LOG(x) std::cout << x << std::endl

const int mod = 1e9 + 7;

int main()
{
    uint64_t answer = 0;
    std::string string;
    std::cin >> string;
    // Frequency of letters
    std::vector<uint64_t> letters(26);
    // Frequency of pairs
    std::vector<uint64_t> pairs(26 * 26);
    // Frequency of triples starting with character c,
    // followed by two the same characters, e.g. cxx
    std::vector<uint64_t> triples(26);

    for (auto c : string)
    {
        int idx = c - 'a';

        // Add all triples that will become palindromes
        // after adding character c at the end
        answer = (answer + triples[idx]) % mod;

        // Iterate over all pairs ending with character c
        // to create triples xcc
        for (auto i = 0; i < 26; ++i)
        {
            int index = i * 26 + idx;
            triples[i] += pairs[index];
        }

        // Create pairs ending with c
        for (auto i = 0; i < 26; ++i)
        {
            int index = i * 26 + idx;
            pairs[index] += letters[i];
        }

        ++letters[idx];
    }
    LOG(answer);
}

