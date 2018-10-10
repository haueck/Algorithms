/*
 * Codeforces - Nature Reserve
 * http://codeforces.com/contest/1059/problem/D
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

const double eps = 1e-7;

struct Point
{
    Point() { }
    Point(double x, double y) : x(x), y(y) { }
    double x{0};
    double y{0};
};

struct Circle
{
    Circle(double x, double y, double r) : x(x), y(y), r(r) { }
    double x{0};
    double y{0};
    double r{0};
};

struct Intersection
{
    Point p1;
    Point p2;
    bool exists{false};
};

Intersection circle_line_intersection(Point p1, Point p2, Circle circle)
{
    // http://mathworld.wolfram.com/Two-PointForm.html
    // http://www.analyzemath.com/CircleEq/circle_line_intersection.html
    auto slope = (p2.y - p1.y) / (p2.x - p1.x);
    auto helper = p1.y - slope * p1.x - circle.y;
    auto a = slope * slope + 1;
    auto b = 2 * (slope * helper - circle.x);
    auto c = std::pow(circle.x, 2) + std::pow(helper, 2) - std::pow(circle.r, 2);
    auto delta = b * b - 4 * a * c;
    if (delta + eps > 0 && delta - eps < 0)
    {
        Intersection result;
        result.exists = true;
        result.p1.x = -b / 2 / a;
        result.p1.y = slope * result.p1.x - slope * p1.x + p1.y;
        result.p2 = result.p1;
        return result;
    }
    else if (delta + eps > 0)
    {
        Intersection result;
        result.exists = true;
        result.p1.x = (-b - std::sqrt(delta)) / 2 / a;
        result.p1.y = slope * result.p1.x - slope * p1.x + p1.y;
        result.p2.x = (-b + std::sqrt(delta)) / 2 / a;
        result.p2.y = slope * result.p2.x - slope * p1.x + p1.y;
        return result;
    }
    return Intersection();
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<Point> lairs(n);
    int positive = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> lairs[i].x >> lairs[i].y;
        if (lairs[i].y > 0)
        {
            positive++;
        }
    }
    if (positive != 0 && positive != n)
    {
        LOG(-1);
        return 0;
    }
    double min = 0;
    double max = 1e15;
    double radius = (min + max) / 2;
    int sign = positive > 0 ? 1 : -1;
    while ((max - min) / radius > 2e-6)
    {
        double middle = (max + min) / 2;
        double xmin = -1e7;
        double xmax = 1e7;
        bool too_small = false;
        Point p1(-1, sign * middle), p2(1, sign * middle);
        for (auto i = 0; i < n; ++i)
        {
            Circle circle(lairs[i].x, lairs[i].y, middle);
            auto result = circle_line_intersection(p1, p2, circle);
            if (!result.exists || (result.p2.x < xmin || result.p1.x > xmax))
            {
                too_small = true;
                break;
            }
            xmin = std::max(result.p1.x, xmin);
            xmax = std::min(result.p2.x, xmax);
        }
        if (too_small)
        {
            min = middle;
        }
        else
        {
            max = middle;
        }
        radius = (min + max) / 2;
    }
    LOG(std::fixed << std::setprecision(6) << radius);
}

