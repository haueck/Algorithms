/*
 * HackerRank - Sparse Arrays
 * Arrays
 * https://www.hackerrank.com/challenges/sparse-arrays
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class Node
{
    static const int C = 'z' - 'a' + 1;
    std::vector<Node*> children;
    int words{0};

public:
    Node() : children(C, nullptr) { };

    ~Node()
    {
        for (auto ptr : children)
        {
            if (ptr != nullptr)
            {
                delete ptr;
            }
        }
    }

    void addWord(const std::string& word, unsigned int position = 0)
    {
        if (position == word.size())
        {
            ++words;
        }
        else
        {
            int index = word[position] - 'a';
            if (children[index] == nullptr)
            {
                children[index] = new Node;
            }
            children[index]->addWord(word, position + 1);
        }
    }

    int matches(const std::string& word, unsigned int position = 0)
    {
        if (position == word.size())
        {
            return words;
        }

        int index = word[position] - 'a';
        if (children[index] == nullptr)
        {
            return 0;
        }
        return children[index]->matches(word, position + 1);
    }

};


int main(int argc, char **argv)
{
    Node root;
    int N = 0;
    int Q = 0;
    std::string line;
    line.reserve(20);

    scanf("%d\n", &N);
    for (int i = 0; i < N; ++i)
    {
        std::getline(std::cin, line);
        root.addWord(line);
    }

    scanf("%d\n", &Q);
    for (int i = 0; i < Q; ++i)
    {
        std::getline(std::cin, line);
        LOG(root.matches(line));
    }

    return 0;
}

