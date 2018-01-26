/*
 *
 *
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>

void advance(std::vector<int>& row, uint64_t count)
{
    uint64_t size = row.size();
    std::vector<int> next(size);
    for (uint64_t i = 0; i < size; ++i)
    {
        next[i] = row[i] ^ row[(i + count) % size];
    }
    row.swap(next);
}

int main()
{
    uint64_t N, M;
    std::cin >> N >> M;
    std::vector<int> row(N);
    for (auto i = 0u; i < N; ++i)
    {
        std::cin >> row[i];
    }
    uint64_t current_row = 1;
    while (current_row < M)
    {
        uint64_t lower_power_of_two = 1;
        while (current_row + 2 * lower_power_of_two <= M)
        {
            lower_power_of_two *= 2;
        }
        advance(row, lower_power_of_two);
        current_row += lower_power_of_two;
    }
    for (auto i = 0u; i < N; ++i)
    {
        std::cout << row[i] << " ";
    }
    std::cout << std::endl;
}
