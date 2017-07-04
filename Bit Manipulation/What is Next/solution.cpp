/*
 * HackerRank - What's next
 * https://www.hackerrank.com/challenges/whats-next
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int n;
        std::cin >> n;
        std::vector<int64_t> A(n);
        std::vector<int64_t> B;
        for (int i = 0; i < n; ++i)
        {
            std::cin >> A[i];
        }
        // We are mainly interested in least significant ones and zeros in front of them
        bool even = n % 2 == 0;
        auto ones_index = even ? n - 2 : n - 1;
        auto zeros_index = n > 2 ? (even ? n - 3 : n - 2) : -1;
        auto ones = A[ones_index];
        auto zeros = zeros_index != -1 ? A[zeros_index] : 0;
        auto first_mutable_group = zeros > 0 ? zeros_index - 1 : ones_index - 1;
        for (int i = 0; i < first_mutable_group; ++i)
        {
            B.push_back(A[i]);
        }
        if (zeros == 1)
        {
            // 11101 -> 11110
            //          ^^^^
            B.push_back(A[first_mutable_group] + 1);
        }
        else if (zeros > 1)
        {
            // 110001 -> 110010
            //           ^^^^^
            B.push_back(A[first_mutable_group]);
            B.push_back(zeros - 1);
            B.push_back(1);
        }
        else
        {
            // 11 -> 101
            //       ^
            B.push_back(1);
        }
        if (ones == 1)
        {
            if (even)
            {
                // 110010 -> 110100
                //               ^^
                B.push_back(A[A.size() - 1] + 1);
            }
            else
            {
                // 1101 -> 1110
                //            ^
                B.push_back(1);
            }
        }
        else
        {
            if (even)
            {
                // 111000 -> 1000011
                //            ^^^^^^
                B.push_back(A[A.size() - 1]  + 1);
                B.push_back(A[ones_index] - 1);
            }
            else
            {
                // 1111 -> 10111
                //          ^^^^
                B.push_back(1);
                B.push_back(A[ones_index] - 1);
            }
        }
        std::cout << B.size() << std::endl;
        for (auto count : B)
        {
            std::cout << count << " ";
        }
        std::cout << std::endl;
    }
}

