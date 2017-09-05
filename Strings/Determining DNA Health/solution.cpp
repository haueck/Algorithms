/*
 * HackerRank - Determining DNA Health
 * https://www.hackerrank.com/challenges/determining-dna-health
 * Author: Rafal Kozik
 */

// TODO: This approach is too slow, 9 out of 33 test cases time out.

#include <set>
#include <cmath>
#include <limits>
#include <vector>
#include <cstring>
#include <iostream>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl

const int mod = 1000000007;
std::vector<uint64_t> powers;

uint64_t add_to_hash(const std::string& text, int position, uint64_t hash)
{
    return ((101 * hash + text[position]) % mod);
}

uint64_t remove_from_hash(const std::string& text, int position, long double length, uint64_t hash)
{
    auto exponent = length - 1;
    if (exponent >= powers.size())
    {
        powers.resize(exponent + 1, 0);
    }
    if (powers[exponent] == 0)
    {
        powers[exponent] = 1;
        for (int i = 0; i < exponent; ++i)
        {
            powers[exponent] = (powers[exponent] * 101) % mod;
        }
    }
    int64_t temp = hash - (text[position] * powers[exponent]) % mod;
    return temp > 0 ? temp : temp + mod;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int n, s;
    std::cin >> n;
    std::vector<std::string> genes(n);
    std::vector<uint64_t> healths(n);
    std::unordered_map<uint64_t,std::vector<int>> hashes(n);
    std::set<uint32_t> sizes;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> genes[i];
        sizes.emplace(genes[i].size());
    }
    for (int i = 0; i < n; ++i)
    {
        std::cin >> healths[i];
    }
    for (int i = 0; i < n; ++i)
    {
        uint64_t hash = 0;
        for (auto j = 0u; j < genes[i].size(); ++j)
        {
            hash = add_to_hash(genes[i], j, hash);
        }
        hashes[hash].push_back(i);
    }
    std::cin >> s;
    uint64_t max = 0;
    uint64_t min = std::numeric_limits<uint64_t>::max();
    while (s--)
    {
        int start, end;
        uint64_t health = 0;
        std::string strand;
        std::cin >> start >> end >> strand;
        std::vector<std::pair<uint64_t,int>> rolling_hashes;
        for (auto size : sizes)
        {
            if (size > strand.size())
            {
                break;
            }
            uint64_t hash = 0;
            for (auto j = 0u; j < size; ++j)
            {
                hash = add_to_hash(strand, j, hash);
            }
            rolling_hashes.emplace_back(hash, size);
        }
        int rolling_hashes_size = rolling_hashes.size();
        for (auto i = 0u; i < strand.size(); ++i)
        {
            for (int j = 0; j < rolling_hashes_size; ++j)
            {
                auto it = hashes.find(rolling_hashes[j].first);
                if (it != hashes.end())
                {
                    for (auto position : it->second)
                    {
                        if (position >= start && position <= end)
                        {
                            if (0 == strncmp(&strand[i], &genes[position][0], rolling_hashes[j].second))
                            {
                                health += healths[position];
                            }
                        }
                    }
                }
            }
            for (int j = 0; j < rolling_hashes_size; ++j)
            {
                if (i + rolling_hashes[j].second < strand.size())
                {
                    rolling_hashes[j].first = remove_from_hash(strand, i, rolling_hashes[j].second, rolling_hashes[j].first);
                    rolling_hashes[j].first = add_to_hash(strand, i + rolling_hashes[j].second, rolling_hashes[j].first);
                }
                else
                {
                    rolling_hashes_size = j;
                    break;
                }
            }
        }
        max = std::max(max, health);
        min = std::min(min, health);
    }
    LOG(min << " " << max);
}
