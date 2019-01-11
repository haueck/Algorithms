/*
 * Codeforces - Elongated Matrix
 * https://codeforces.com/contest/1102/problem/F
 * Author: Rafal Kozik
 */

// This is the same idea as in Graphs/Travelling Salesman Problem

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

int dp[16][16][0xffff];

std::vector<int> calc_absent(int set, int all, int n) {
    std::vector<int> absent;
    for (auto i = 0; i < n; ++i) {
        bool available = (all >> i) & 1;
        bool exists = (set >> i) & 1;
        if (available && !exists) {
            absent.push_back(i);
        }
    }
    return absent;
}

std::vector<int> calc_sets(int s, int n) {
    std::vector<int> sets{ 0 };
    for (auto i = 0; i < n; ++i) {
        if (i != s) {
            auto size = sets.size();
            for (auto j = 0u; j < size; ++j) {
                sets.push_back(sets[j] | (1 << i));
            }
        }
    }
    std::swap(sets.front(), sets.back());
    sets.pop_back();
    std::sort(sets.begin(), sets.end(), [](int a, int b) { return std::bitset<16>(a).count() < std::bitset<16>(b).count(); });
    return sets;
}

void find_max_permutation(int s, int set, int t) {
    for (auto i = 0; (1 << i) <= set; ++i) {
        if ((set >> i) & 1) {
            auto copy = set & ~(1 << i);
            dp[s][t][set] = std::max(dp[s][t][set], std::min(dp[s][i][copy], dp[i][t][0]));
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> d(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> d[i][j];
        }
    }
    if (n == 1) {
        int min = INT32_MAX;
        for (int k = 0; k + 1 < m; ++k) {
            min = std::min(min, std::abs(d[0][k] - d[0][k + 1]));
        }
        LOG(min);
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        dp[i][i][0] = 0;
        for (int j = i + 1; j < n; ++j) {
            int min = INT32_MAX;
            for (int k = 0; k < m; ++k) {
                min = std::min(min, std::abs(d[i][k] - d[j][k]));
            }
            dp[i][j][0] = min;
            dp[j][i][0] = min;
        }
    }
    std::vector<std::vector<int>> wrap(n, std::vector<int>(n, INT32_MAX));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k + 1 < m; ++k) {
                wrap[i][j] = std::min(wrap[i][j], std::abs(d[i][k] - d[j][k + 1]));
            }
        }
    }
    int result = 0;
    for (int s = 0; s < n; ++s) {
        auto sets = calc_sets(s, n);
        for (auto i = 0u; i < sets.size(); ++i) {
            auto absent = calc_absent(sets[i], sets.back(), n);
            for (auto j = 0u; j < absent.size(); ++j) {
                find_max_permutation(s, sets[i], absent[j]);
            }
        }
        for (auto i = 0; i < n; ++i) {
            if (sets.back() & (1 << i)) {
                auto removed = sets.back() & ~(1 << i);
                result = std::max(result, std::min(dp[s][i][removed], wrap[i][s]));
            }
        }
    }
    LOG(result);
}

