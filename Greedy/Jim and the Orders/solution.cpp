/*
 * HackerRank - Jim and the Orders
 * Greedy
 * https://www.hackerrank.com/challenges/jim-and-the-orders
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    std::vector<std::pair<int,int>> queue;
    queue.reserve(N);
    for (int i = 0; i < N; ++i)
    {
        int t, d;
        std::cin >> t >> d;
        queue.emplace_back(t + d, i + 1);
    }
    std::sort(queue.begin(), queue.end());
    for (auto& e : queue)
    {
        std::cout << e.second << " ";
    }
    std::cout << std::endl;
    return 0;
}

