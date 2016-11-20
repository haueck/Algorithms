/*
 * HackerRank - Grid Challenge
 * Greedy
 * https://www.hackerrank.com/challenges/grid-challenge
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

void swap(std::string& data, int p)
{
    auto c = data[p];
    data[p] = data[p + 1];
    data[p + 1] = c;
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::cin >> N;
        std::vector<std::string> data(N, std::string());
        data.reserve(N);
        std::cin.ignore(1, '\n');
        for (int i = 0; i < N; ++i)
        {
            std::getline(std::cin, data[i]);
        }

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N - 1; ++j)
            {
                int idx = j;
                while (j >= 0 && data[i][idx + 1] < data[i][idx])
                {
                    swap(data[i], idx);
                    --idx;
                }
            }
        }
        bool sorted = true;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N - 1; ++j)
            {
                if (data[j][i] > data[j + 1][i])
                {
                    sorted = false;
                    i = N;
                    break;
                }
            }
        }
        LOG((sorted ? "YES" : "NO"));
    }
    return 0;
}


