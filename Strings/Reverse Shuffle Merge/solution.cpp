/*
 * HackerRank - Reverse Shuffle Merge
 * https://www.hackerrank.com/challenges/reverse-shuffle-merge
 * Author: Rafal Kozik
 */

#include <vector>
#include <iostream>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

const int abc = 'z' - 'a' + 1;

int main()
{
    std::string s;
    std::cin >> s;
    std::reverse(s.begin(), s.end());
    std::vector<int> required(s.size());
    std::vector<int> written(abc);
    std::vector<int> freq(abc);
    std::string result;
    for (int i = 0; i < s.size(); ++i)
    {
        ++freq[s[i] - 'a'];
    }
    for (int i = 0; i < abc; ++i)
    {
        freq[i] /= 2;
        written[i] = freq[i];
    }
    for (int i = s.size() - 1; i >= 0; --i)
    {
        if (written[s[i] - 'a'] > 0)
        {
            required[i] = written[s[i] - 'a']--;
        }
    }
    int current = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (written[s[i] - 'a'] < required[i])
        {
            /*
             * This is the last chance to write character s[i] because
             * there is not enough of those after this point. So we write
             * as many as possible lower characters - first all a then b and so on.
             */
            for (int j = 0; j < s[i] - 'a'; ++j)
            {
                for (int k = current; k <= i; ++k)
                {
                    if (freq[j] == written[j])
                    {
                        break;
                    }
                    if (s[k] - 'a' == j)
                    {
                        result.push_back(j + 'a');
                        written[j]++;
                        current = k + 1;
                    }
                }
            }
            /*
             * Finally, write that required character at the lowest possible index.
             */
            while (s[current] != s[i])
            {
                ++current;
            }
            result.push_back(s[current]);
            written[s[current] - 'a']++;
            ++current;
        }
    }
    LOG(result);
}
 
