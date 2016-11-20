/*
 * Trie implementation
 * Author: Rafal Kozik
 */

#include "gtest/gtest.h"
#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class Trie
{
    struct Node
    {
        Node() : children(26, nullptr) { };
        std::vector<Node*> children;
        int words{0};
        int prefixes{0};
    };

    void addWord(Node* node, const std::string& word, size_t index)
    {
        ++node->prefixes;
        if (index == word.size())
        {
            ++node->words;
        }
        else
        {
            int i = word[index] - 'a';
            if (node->children[i] == nullptr)
            {
                node->children[i] = new Node;
            }
            addWord(node->children[i], word, index + 1);
        }
    }

    int countWords(Node* node, const std::string& word, size_t index)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else if (index == word.size())
        {
            return node->words;
        }
        else
        {
            return countWords(node->children[word[index] - 'a'], word, index + 1);
        }
    }

    int countPrefix(Node* node, const std::string& prefix, size_t index)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else if (index == prefix.size())
        {
            return node->prefixes;
        }
        else
        {
            return countPrefix(node->children[prefix[index] - 'a'], prefix, index + 1);
        }
    }

    void dump(Node* node, char* tmp, int index)
    {
        char c = 'a';
        if (node == nullptr)
        {
            return;
        }
        if (node->words > 0)
        {
            LOG(tmp << ": " << node->words);
        }
        for (auto child : node->children)
        {
            tmp[index] = c++;
            dump(child, tmp, index + 1);
        }
        tmp[index] = '\0';
    }

    Node m_root;

public:

    void addWord(const std::string& word)
    {
        addWord(&m_root, word, 0);
    };

    int countPrefix(const std::string& prefix)
    {
        return countPrefix(&m_root, prefix, 0);
    };

    int countWords(const std::string& word)
    {
        return countWords(&m_root, word, 0);
    };

    void dump()
    {
        std::vector<char> tmp(100, '\0');
        dump(&m_root, tmp.data(), 0);
    };
};

TEST(Trie, Test)
{
    Trie trie;
    trie.addWord("lupa");
    trie.addWord("lupsko");
    trie.addWord("lupeczka");
    trie.addWord("laweczka");
    trie.addWord("lupa");
    trie.addWord("zupa");

    EXPECT_EQ(2, trie.countWords("lupa"));
    EXPECT_EQ(0, trie.countWords("lup"));
    EXPECT_EQ(1, trie.countWords("laweczka"));
    EXPECT_EQ(1, trie.countWords("zupa"));

    EXPECT_EQ(0, trie.countPrefix("c"));
    EXPECT_EQ(1, trie.countPrefix("z"));
    EXPECT_EQ(5, trie.countPrefix("l"));
    EXPECT_EQ(4, trie.countPrefix("lu"));
    EXPECT_EQ(4, trie.countPrefix("lup"));
    EXPECT_EQ(1, trie.countPrefix("lupe"));
}

