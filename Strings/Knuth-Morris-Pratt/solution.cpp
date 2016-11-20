/*
 * Knuth-Morris-Pratt pattern match
 * Author: Rafal Kozik
 */

#include "gtest/gtest.h"
#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

std::vector<int> prefix(const std::string& pattern)
{
    std::vector<int> p(pattern.size() + 1, -1);
    int length = pattern.size();
    for (int i = 1; i <= length; i++)
    {
        int pos = p[i - 1];
        // This loop is executed only when we fail to match.
        // pos==-1 means that we have nothing more to check,
        // we are at the beginning of the table.
        while (
            pos != -1 &&
            pattern[pos] != pattern[i - 1]
        )
        {
            //          01234567
            // Example: AAACAAAA
            //          01201233
            // For 7th element I know that I am not the 4th element in a row.
            // But I need to check if I am 3rd, 2nd, etc
            // Elements under 4, 5 and 6 equal to 0, 1 and 2
            // So let's go back to the beginning of the table
            // because I've already checked those elements.
            // Ok, element before me (6th) was 2nd element in a row (6th == 2nd)
            // So I need to check if I am equal to 3rd. And yes, I am.
            //
            //          01234567
            // Example: ABACABAA
            //          00101231
            //
            // Similarly, I am not 4rd element in a row, let's backtrace.
            // Keeping in mind that 6th == 2nd, I can see that element
            // before me is the first element that matches. Am I 2nd?
            // No, because 2nd element equals to B and I am A.
            // Finally, compare with the first element, yes, matches.
            pos = p[pos];
        }
        p[i] = pos + 1;
    }
    return p;
}

std::vector<int> matches(const std::string& pattern, const std::vector<int>& p, const std::string& text)
{
    std::vector<int> matches;
    int length = pattern.size();
    size_t sp = 0;
    int kp = 0;
    while (sp < text.size())
    {
        /*
        * This loop is only executed when there is no match and
        * we look in the prefix table where we can continue.
        * Text:     ABCDABCGHIJK
        * Pattern:  ABCDABCF
        * Prefix: -100001230
        * If comparison fails on F ne G, we check if previous
        * character has prefix > 0. If it is 0 we go to the beginning
        * of a pattern. If not (it is 3) we can continue from
        * Pattern[3]=D. It is difficult.
        */
        while (kp != -1 && (kp == length || pattern[kp] != text[sp]))
        {
            kp = p[kp];
        }
        kp++;
        sp++;
        if (kp == length)
        {
            matches.push_back(sp - pattern.size());
        }
    }
    return matches;
}

std::vector<int> kmp(const std::string& pattern, const std::string& text)
{
    std::vector<int> p = prefix(pattern);
    return matches(pattern, p, text);
}

void compare(const std::vector<int>& v1, const std::vector<int>& v2)
{
    ASSERT_EQ(v1.size(), v2.size());
    for (size_t i = 0; i < v1.size(); ++i)
    {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

TEST(KnuthMorrisPratt, Test)
{
    compare(prefix("cocacola"), { -1, 0, 0, 1, 0, 1, 2, 0, 0 });
    compare(prefix("aaacaaaa"), { -1, 0, 1, 2, 0, 1, 2, 3, 3 });
    compare(prefix("abacabaa"), { -1, 0, 0, 1, 0, 1, 2, 3, 1 });
    compare(kmp("aba", "abacabaa"), { 0, 4 });
}
