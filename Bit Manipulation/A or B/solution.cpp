/*
 * HackerRank - A or B
 * https://www.hackerrank.com/challenges/aorb
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

int hex_to_int(char c)
{
    if (c >= 'A')
    {
        return 10 + (c - 'A');
    }
    else
    {
        return c - '0';
    }
}

char int_to_hex(int a)
{
    if (a > 9)
    {
        return 'A' + (a - 10);
    }
    else
    {
        return '0' + a;
    }
}

int main()
{
    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int K;
        std::string A, B, C;
        std::cin >> K >> A >> B >> C;
        std::reverse(A.begin(), A.end());
        std::reverse(B.begin(), B.end());
        std::reverse(C.begin(), C.end());
        auto max_size = std::max(std::max(A.size(), B.size()), C.size());
        A.resize(max_size, '0');
        B.resize(max_size, '0');
        C.resize(max_size, '0');
        for (auto i = 0u; i < max_size; ++i)
        {
            int a = hex_to_int(A[i]);
            int b = hex_to_int(B[i]);
            int c = hex_to_int(C[i]);
            for (int j = 0; j < 4; ++j)
            {
                int v = 1 << j;
                if (c & v)
                {
                    if (!(a & v || b & v))
                    {
                        b = b | v;
                        --K;
                    }
                }
                else
                {
                    if (a & v)
                    {
                        a = a ^ v;
                        --K;
                    }
                    if (b & v)
                    {
                        b = b ^ v;
                        --K;
                    }
                }
            }
            A[i] = int_to_hex(a);
            B[i] = int_to_hex(b);
        }
        if (K < 0)
        {
            LOG(-1);
        }
        else
        {
            for (int i = max_size - 1; i >= 0 && K > 0; --i)
            {
                int a = hex_to_int(A[i]);
                int b = hex_to_int(B[i]);
                for (int j = 3; j >= 0; --j)
                {
                    int v = 1 << j;
                    if (a & v && b & v && K > 0)
                    {
                        a = a ^ v;
                        --K;
                    }
                    else if (a & v && K > 1)
                    {
                        b = b | v;
                        a = a ^ v;
                        K = K - 2;
                    }
                }
                A[i] = int_to_hex(a);
                B[i] = int_to_hex(b);
            }
            while (A.size() > 1 && A[A.size() - 1] == '0')
            {
                A.pop_back();
            }
            while (B.size() > 1 && B[B.size() - 1] == '0')
            {
                B.pop_back();
            }
            std::reverse(A.begin(), A.end());
            std::reverse(B.begin(), B.end());
			LOG(A);
			LOG(B);
        }
    }
}

