/*
 * HackerRank - Dreamplay and the String Game
 * https://www.hackerrank.com/contests/101hack48/challenges/dreamplay-and-the-string-game
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

std::string stringGameWinner(std::string s, std::string p)
{
    if (s.size() < p.size())
    {
        return "Steven";
    }
    else if (s.size() == p.size())
    {
        return s == p ? "Amanda" : "Steven";
    }
    else
    {
        auto moves = (s.size() - p.size() + 1) / 2;
        auto found = s.find(p, moves - 1);
		bool left_dist_equal_moves = false;
        while (found != std::string::npos)
        {
            auto end_pos = found + p.size() - 1;
            auto left_dist = found + 1;
            auto right_dist = s.size() - end_pos;
            if (left_dist < right_dist)
            {
                if (left_dist > moves)
                {
                    return "Amanda";
                }
                left_dist_equal_moves = true;
            }
            else
            {
                if (right_dist > moves)
                {
                    return "Amanda";
                }
                else if (left_dist_equal_moves && right_dist == moves)
                {
                    return "Amanda";
                }
                else
                {
                    return "Steven";
                }
            }
            found = s.find(p, found + 1);
        }
    }
    return "Steven";
}

int main()
{
    std::ios::sync_with_stdio(false);
    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++)
	{
        std::string s, p;
        std::cin >> s >> p;
        auto result = stringGameWinner(s, p);
        std::cout << result << std::endl;
    }
}

