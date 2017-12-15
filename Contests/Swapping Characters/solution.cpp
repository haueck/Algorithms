/*
 * Codeforces - Swapping Characters
 * http://codeforces.com/contest/903/problem/E
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

#define LOG(x) std::cout << x << std::endl

int main()
{
    int n, k;
    std::cin >> k >> n;
    std::unordered_set<std::string> strings;
    for (int i = 0; i < k; ++i)
    {
        std::string string;
        std::cin >> string;
        strings.emplace(string);
    }
    if (strings.size() == 1)
    {
        auto answer = *(strings.begin());
        std::swap(answer[0], answer[1]);
        LOG(answer);
    }
    else
    {
        auto it = strings.begin();
        auto first = *it;
        auto second = *std::next(it);
        std::vector<int> diffs;
        bool all_unique = true;
        std::vector<int> frequencies('z' - 'a' + 1);
        for (int i = 0; i < n; ++i)
        {
            auto index = first[i] - 'a';
            frequencies[index]++;
            if (frequencies[index] > 1)
            {
                all_unique = false;
            }
            if (first[i] != second[i])
            {
                diffs.push_back(i);
            }
        }
        std::vector<std::string> candidates1, candidates2;
        if (diffs.size() == 4)
        {
            // Initial string can be costructed by swapping those 4 different positions
            candidates1.assign(6, first);
            candidates2.assign(6, second);
            std::vector<std::pair<int,int>> pairs{ {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3} };
            for (int i = 0; i < 6; ++i)
            {
                std::swap(candidates1[i][diffs[pairs[i].first]], candidates1[i][diffs[pairs[i].second]]);
                std::swap(candidates2[i][diffs[pairs[i].first]], candidates2[i][diffs[pairs[i].second]]);
            }
        }
        else if (diffs.size() == 3)
        {
            // Initial string can be costructed by swapping those 3 different positions
            candidates1.assign(3, first);
            candidates2.assign(3, second);
            std::vector<std::pair<int,int>> pairs{ {0, 1}, {0, 2}, {1, 2} };
            for (int i = 0; i < 3; ++i)
            {
                std::swap(candidates1[i][diffs[pairs[i].first]], candidates1[i][diffs[pairs[i].second]]);
                std::swap(candidates2[i][diffs[pairs[i].first]], candidates2[i][diffs[pairs[i].second]]);
            }
        }
        else if (diffs.size() == 2)
        {
            // Those 2 different characters could be swapped with any other characters in the string
            for (int i = 0; i < n; ++i)
            {
                candidates1.push_back(first);
                std::swap(candidates1.back()[i], candidates1.back()[diffs[0]]);
                candidates1.push_back(first);
                std::swap(candidates1.back()[i], candidates1.back()[diffs[1]]);
                candidates2.push_back(second);
                std::swap(candidates2.back()[i], candidates2.back()[diffs[0]]);
                candidates2.push_back(second);
                std::swap(candidates2.back()[i], candidates2.back()[diffs[1]]);
            }
        }
        else
        {
            LOG(-1);
            return 0;
        }
        std::vector<std::string> candidates;
        std::sort(candidates1.begin(), candidates1.end());
        std::sort(candidates2.begin(), candidates2.end());
        std::set_intersection(candidates1.begin(), candidates1.end(), candidates2.begin(), candidates2.end(), std::back_inserter(candidates));
        for (auto& candidate : candidates)
        {
            bool valid = true;
            for (auto& string : strings)
            {
                auto count = 0;
                for (int i = 0; i < n; ++i)
                {
                    if (candidate[i] != string[i])
                    {
                        ++count;
                    }
                }
                if (!((count == 0 && !all_unique) || count == 2))
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                LOG(candidate);
                return 0;
            }
        }
        LOG(-1);
    }
}

