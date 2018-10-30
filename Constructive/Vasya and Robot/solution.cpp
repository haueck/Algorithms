/*
 * Codeforces - Vasya and Robot
 * http://codeforces.com/contest/1073/problem/C
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

struct Vector
{
    int x{0};
    int y{0};

    void add(Vector o)
    {
        x += o.x;
        y += o.y;
    }

    void subtract(Vector o)
    {
        x -= o.x;
        y -= o.y;
    }
};

bool is_reachable(Vector p, int n)
{
    Vector a{ std::abs(p.x), std::abs(p.y) };
    if (n < a.x + a.y || (n - a.x - a.y) % 2 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Vector to_vector(char c)
{
    if (c == 'U')
    {
        return { 0, 1 };
    }
    else if (c == 'D')
    {
        return { 0, -1 };
    }
    else if (c == 'R')
    {
        return { 1, 0 };
    }
    else
    {
        return { -1, 0 };
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::string s;
    Vector target, current, diff;
    for (int i = 0; i < n; ++i)
    {
        char c;
        std::cin >> c;
        s.push_back(c);
        current.add(to_vector(c));
    }
    std::cin >> target.x >> target.y;
    diff.x = target.x - current.x;
    diff.y = target.y - current.y;
    int right = -1;
    int shortest = n + 1;
    for (int left = 0; left < n; ++left)
    {
        if (left > 0)
        {
            diff.subtract(to_vector(s[left - 1]));
        }
        while (right + 1 < n && !is_reachable(diff, right - left + 1))
        {
            ++right;
            diff.add(to_vector(s[right]));
        }
        if (!is_reachable(diff, right - left + 1))
        {
            break;
        }
        shortest = std::min(shortest, right - left + 1);
    }
    LOG((shortest == n + 1 ? -1 : shortest));
}

