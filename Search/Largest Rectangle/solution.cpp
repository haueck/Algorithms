/*
 * HackerRank - Largest Rectangle
 * https://www.hackerrank.com/challenges/largest-rectangle
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <stack>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n;
    std::cin >> n;
    std::vector<uint64_t> h(n);
    for (int i = 0; i < n; i++)
    {
       std::cin >> h[i];
    }
    std::stack<int> stack;
    uint64_t max_area = 0;
    for (int i = 0; i < n; ++i)
    {
        if (stack.empty() || h[i] > h[stack.top()])
        {
            stack.push(i);
        }
        else
        {
            while (!stack.empty() && h[stack.top()] > h[i])
            {
                auto idx = stack.top();
                stack.pop();
                auto height = h[idx];
                auto beginning = stack.empty() ? 0 : stack.top() + 1;
                auto width = i - beginning;
                max_area = std::max(max_area, height * width);
            }
            if (stack.empty() || h[stack.top()] <= h[i])
            {
                stack.push(i);
            }
        }
    }
    while (!stack.empty())
    {
        auto idx = stack.top();
        stack.pop();
        auto height = h[idx];
        auto beginning = stack.empty() ? 0 : stack.top() + 1;
        auto width = n - beginning;
        max_area = std::max(max_area, height * width);
    }
    LOG(max_area);
}

