/*
 *
 *
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl
#ifdef DEBUG
    #define DBG(x) std::cerr << x << std::endl
#else
    #define DBG(x)
#endif

int main()
{
    std::ios::sync_with_stdio(false);
}

