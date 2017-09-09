/*
 * HackerRank - Merging Communities
 * https://www.hackerrank.com/challenges/merging-communities
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

class DisjointSet
{
public:

    std::vector<int> data;

    DisjointSet(int N) : data(N, -1) { }

    int size(int a)
    {
        return -1 * data[find(a)];
    }

    int find(int i)
    {
        if (data[i] < 0)
        {
            return i;
        }
        data[i] = find(data[i]);
        return data[i];
    }

    void merge(int a, int b)
    {
        auto root_a = find(a);
        auto root_b = find(b);
        if (root_a == root_b)
        {
            return;
        }
        else if (data[root_a] < data[root_b])
        {
            data[root_a] += data[root_b];
            data[root_b] = root_a;
        }
        else
        {
            data[root_b] += data[root_a];
            data[root_a] = root_b;
        }
    }
};

int main()
{
    int N, Q;
    std::cin >> N >> Q;
    DisjointSet communities(N);
    while (Q--)
    {
        char query;
        std::cin >> query;
        if (query == 'M')
        {
            int a, b;
            std::cin >> a >> b;
            communities.merge(a, b);
        }
        else if (query == 'Q')
        {
            int a;
            std::cin >> a;
            LOG(communities.size(a));
        }
    }
}

