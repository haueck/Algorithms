/*
 * HackerRank - Kindergarden Adventures
 * https://www.hackerrank.com/challenges/kindergarten-adventures/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <limits>

#define LOG(x) std::cout << x << std::endl

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int main() 
{
    int n;
    std::cin >> n;
    std::vector<int> times(n);
    std::vector<std::pair<int,int>> ranges(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> times[i];
    }
	// Each range defines where we can start to see a drawing.
    // If a child at 6th position needs 3 minutes to finish,
    // we can start anywhere in the range <7,6-3>, wrapping at the end.
    for (int i = 0; i < n; ++i)
    {
        if (times[i] < n && times[i] > 0)
        {
            auto from = mod(i + 1, n);
            auto to = mod(i - times[i] + 1, n);
            ranges[from].first++;
            ranges[to].second++;
        }
    }
    int included = 0;
    int max = std::numeric_limits<int>::min();
    int position = 0;
    for (int i = 0; i < n; ++i)
    {
		// Count ranges that start and ones that close
        included += ranges[i].first - ranges[i].second;
        if (included > max)
        {
            max = included;
            position = i;
        }
    }
    LOG(position + 1);
}

