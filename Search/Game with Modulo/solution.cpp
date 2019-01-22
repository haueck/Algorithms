/*
 * Codeforces - Game with modulo
 * http://codeforces.com/contest/1104/problem/D
 * Author: Rafal Kozik
 */

// This is an interactive problem

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "end") {
            return 0;
        }
        int64_t x = 0;
        int64_t y = 1;
        while (true) {
            LOG("? " << x << " " << y);
            std::getline(std::cin, line);
            if (line == "x") {
                break;
            }
            x = y;
            y *= 2;
        }
        while (y > x + 1) {
            int mid = (x + y + 1) / 2;
            LOG("? " << x << " " << mid);
            std::getline(std::cin, line);
            if (line == "y") {
                x = mid;
            }
            else {
                y = mid;
            }
        }
        LOG("! " << y);
    }
}

