/*
 * HackerRank - Basketball Game
 * https://www.hackerrank.com/contests/101hack47/challenges/basketball-game
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <cmath>

#define eps (1e-9)
#define LOG(x) std::cout << x << std::endl

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for(int t = T; t > 0; --t)
    {
        bool blocked = false;
        int xHoop, yHoop, xC, yC, sC;
        std::cin >> xHoop >> yHoop;
        std::cin >> xC >> yC >> sC;
        double length = std::sqrt((xHoop - xC) * (xHoop - xC) + (yHoop - yC) * (yHoop - yC));
        double xN = (xHoop - xC) / length;
        double yN = (yHoop - yC) / length;
        double tMax = length / sC;
        for (int i = 0; i < 5; i++)
        {
            int x, y, s;
            std::cin >> x >> y >> s;
            double xV = xC - x;
            double yV = yC - y;
            double a = sC * sC * (xN * xN + yN * yN) - s * s;
            double b = 2 * sC * (xN * xV + yN * yV);
            double c = xV * xV + yV * yV;
            double delta = b * b - 4 * a * c;
            if (std::abs(a) < eps)
            {
                auto x0 = -c / b;
                if ((b > 0 && x0 > 0) || (b < 0 && x0 < tMax))
                {
                    blocked = true;
                }
            }
            else if (a > 0)
            {
                if (delta > eps)
                {
                    auto x1 = (-b - std::sqrt(delta))/2.0/a;
                    auto x2 = (-b + std::sqrt(delta))/2.0/a;
                    if ((x1 > 0 && x1 < tMax) || (x2 > 0 && x2 < tMax))
                    {
                        blocked = true;
                    }
                }
            }
            else
            {
                if (delta > eps)
                {
                    auto x1 = (-b - std::sqrt(delta))/2.0/a;
                    auto x2 = (-b + std::sqrt(delta))/2.0/a;
                    if (!((x1 < 0 && x2 > tMax) || (x2 < 0 && x1 > tMax)))
                    {
                        blocked = true;
                    }
                }                 
                else if (delta < eps)
                {
                    blocked = true;
                }
            }
        }
        LOG((blocked ? "NO" : "YES"));
    }
}

