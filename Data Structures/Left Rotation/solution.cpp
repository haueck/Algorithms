/*
 * HackerRank - Left Rotation
 * https://www.hackerrank.com/challenges/array-left-rotation
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

int gcd(int a, int b)
{
    while (b != 0)
    {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

int64_t lcm(int64_t a, int64_t b)
{
    return (a * b) / gcd(a, b);
}

int next(int i, int d, int size)
{
    int n = i - d;
    return n < 0 ? size + n : n;
}

int main()
{
    int n, d;
    std::cin >> n >> d;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
       std::cin >> a[i];
    }
    int inner_loop = lcm(a.size(), d) / d;
    int outer_loop = a.size() / inner_loop;
    for (int i = 0; i < outer_loop; ++i)
    {
        int value = a[i];
        int current = i;
        for (int j = 0; j < inner_loop; ++j)
        {
            current = next(current, d, a.size());
            int temp = a[current];
            a[current] = value;
            value = temp;
        }
    }
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

