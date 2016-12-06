/*
 * HackerRank - Gemstones
 * Strings
 * https://www.hackerrank.com/challenges/gem-stones
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N = 0;
    std::cin >> N;
    std::cin.ignore(1, '\n');
    std::vector<int> elements('z' - 'a' + 1, 0);
    for (int i = 0; i < N; ++i)
    {
        std::string rock;
        std::getline(std::cin, rock);
        for (uint32_t j = 0; j < rock.size(); ++j)
        {
            if (elements[rock[j] - 'a'] == i)
            {
                ++elements[rock[j] - 'a'];
            }
        }
    }
    LOG(std::count_if(elements.begin(), elements.end(), [N](int c){ return c == N; }));
    return 0;
}
