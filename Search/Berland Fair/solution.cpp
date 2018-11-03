/*
 * Codeforces - Berland Fair
 * http://codeforces.com/contest/1073/problem/D
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

void fenwick_update(std::vector<int64_t>& bit, int index, int64_t value)
{
    ++index;
    int size = bit.size();
    while (index < size)
    {
       bit[index] += value;
       index += index & (-index);
    }
}

int64_t fenwick_sum(std::vector<int64_t>& bit, int index)
{
    ++index;
    int64_t sum = 0;
    while (index > 0)
    {
        sum += bit[index];
        index -= index & (-index);
    }
    return sum;
}

int upper_bound(std::vector<int64_t>& bit, int left, int right, int64_t value)
{
    while (right > left)
    {
        auto mid = (left + right) / 2;
        auto sum = fenwick_sum(bit, mid);
        if (sum > value)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return left;
}

int main()
{
    int n;
    int64_t money;
    std::cin >> n >> money;
    std::vector<int64_t> prices(n), bit(n + 1);
    auto total_cost = 0ll;
    auto cookies = 0ll;
    auto booths = n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> prices[i];
        fenwick_update(bit, i, prices[i]);
        total_cost += prices[i];
    }
    while (money > 0 && booths > 0)
    {
        int64_t rounds = money / total_cost;
        money -= total_cost * rounds;
        cookies += rounds * booths;
        while (money < total_cost && booths > 0)
        {
            auto first_greater = upper_bound(bit, 0, n - 1, money);
            fenwick_update(bit, first_greater, -prices[first_greater]);
            total_cost -= prices[first_greater];
            booths--;
        }
    }
    LOG(cookies);
}


