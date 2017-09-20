/*
 * HackerRank - Contacts
 * https://www.hackerrank.com/challenges/contacts
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

class Trie
{
public:

    std::vector<Trie*> children;
    int prefixes{0};
    Trie() : children('z' - 'a' + 1, nullptr) { }

    void add(const std::string& word, uint32_t position)
    {
        ++prefixes;
        if (position == word.size())
        {
            return;
        }
        int index = word[position] - 'a';
        if (children[index] == nullptr)
        {
            children[index] = new Trie;
        }
        children[index]->add(word, position + 1);
    }

    int find(const std::string& word, uint32_t position)
    {
        if (position == word.size())
        {
            return prefixes;
        }
        int index = word[position] - 'a';
        if (children[index] == nullptr)
        {
            return 0;
        }
        return children[index]->find(word, position + 1);
    }

    ~Trie()
    {
        for (auto ptr : children)
        {
            delete ptr;
        }
    }
};

int main()
{
    int q;
    std::cin >> q;
    Trie trie;
    while (q--)
    {
        std::string query, word;
        std::cin >> query >> word;
        if (query == "add")
        {
            trie.add(word, 0);
        }
        else if (query == "find")
        {
            LOG(trie.find(word, 0));
        }
    }
}

