/*
 * HackerRank - Mr. X and His Shots
 * https://www.hackerrank.com/challenges/x-and-his-shots
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<std::pair<int,int>> shots(N);
    std::vector<int> starts(M), ends(M);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> shots[i].first >> shots[i].second;
    }
    for (int i = 0; i < M; ++i)
    {
        std::cin >> starts[i] >> ends[i];
    }
    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());
    uint64_t result = 0;
    for (int i = 0; i < N; ++i)
    {
        auto included = std::distance(starts.begin(), std::upper_bound(starts.begin(), starts.end(), shots[i].second));
        auto excluded = std::distance(ends.begin(), std::upper_bound(ends.begin(), ends.end(), shots[i].first - 1));
        result += included - excluded;
    }
    LOG(result);
}

