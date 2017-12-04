/*
 *
 *
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> A(n);
    // How far can we go from the current position
    // without any car model being duplicated
    std::vector<int> furthest(n);
    // Previous position of the same model
    std::vector<int> previous(n, -1);
    for (int i = 0; i < n; i++)
    {
       std::cin >> A[i];
    }
    std::unordered_map<int,int> seen;
    int left = 0;
    int right = 0;
    while (left < n)
    {
        while (right < n)
        {
            // Go as far as possible without any duplicates
            auto it = seen.find(A[right]);
            if (it == seen.end())
            {
                seen.emplace(A[right], right);
                ++right;
                continue;
            }
            // Found duplicate, store its position
            previous[right] = it->second;
            break;
        }
        // This is where we can go from left without duplicates
        furthest[left] = right - 1;
        seen.erase(A[left]);
        ++left;
    }
    while (q--)
    {
        int l, r;
        std::cin >> l >> r;
        int left = l - 1;
        int right = std::min(furthest[left], r - 1);
        int previous_right = -1;
        int64_t result = 0;
        while (true)
        {
            int64_t size = right - left + 1;
            // Number of subarrays in subarray of size equal to size.
            // For example, for size = 5 it is equal to 5 + 4 + 3 + 2 + 1.
            result += ((1 + size) * size) / 2;
            long overlapping_size = previous_right - left + 1;
            if (overlapping_size > 0)
            {
                result -= ((1 + overlapping_size) * overlapping_size) / 2;
            }
            if (right == r - 1)
            {
                break;
            }
            previous_right = right;
            left = previous[right + 1] + 1;
            right = std::min(furthest[left], r - 1);
        }
        LOG(result);
    }
}

