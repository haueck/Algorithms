/*
 * HackerRank - Sherlock and Array
 * Search
 * https://www.hackerrank.com/challenges/sherlock-and-array
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

void search(const std::vector<uint64_t>& sums)
{
    int left = 0;
    int right = sums.size() - 1;
    uint64_t total = sums[right];
    while (left < right)
    {
        int middle = (left + right) / 2;
        if (sums[middle] < total - sums[middle + 1])
        {
            left = middle + 1;
        }
        else
        {
            right = middle;
        }
    }
    if (sums.size() == 1 || (left + 1 < sums.size() && sums[left] == total - sums[left + 1]))
    {
        LOG("YES");
    }
    else
    {
        LOG("NO");
    }
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::cin >> N;
        std::vector<int> data(N, 0);
        std::vector<uint64_t> sums(N, 0);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> data[i];
        }
        sums[0] = data[0];
        for (int i = 1; i < N; ++i)
        {
            sums[i] = sums[i - 1] + data[i];
        }
        search(sums);
    }
    return 0;
}

