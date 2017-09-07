/*
 * HackerRank - Candies
 * https://www.hackerrank.com/challenges/candies
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <numeric>

#define LOG(x) std::cout << x << std::endl

void candies(std::vector<int>& children, std::vector<uint64_t>& count, uint32_t current)
{
    if (current + 1 == children.size())
    {
        return;
    }
    if (children[current + 1] < children[current])
    {
        candies(children, count, current + 1);
        if (count[current + 1] >= count[current])
        {
            count[current] = count[current + 1] + 1;
        }
    }
    else if (children[current + 1] == children[current])
    {
        candies(children, count, current + 1);
    }
    else
    {
        count[current + 1] = count[current] + 1;
        candies(children, count, current + 1);
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> children(n);
    std::vector<uint64_t> count(n, 1);
    for (int i = 0; i < n; i++)
    {
       std::cin >> children[i];
    }
    candies(children, count, 0);
    LOG(std::accumulate(count.begin(), count.end(), 0ull));
}

