/*
 * HackerRank - Subset Component
 * https://www.hackerrank.com/challenges/subset-component
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

int count_nodes(uint64_t v)
{
    int count = 0;
    while (v > 0)
    {
        if (v & 1)
        {
            ++count;
        }
        v >>= 1;
    }
    return count;
}

std::vector<std::vector<uint64_t>> calculate_sets(std::vector<uint64_t> data)
{
    std::vector<std::vector<uint64_t>> sets(1, std::vector<uint64_t>());
    for (auto element : data)
    {
        std::vector<std::vector<uint64_t>> append;
        for (auto subset : sets)
        {
            subset.push_back(element);
            append.emplace_back(subset);
        }
        sets.insert(sets.begin(), append.begin(), append.end());
    }
    return sets;
}

std::vector<uint64_t> calculate_components(std::vector<uint64_t>& set)
{
    std::vector<uint64_t> components;
    for (auto i = 0u; i < set.size(); ++i)
    {
        if (set[i] == 0)
        {
            continue;
        }
        bool connected = false;
        for (auto j = 0u; j < components.size(); ++j)
        {
            if (set[i] & components[j])
            {
                components[j] |= set[i];
                connected = true;
                break;
            }
        }
        if (!connected)
        {
            components.push_back(set[i]);
        }
    }
    if (components.size() == set.size())
    {
        return components;
    }
    else
    {
        return calculate_components(components);
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<uint64_t> data(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data[i];
    }
    auto sets = calculate_sets(data);
    int total = 0;
    for (auto set : sets)
    {
        auto components = calculate_components(set);
        total += 64 + components.size();
        for (auto component : components)
        {
            total -= count_nodes(component);
        }
    }
    std::cout << total << std::endl;
}

