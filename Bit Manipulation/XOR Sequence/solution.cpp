/*
 * HackerRank - XOR Sequence
 * https://www.hackerrank.com/challenges/xor-se
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

/*
 * A6: 1^2^3^4^5^6
 * A7: 1^2^3^4^5^6^7
 * A8: 1^2^3^4^5^6^7^8
 * A9: 1^2^3^4^5^6^7^8^9
*/

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        uint64_t L, R;
        uint64_t result = 0;
        std::cin >> L >> R;
        // When we calculate A6^A7^A8^A9
        // parts 123456 will cancel out each other.
        // They will not cancel if there is an odd
        // number of elements.
        if ((R - L + 1) % 2 != 0)
        {
            // Calculate AL
            auto last = L;
            // Notice that 1^(2^3)^(4^5) = 1^1^1
            // Check if L is even and add the last number
            // to the result and remove it.
            // We get 1^(2^3)^4 => 1^(2^3)
            if (last % 2 == 0)
            {
                result ^= last;
                --last;
            }
            // Remove leading 1: 1^(2^3)^(4^5) => (2^3)^(4^5)
            --last;
            // If there is even number of pairs they will
            // cancel out and only leading 1 is left.
            // Otherwise, pairs will cancel out with leading 1.
            if ((last >> 1) % 2 == 0)
            {
                result ^= 1;
            }
        }
        // Notice that in A6^A7^A8^A9 for numbers 7-9 some
        // pairs will cancel out. We need to calculate only 7^9.
        // In other cases we may calculate even numbers, like 4^6^8,
        // but they will be always of the form A[n]^A[n+2]^A[n+4}^...
        // We use tha fact that (0^2)^(4^6) = 2^2 (only second bit
        // is different in pairs (n,n+2)).
        // p is the number of of such numbers (p=2 for 7^9)
        int p = (1 + R - L) / 2;
        // First number of the sequence (first=7 for 7^9)
        uint64_t first = (L + R) % 2 ? L + 1 : L + 2;
        // If the second bit of the first number is 1,
        // we need to include it separately as there is no matching
        // number in the sequence.
        if (first & 2)
        {
            result ^= first;
            --p;
        }
        // If the number of elemets in the sequence is odd,
        // we neeed to include the last number.
        if (p % 2 != 0)
        {
            result ^= R;
        }
        // If the number of pais is even they will cancel out,
        // otherwise we are left with 2.
        if ((p >> 1) % 2 != 0)
        {
            result ^= 2;
        }
        LOG(result);
    }
    return 0;
}

