/*
 * Codeforces - Almost Difference
 * http://codeforces.com/contest/903/problem/D
 * Author: Rafal Kozik
 */

#include <vector>
#include <iomanip>
#include <iostream>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<int64_t> data(n);
    std::vector<std::pair<int64_t,int64_t>> lower_and_greater(n);
    std::vector<int64_t> suffix_sums(n);
    std::unordered_map<int,int> number_of_occurences;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data[i];
    }
    int64_t total = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        auto c = data[i];
        number_of_occurences[c]++;
        lower_and_greater[i].first = number_of_occurences[c - 1],
        lower_and_greater[i].second = number_of_occurences[c + 1],
        total += c;
        suffix_sums[i] = total;
    }
    long double result = 0;
    for (int i = 0; i < n; ++i)
    {
        auto lower = lower_and_greater[i].first;
        auto greater = lower_and_greater[i].second;
        result += (suffix_sums[i] -  lower * (data[i] - 1) - (n - i - lower - greater) * data[i] - greater * (data[i] + 1));
    }
    LOG(std::fixed << std::setprecision(0) << result);
}
