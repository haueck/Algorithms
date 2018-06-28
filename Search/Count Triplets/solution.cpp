/*
 * HackerRank - Count Triplets
 * https://www.hackerrank.com/challenges/count-triplets-1/problem
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <unordered_map>

struct Index
{
    // The number of occurences of this element so far
    int64_t count{0};
    // How many times this element can be in the middle of a series
    int64_t middle{0};
};

int main()
{
    int64_t n, r;
    std::cin >> n >> r;
    std::vector<int> data(n);
    std::unordered_map<int,Index> index;
    for (auto& e : data)
    {
        std::cin >> e;
    }
    int64_t count = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        auto next = index.find(r * data[i]);
        auto& current = index[data[i]];
        if (next != index.end())
        {
            count += next->second.middle;
            current.middle += next->second.count;
        }
        current.count++;
    }
    std::cout << count << std::endl;
}
