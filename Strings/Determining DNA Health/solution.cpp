/*
 * HackerRank - Determining DNA Health
 * https://www.hackerrank.com/challenges/determining-dna-health
 * Author: Rafal Kozik
 */

#include <set>
#include <limits>
#include <vector>
#include <cstring>
#include <iostream>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl

const std::size_t LSI = 10;
std::vector<uint64_t> powers{1};

struct Gene
{
    std::vector<int> positions;
    std::vector<uint64_t> accumulated_health;

    Gene(int position, uint64_t health) : positions(1, position), accumulated_health(1, health) { }

    void add(int position, uint64_t health)
    {
        positions.push_back(position);
        accumulated_health.push_back(accumulated_health.back() + health);
    }
};

struct Strand
{
    const uint64_t MOD = 1000000007;
    const std::string& strand;
    std::size_t hash{0};
    int from;
    int to;
    int size;

    Strand(const std::string& strand) : Strand(strand, 0, strand.size() - 1, strand.size()) { }

    Strand(const std::string& strand, int from, int to, int size) : strand(strand), from(from), to(to), size(size)
    {
        for (auto i = from; i <= to; ++i)
        {
            add_to_hash(i);
        }
    }

    void add_to_hash(int position)
    {
        hash = (101 * hash + strand[position]) % MOD;
    }

    void remove_from_hash(int position, int length)
    {
        int exponent = length - 1;
        int current = powers.size();
        while (length > current)
        {
            powers.push_back((powers[current++ - 1] * 101) % MOD);
        }
        int64_t temp = hash - (strand[position] * powers[exponent]) % MOD;
        hash = temp > 0 ? temp : temp + MOD;
    }

    void move_hash(int start)
    {
        if (to < start + size / 2)
        {
            from = start;
            to = start;
            hash = 0;
            add_to_hash(start);
        }
        for (auto k = to + 1; k < start + size; ++k)
        {
            add_to_hash(k);
        }
        to = start + size - 1;
        for (auto k = from; k < start; ++k)
        {
            remove_from_hash(k, to - from + 1);
            from++;
        }
    }
};

namespace std
{
    template <>
    struct hash<Strand>
    {
        std::size_t operator()(const Strand& strand) const
        {
            return strand.hash;
        }
    };
}

bool operator==(const Strand &l, const Strand &r)
{
    return l.size == r.size && 0 == strncmp(&l.strand[l.from], &r.strand[r.from], l.size);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, s;
    std::cin >> n;
    std::vector<std::size_t> empty;
    std::vector<uint64_t> healths(n);
    std::vector<std::string> genes(n);
    std::unordered_map<Strand,Gene> map;
    std::unordered_map<Strand,std::vector<std::size_t>> index;
    std::set<std::size_t> sizes;
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
        if (genes[i].size() > LSI)
        {
            Strand strand(genes[i], 0, LSI - 1, LSI);
            auto position = std::distance(sizes.begin(), sizes.find(genes[i].size()));
            auto it = index.find(strand);
            if (it == index.end())
            {
                index.emplace(strand, std::vector<std::size_t>(1, position));
            }
            else
            {
                it->second.push_back(position);
            }
        }
        Strand strand(genes[i]);
        auto it = map.find(strand);
        if (it == map.end())
        {
            map.emplace(strand, Gene(i, healths[i]));
        }
        else
        {
            it->second.add(i, healths[i]);
        }
    }
    std::cin >> s;
    uint64_t max = 0;
    uint64_t min = std::numeric_limits<uint64_t>::max();
    while (s--)
    {
        int start, end;
        std::size_t lsb = 0;
        uint64_t health = 0;
        std::string strand;
        std::cin >> start >> end >> strand;
        std::vector<Strand> strands;
        for (auto size : sizes)
        {
            if (size > strand.size())
            {
                break;
            }
            if (size <= LSI)
            {
                lsb++;
            }
            strands.emplace_back(strand, 0, 0, size);
        }
        Strand key(strand, 0, 0, LSI);
        for (auto i = 0u; i < strand.size(); ++i)
        {
            auto& long_genes = empty;
            if (i + LSI <= strand.size())
            {
                key.move_hash(i);
                auto it = index.find(key);
                if (it != index.end())
                {
                    long_genes = it->second;
                }
            }
            for (auto j = 0u; j < lsb; ++j)
            {
                if (i + strands[j].size <= strand.size())
                {
                    strands[j].move_hash(i);
                    auto it = map.find(strands[j]);
                    if (it != map.end())
                    {
                        for (auto position : it->second.positions)
                        {
                            if (position >= start && position <= end)
                            {
                                health += healths[position];
                            }
                        }
                    }
                }
            }
            for (auto j : long_genes)
            {
                if (j < strands.size())
                {
                    strands[j].move_hash(i);
                    auto it = map.find(strands[j]);
                    if (it != map.end())
                    {
                        for (auto position : it->second.positions)
                        {
                            if (position >= start && position <= end)
                            {
                                health += healths[position];
                            }
                        }
                    }
                }
            }
        }
        max = std::max(max, health);
        min = std::min(min, health);
    }
    LOG(min << " " << max);
}

