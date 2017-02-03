/*
 * TSP - Travelling Salesman Problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl;

class Set
{
public:

    std::vector<bool> nodes;
    int count{0};

    Set(int n) : nodes(n, false) { }

    void add(int e)
    {
        nodes[e] = true;
        ++count;
    }

    std::size_t hash() const
    {
        return std::hash<std::vector<bool>>()(nodes);
    }

    void flip(int e)
    {
        nodes[e] = !nodes[e];
    }

	std::vector<int> elements(bool cond, int size) const
	{
        std::vector<int> result;
        result.reserve(size);
        for (auto i = 1u; i < nodes.size(); ++i)
        {
            if (nodes[i] == cond)
            {
                result.push_back(i);
            }
        }
        return result;
    }

    std::vector<int> not_in_set() const
    {
        return elements(false, nodes.size() - count);
    }

    std::vector<int> in_set() const
    {
        return elements(true, count);
    }
};

std::vector<Set> generate_sets(int N)
{
    std::vector<Set> sets;
    sets.emplace_back(N);
    for (int i = 1; i < N; ++i)
    {
        std::vector<Set> temp;
        for (auto set : sets)
        {
            set.add(i);
            temp.emplace_back(std::move(set));
        }
        sets.insert(sets.begin(), temp.begin(), temp.end());
    }
    return sets;
}

int get_min_cost_via_set(int target_node, Set& set, std::vector<std::unordered_map<std::size_t,int>>& cost, const std::vector<std::vector<int>>& dist)
{
    auto min = std::numeric_limits<int>::max();
    for (auto penultimate_node : set.in_set())
    {
        set.flip(penultimate_node);
        auto new_cost = cost[penultimate_node][set.hash()] + dist[penultimate_node][target_node];
        if (new_cost < min)
        {
            min = new_cost;
        }
        set.flip(penultimate_node);
    }
    return min;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int N;
        std::cin >> N;
        std::vector<std::vector<int>> dist(N, std::vector<int>(N));
        std::vector<std::unordered_map<std::size_t,int>> cost(N);
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                std::cin >> dist[i][j];
            }
        }
        auto sets = generate_sets(N);
        auto empty_set = sets.back();
        sets.pop_back();
        std::sort(sets.begin(), sets.end(), [](const Set& lhs, const Set& rhs) { return lhs.count < rhs.count; });
        auto full_set = sets.back();
        sets.pop_back();
        for (auto node : empty_set.not_in_set())
        {
            cost[node][empty_set.hash()] = dist[0][node];
        }
        for (auto& set : sets)
        {
            for (auto target_node : set.not_in_set())
            {
                cost[target_node][set.hash()] = get_min_cost_via_set(target_node, set, cost, dist);
            }
        }
        LOG(get_min_cost_via_set(0, full_set, cost, dist));
    }
    return 0;
}
