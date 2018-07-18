/*
 * Min Max Riddle
 * https://www.hackerrank.com/challenges/min-max-riddle/problem
 * Author: Rafal Kozik
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::pair<int,int>> data(n);
    for (auto i = 0; i < n; ++i)
    {
        std::cin >> data[i].first;
        data[i].second = i + 1;
    }
    std::map<int,int> map;
    map[0] = -1;
    map[n + 1] = -1;
    std::sort(data.begin(), data.end());
    std::vector<int> app(n + 1);
    for (auto i = 0; i < n; ++i)
    {
        /*
         * When an element is inserted into the search tree, all elements
         * in the tree are lower or equal to the current element.
         * Elements in the tree are sorted by the orignal index,
         * so they are in the same order as in the orignal array.
         * Next element in the tree will be the closest lower or equal element on the right.
         * Previous element in the tree will be the closest lower or equal element on the left.
         * After skip equal elements and we can find first lower element.
         */
        auto it = map.emplace(data[i].second, data[i].first).first;
        auto next = std::next(it);
        auto prev = std::prev(it);
        while (next->second == data[i].first)
        {
            next = std::next(next);
        }
        while (prev->second == data[i].first)
        {
            prev = std::prev(prev);
        }
        /*
         * This element will first appear when the window size is equal to this value.
         * When the window size will be greater, lower element on the left or right will be picked.
         */
        auto length = next->first - prev->first - 1;
        app[length] = std::max(app[length], data[i].first);
    }
    for (int i = app.size() - 2; i >= 0; --i)
    {
        /*
         * If an element appears in the window of size x, it will also appear in all smaller windows.
         * So need to make sure that we always pick the greatest element of all possible elements.
         */
        app[i] = std::max(app[i + 1], app[i]);
    }
    for (auto i = 1; i < n + 1; ++i)
    {
        std::cout << app[i] << " ";
    }
    std::cout << std::endl;
}
