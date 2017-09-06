/*
 * HackerRank - Demanding Money
 * https://www.hackerrank.com/challenges/borrowing-money
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

struct Node
{
    std::vector<int> neighbours;
    int savings{0};
};

int max_profit(std::vector<Node>& nodes, int current, bool conned, uint64_t& count, std::vector<int>& state)
{
    int profit = 0;
    state[current] = 2;
    if (conned)
    {
        // Take his money and mark all neighbours as away from home
        profit += nodes[current].savings;
        for (auto nb : nodes[current].neighbours)
        {
            if (state[nb] == 0)
            {
                state[nb] = 1;
            }
        }
    }
    for (auto nb : nodes[current].neighbours)
    {
        if (state[nb] == 2)
        {
            continue;
        }
        else if (state[nb] == 1)
        {
            // This one cannot be conned
            profit += max_profit(nodes, nb, false, count, state);
        }
        else
        {
            // Check what is better for the profit, to con this one or not
            uint64_t count1 = 1;
            uint64_t count2 = 1;
            auto state_copy = state;
            auto profit1 = max_profit(nodes, nb, false, count1, state_copy);
            auto profit2 = max_profit(nodes, nb, true, count2, state);
            if (profit1 == profit2)
            {
                profit += profit1;
                count *= (count1 + count2);
            }
            else if (profit1 > profit2)
            {
                profit += profit1;
                count *= count1;
            }
            else
            {
                profit += profit2;
                count *= count2;
            }
        }
    }
    return profit;
}

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<Node> nodes(N + 1);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> nodes[i].savings;
    }
    for (int i = 0; i < M; ++i)
    {
        int A, B;
        std::cin >> A >> B;
        nodes[A - 1].neighbours.push_back(B - 1);
        nodes[B - 1].neighbours.push_back(A - 1);
    }
    uint64_t count = 1;
    /*
     * 0 - not visited, can be conned
     * 1 - not visited, cannot be conned
     * 2 - visited
     */
    std::vector<int> state(N + 1);
    // Create a dummy node that is connected to all other nodes
    for (int i = 0; i < N; ++i)
    {
        nodes[N].neighbours.push_back(i);
    }
    auto profit = max_profit(nodes, N, false, count, state);
    LOG(profit << " " << count);
}

