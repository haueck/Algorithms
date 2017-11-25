/*
 * Codeforces - Credit Card
 * http://codeforces.com/contest/893/problem/D
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n, d;
    std::cin >> n >> d;
    std::vector<int> trans(n);
    std::vector<int64_t> hist(n);
    std::vector<int64_t> max(n);
    int64_t balance = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> trans[i];
        balance += trans[i];
        if (balance > d)
        {
            LOG(-1);
            return 0;
        }
        hist[i] = balance;
    }
    max[n - 1] = d - hist[n - 1];
    for (int i = n - 2; i >= 0; --i)
    {
        max[i] = std::min(d - hist[i], max[i + 1]);
    }
    int64_t deposited = 0;
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (trans[i] == 0 && hist[i] + deposited < 0)
        {
            ++count;
            deposited = max[i];
            if (hist[i] + deposited < 0)
            {
                LOG(-1);
                return 0;
            }
        }
    }
    LOG(count);
}
