/*
 * HackerRank - Cipher
 * https://www.hackerrank.com/challenges/cipher
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int N, K;
    std::cin >> N >> K;
    std::string encoded;
    std::cin >> encoded;
    std::vector<bool> decoded(N);
    decoded[0] = encoded[0] == '1';
    bool previous = false;
    for (int i = 1; i < N; ++i)
    {
        if (i - K >= 0)
        {
            previous ^= decoded[i - K];
        }
        previous ^= decoded[i - 1];
        decoded[i] = (encoded[i] == '1') ^ previous;
    }
    for (auto e : decoded)
    {
        std::cout << e;
    }
}

