/*
 * HackerRank - Range Modular Queries
 * https://www.hackerrank.com/contests/w30/challenges/range-modular-queries
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

// This is a treshhold for which we need 200 * n precomputation steps
// and the worst case scenario for each query is O(200 * logn).
// This is enough to finish within time limit.
const int K = 200;

int main()
{
    std::ios::sync_with_stdio(false);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::vector<int> freq[40001];
    std::vector<int> modulos[K][K];

    for (int i = 0; i < n; i++)
	{
       std::cin >> a[i];
    }

    for (int i = 0; i < n; i++)
	{
       freq[a[i]].push_back(i);
    }

    // Precomputing table in O(n*K)
    for (int x = 1; x < K; x++)
    {
        for (int i = 0; i < n; i++)
        {
            modulos[x][a[i] % x].push_back(i);
        }
    }

    for (int i = 0; i < q; i++)
    {
        int left, right, x, y;
        std::cin >> left >> right >> x >> y;
        if (x < K)
        {
            // For small x's we use precomputed table and it is possible
            // to get a result in O(logn)
            auto start = std::lower_bound(modulos[x][y].begin(), modulos[x][y].end(), left);
            auto end = std::lower_bound(modulos[x][y].begin(), modulos[x][y].end(), right);
            if (end == modulos[x][y].end() || *end > right)
            {
                --end;
            }
            LOG(std::distance(start, end) + 1);
        }
        else
        {
            // For large x's we itarate over all possible values giving
            // y as a result of a[i] % x, that is i = k * x + y.
            int count = 0;
            for (int i = y; i < 40001; i += x)
            {
                auto start = std::lower_bound(freq[i].begin(), freq[i].end(), left);
                auto end = std::lower_bound(freq[i].begin(), freq[i].end(), right);
                if (end == freq[i].end() || *end > right)
                {
                    --end;
                }
                count += std::distance(start, end) + 1;
            }
            LOG(count);
        }
    }
    return 0;
}

