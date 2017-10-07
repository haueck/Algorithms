/*
 * HackerRank - Keywords
 * https://www.hackerrank.com/contests/optimization-oct17/challenges/keywords
 * Author: Rafal Kozik
 */

#include <vector>
#include <limits>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

int minimumLength(std::string text, std::vector<std::string> keys)
{
    std::stringstream ss;
    ss.str(text);
    std::vector<std::string> words;
    std::vector<int> lengths;
    std::string word;
    int acc = 0;
    while (std::getline(ss, word, ' '))
    {
        acc += word.size();
        lengths.push_back(acc);
        words.emplace_back(std::move(word));
    }
    std::unordered_map<std::string,int> key_set;
    for (auto i = 0u; i < keys.size(); ++i)
    {
        key_set.emplace(keys[i], i);
    }
    std::unordered_set<std::string> seen;
    int found_all_index{-1};
    int words_count = words.size();
    std::vector<std::vector<int>> last_seen(1, std::vector<int>(keys.size(), -1));
    for (int i = 0; i < words_count; ++i)
    {
        auto found = key_set.find(words[i]);
        if (found != key_set.end())
        {
            if (found_all_index == -1)
            {
                seen.emplace(words[i]);
                if (seen.size() == key_set.size())
                {
                    found_all_index = i;
                }
            }
            last_seen[i][found->second] = i;
        }
        last_seen.push_back(last_seen[i]);
    }
    if (found_all_index == -1)
    {
        return -1;
    }
    int result = std::numeric_limits<int>::max();
    for (int i = found_all_index; i < words_count; ++i)
    {
        int min = std::numeric_limits<int>::max();
        int max = std::numeric_limits<int>::min();
        for (auto position : last_seen[i])
        {
            min = std::min(min, position);
            max = std::max(max, position);
        }
        int length = max - min;
        length += lengths[max];
        if (min > 0)
        {
            length -= lengths[min - 1];
        }
        result = std::min(result, length);
    }
    return result;
}

int main()
{
    std::cout << minimumLength("why how whywhat why what how what when what", { "why", "how", "what" }) << std::endl;
}

