/*
 * HackerRank - Even-odd Boxes
 * https://www.hackerrank.com/contests/101hack50/challenges/even-and-odd-boxes/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int calculate_minimum_moves(std::vector<int>& boxes)
{
    int good_to_move = 0;
    int wrong_add_or_remove = 0;
    int wrong_add_only = 0;
    for (auto i = 0u; i < boxes.size(); i++)
    {
        if (i % 2 == 0)
        {
            if (boxes[i] % 2 != 0)
            {
                // It should be even but it is not
                if (boxes[i] == 1)
                {
                    // We need to add chocolates to this box
                    wrong_add_only++;
                }
                else
                {
                    // We can either remove or add chocolates to this box
                    wrong_add_or_remove++;
                    good_to_move += boxes[i] - 3;
                }
            }
            else
            {
                // Get the number of chocolates that can be safely removed
                good_to_move += boxes[i] - 2;
            }
        }
        else
        {
            if (boxes[i] % 2 == 0)
            {
                // It should be odd but it is not
                wrong_add_or_remove++;
                good_to_move += boxes[i] - 2;
            }
            else
            {
                good_to_move += boxes[i] - 1;
            }
        }
        if (good_to_move > 100000)
        {
            // We will never move more chocolates than there are boxes
            good_to_move = 100000;
        }
    }
    // Move chocolates from boxes that have too much to boxes that need one
    int count = std::min(wrong_add_only, wrong_add_or_remove);
    wrong_add_only -= count;
    wrong_add_or_remove -= count;
    if (wrong_add_only > 0)
    {
        if (wrong_add_only % 2 == 0 && good_to_move >= wrong_add_only)
        {
            return count + wrong_add_only;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (wrong_add_or_remove % 2 == 0)
        {
            return count + wrong_add_or_remove / 2;
        }
        else
        {
            return -1;
        }
    }
}

int main()
{
    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++)
    {
        int n;
        std::cin >> n;
        std::vector<int> boxes(n);
        for (int i = 0; i < n; i++)
        {
           std::cin >> boxes[i];
        }
        std::cout << calculate_minimum_moves(boxes) << std::endl;
    }
}

