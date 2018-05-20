/*
 * Codeforces - Nested Segments
 * http://codeforces.com/contest/976/problem/C
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

struct Segment
{
    Segment(int64_t left, int64_t right, int index) : left(left), right(right), index(index) { }
    int64_t left;
    int64_t right;
    int index;
    bool operator<(const Segment& other) const
    {
        if (left == other.left)
        {
            return right > other.right;
        }
        return left < other.left;
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::vector<Segment> data;
    for (auto i = 0; i < n; ++i)
    {
        int64_t l, r;
        std::cin >> l >> r;
        data.emplace_back(l, r, i + 1);
    }
    std::sort(data.begin(), data.end());
    int64_t max_right = 0;
    int max_index = 0;
    for (auto& segment : data)
    {
        if (segment.right <= max_right)
        {
            LOG(segment.index << " " << max_index);
            return 0;
        }
        if (segment.right > max_right)
        {
            max_right = segment.right;
            max_index = segment.index;
        }
    }
    LOG(-1 << " " << -1);
}

