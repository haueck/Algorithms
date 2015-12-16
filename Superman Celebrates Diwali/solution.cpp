/*
 * HackerRank - Superman Celebrates Diwali
 * Dynamic Programming
 * https://www.hackerrank.com/challenges/superman-celebrates-diwali
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    int N, H, I;
    scanf("%d %d %d", &N, &H, &I);
    std::vector<std::vector<int>> victims(N + 1, std::vector<int>(H + I, 0));
    for (int i = 0; i < N; ++i)
    {
        int people;
        int floor;
        scanf("%d", &people);
        for (int j = 0; j < people; ++j)
        {
            scanf("%d", &floor);
            victims[i][floor - 1] += 1;
        }
    }
    for (int floor = H - 1; floor >= 0; --floor)
    {
        int max = 0;
        for (int building = 0; building < N; ++building)
        {
            victims[building][floor] += victims[building][floor + 1] > victims[N][floor + I] ? victims[building][floor + 1] : victims[N][floor + I];
            if (victims[building][floor] > max)
            {
                max = victims[building][floor];
            }
        }
        victims[N][floor] = max;
    }
    int result = 0;
    for (int building = 0; building < N; ++building)
    {
        result = victims[building][0] > result ? victims[building][0] : result;
    }
    std::cout << result << std::endl;
    return 0;
}

