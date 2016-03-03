/*
 * HackerRank - Dynamic Array
 * Arrays
 * https://www.hackerrank.com/challenges/dynamic-array
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <tuple>

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char **argv)
{
    int lastans = 0;
    int N = 0;
    int Q = 0;
    (void)scanf("%d %d", &N, &Q);
    std::vector<std::tuple<int,int,int>> queries;
    std::vector<std::vector<int>> sequences(N, std::vector<int>());
    queries.reserve(Q);

    for (int i = 0; i < Q; ++i)
    {
        int o, x, y;
        (void)scanf("%d %d %d", &o, &x, &y);
        queries.emplace_back(o, x, y);
    }

    for (int i = 0; i < Q; ++i)
    {
        int pos = (std::get<1>(queries[i]) ^ lastans) % N;
        if (std::get<0>(queries[i]) == 1)
        {
            sequences[pos].push_back(std::get<2>(queries[i]));
        }
        else
        {
            int element = sequences[pos][std::get<2>(queries[i]) % sequences[pos].size()];
            LOG(element);
            lastans = element;
        }
    }

    return 0;
}

