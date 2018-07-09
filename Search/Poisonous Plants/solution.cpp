/*
 * HackerRank - Poisonous Plants
 * https://www.hackerrank.com/challenges/poisonous-plants/problem
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
    std::vector<int> plants(n);
    for (auto& plant : plants)
    {
        std::cin >> plant;
    }
    // I will replace volume of pesticide with height in the comments
    // Plants in increasing height only
    std::stack<int> stack;
    // Number of days it takes i-th plant to die
    std::vector<int> lifespan(n);
    // Plants on the right, which are higher than the current lowest, will die sooner or later
    auto min = plants[0];
    auto result = 0;
    for (auto i = 1; i < n; i++)
    {
        if (plants[i] > plants[i - 1])
        {
            // It will die on the first day
            lifespan[i] = 1;
        }
        else
        {
            // If the current plant has height 7 and there is a lower plant somewhere on the left
            // it will die one day. However, it will live as long as there are higher plants between them.
            // In this loop, we will remove all those higher plants. The current plant is a bottleneck
            // anyway, so it is enough to know the lifespan of the current plant.
            while (!stack.empty() && plants[stack.top()] >= plants[i])
            {
                // If the plant is lower or equal to the lowest one, it will not die, so skip it
                if (plants[i] > min)
                {
                    lifespan[i] = std::max(lifespan[i], lifespan[stack.top()] + 1);
                }
                stack.pop();
            }
        }
        min = std::min(plants[i], min);
        result = std::max(result, lifespan[i]);
        stack.push(i);
    }
    LOG(result);
}
