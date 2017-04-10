/*
 *
 *
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        std::cin >> n;
        std::vector<std::pair<int,int>> array(n);
        for (int i = 0; i < n; i++)
        {
            std::cin >> array[i].first;
            array[i].second = i;
        }
        std::sort(array.begin(), array.end(), std::greater<std::pair<int,int>>());
        int end = n;
        bool bob = true;
        for (int i = 0; i < n; i++)
        {
            if (array[i].second < end)
            {
                end = array[i].second;
                bob = !bob;
            }
        }
        LOG((bob ? "ANDY" : "BOB"));
    }
}

