/*
 * HackerRank - Queries with Fixed Length
 * https://www.hackerrank.com/challenges/queries-with-fixed-length/problem
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <queue>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> data(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data[i];
    }
    while (q--)
    {
        int d;
        std::cin >> d;
        std::priority_queue<std::pair<int,int>> max_heap;
        std::priority_queue<int,std::vector<int>,std::greater<int>> min_heap;
        for (int i = 0; i < d; ++i)
        {
            max_heap.emplace(data[i], i);
        }
        min_heap.push(max_heap.top().first);
        for (int i = d; i < n; ++i)
        {
            max_heap.emplace(data[i], i);
            while (max_heap.top().second <= i - d)
            {
                max_heap.pop();
            }
            min_heap.push(max_heap.top().first);
        }
        LOG(min_heap.top());
    }
}

