/*
 * Codeforces - GCD Counting
 * https://codeforces.com/contest/1101/problem/D
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>

#define LOG(x) std::cout << x << std::endl

struct Node {
    int value;
    std::vector<int> edges;
};

void find_furthest(std::vector<Node>& graph, std::vector<bool>& visited, int c, int p, int d, int& furthest, int& distance) {
    if (visited[c]) {
        return;
    }
    if (graph[c].value % p != 0) {
        return;
    }
    if (d > distance) {
        distance = d;
        furthest = c;
    }
    visited[c] = true;
    for (auto edge : graph[c].edges) {
        find_furthest(graph, visited, edge, p, d + 1, furthest, distance);
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Node> graph(n);
    std::map<int,int> candidates;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        graph[i].value = v;
        int sqrt = std::sqrt(v);
        if (v % 2 == 0) {
            candidates[2]++;
            while (v % 2 == 0) {
                v = v / 2;
            }
        }
        for (int i = 3; i <= sqrt; i = i + 2) {
            if (v % i == 0) {
                candidates[i]++;
                while (v % i == 0) {
                    v = v / i;
                }
            }
        }
        if (v > 1) {
            candidates[v]++;
        }
    }
    for (int i = 0; i + 1 < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].edges.push_back(b - 1);
        graph[b - 1].edges.push_back(a - 1);
    }
    int result = 0;
    std::vector<std::pair<int, int>> primes;
    for (auto [prime, count] : candidates) {
        primes.emplace_back(count, prime);
    }
    std::sort(primes.begin(), primes.end(), std::greater<>());
    for (auto [count, prime] : primes) {
        if (count <= result) {
            break;
        }
        std::vector<bool> visited(n);
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && graph[i].value % prime == 0) {
                int furthest = i;
                int distance = 1;
                std::vector<bool> temp(n);
                find_furthest(graph, temp, i, prime, 1, furthest, distance);
                find_furthest(graph, visited, furthest, prime, 1, furthest, result);
            }
        }
    }
    LOG(result);
}
