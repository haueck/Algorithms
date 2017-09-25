/*
 * HackerRank - Truck Tour
 * https://www.hackerrank.com/challenges/truck-tour/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int N;
    std::cin >> N;
    std::vector<std::pair<int,int>> stations(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> stations[i].first >> stations[i].second;
    }
    int tank = 0;
    int start = 0;
    int position = 0;
    while ((position + 1) % N != start)
    {
        tank += stations[position].first;
        while (stations[position].second > tank)
        {
            if (start == position)
            {
                start = (start + 1) % N;
                position = start;
                tank = stations[position].first;
            }
            else
            {
                tank -= stations[start].first;
                tank += stations[start].second;
                start = (start + 1) % N;
            }
        }
        tank -= stations[position].second;
        position = (position + 1) % N;
    }
    LOG(start);
}

