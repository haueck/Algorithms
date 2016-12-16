/*
 * HackerRank - Caesar Cipher
 * Strings
 * https://www.hackerrank.com/challenges/caesar-cipher-1
 * Author: Rafal Kozik
 */

#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int chars = 'z' - 'a' + 1;
    int S, K;
    std::string string;
    std::cin >> S;
    std::cin.ignore(1, '\n');
    std::getline(std::cin, string);
    std::cin >> K;
    for (auto c : string)
    {
        if (c >= 'a' && c <= 'z')
        {
            std::cout << static_cast<char>('a' + (c - 'a' + K) % chars);
        }
        else if (c >= 'A' && c <= 'Z')
        {
            std::cout << static_cast<char>('A' + (c - 'A' + K) % chars);
        }
        else
        {
            std::cout << c;
        }
    }
    std::cout << std::endl;
    return 0;
}

