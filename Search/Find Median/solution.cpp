/*
 * Find the Media
 * https://www.hackerrank.com/challenges/find-the-median
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int pivot(std::vector<int>& data, int left, int right)
{
    int current = left;
    for (int i = left; i < right; ++i)
    {
        if (data[i] < data[right])
        {
            std::swap(data[i], data[current]);
            ++current;
        }
    }
    std::swap(data[current], data[right]);
    return current;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data[i];
    }
    int left = 0;
    int right = n - 1;
    while (true)
    {
        int p = pivot(data, left, right);
        if (p == n / 2)
        {
            LOG(data[p]);
            return 0;
        }
        else if (p < n / 2)
        {
            left = p + 1;
        }
        else
        {
            right = p - 1;
        }
    }
}
