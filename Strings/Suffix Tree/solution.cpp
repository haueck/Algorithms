/*
 * Suffix tree
 * Author: Rafal Kozik
 */

#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>

#define LOG(x) std::cout << x << std::endl

class SuffixTree
{
public:

    void addWord(const std::string& w, char delim = '$')
    {
        words.push_back(w + delim);
        for (auto i = 0u; i < words.back().size(); ++i)
        {
            m_root.addWord(words.back(), i, delim);
        }
    }

    void dump()
    {
        m_root.dump(1);
    }

    int edgeExists(const std::string w, int level)
    {
        int count = 0;
        m_root.edgeExists(w, level, 1, count);
        return count;
    }

    int palindrome()
    {
        return m_root.palindrome(words.size());
    }

    struct Node;
    struct Edge
    {

        Edge(const std::string& word, int p_start, char delim = '$') : text(word), start(p_start), end(text.size()), to(nullptr), dict({{ delim, 1 }}) { };
        Edge(const std::string& word, int p_start, int p_end, Node* node, char delim = '$') : text(word), start(p_start), end(p_end), to(node), dict({{ delim, 1 }}) { };

        size_t matches(const std::string& word, int index)
        {
            int l1 = end - start;
            int l2 = static_cast<int>(word.size()) - index;
            int l = l1 < l2 ? l1 : l2;
            for (int i = 0; i < l; ++i)
            {
                if (text[start + i] != word[index + i])
                {
                    return i;
                }
            }
            return l;
        }

        Node* split(int position, char delim = '$')
        {
            if (position > end)
            {
                throw "Position for split() exceeds text's length";
            }
            Node* n = new Node();
            n->edges.emplace_back(text, start + position, end, to, delim);
            to = n;
            end = start + position;
            return n;
        }

        std::string suffix()
        {
            return std::string(text, start, end - start);
        }

        size_t length()
        {
            return end - start;
        }

        void dump()
        {
            LOG("Text: " << text);
            LOG("Start: " << start);
            LOG("End: " << end);
            LOG("Actual: " << suffix());
        }

        const std::string& text;
        int start;
        int end;
        Node* to;
        std::unordered_map<char,int> dict;
    };

    struct Node
    {
        void addWord(const std::string& word, size_t index, char delim)
        {
            for (auto& edge : edges)
            {
                /*
                 * Checks whether an edge and the current word
                 * have the same prefix.
                 */
                auto position = edge.matches(word, index);
                /*
                 * If there is no common prefix, go to the next egde
                 */
                if (position > 0)
                {
                    /*
                     * Mark this edge to be a part of the current word
                     */
                    edge.dict[delim] = 1;
                    /*
                     * If this edge matches the whole word, we are done.
                     * Otherwise, we need to go down the tree
                     */
                    if (position < word.size() - index)
                    {
                        if (position == edge.length())
                        {
                            /*
                             * Whole edge matches the word, go to the next node
                             */
                            edge.to->addWord(word, index + position, delim);
                        }
                        else
                        {
                            /*
                             * Only part of the edge matche, it has to be splitted
                             */
                            Node* node = edge.split(position, delim);
                            node->addWord(word, index + position, delim);
                        }
                    }
                    return;
                }
            }
            /*
             * There was not match, so we add a new edge
             */
            edges.emplace_back(word, index, delim);
        };

        void dump(int depth)
        {
            for (auto& edge : edges)
            {
                LOG(depth << ": " << edge.suffix());
                if (edge.to != nullptr)
                {
                    edge.to->dump(depth + 1);
                }
            }
        };

        void edgeExists(const std::string suffix, int level, int current, int& count)
        {
            for (auto& edge : edges)
            {
                if (level == current && edge.suffix() == suffix)
                {
                    ++count;
                }
                if (edge.to != nullptr)
                {
                    edge.to->edgeExists(suffix, level, current + 1, count);
                }
            }
        };

        int palindrome(size_t count)
        {
            int max = 0;
            for (auto i = 0u; i < edges.size(); ++i)
            {
                if (edges[0].dict.size() == count)
                {
                    int children = 0;
                    if (edges[i].to != nullptr)
                    {
                        children = edges[i].to->palindrome(count);
                    }
                    int total = children + edges[i].length();
                    if (total > max)
                    {
                        max = total;
                    }
                }
            }
            return max;
        }

        std::vector<Edge> edges;
    };

    std::list<std::string> words{};
    Node m_root;
};

TEST(SuffixTree, Edge)
{
    std::vector<std::pair<std::string,std::string>> splits{ {"", "wrotki"}, {"w", "rotki"}, {"wr", "otki"}, {"wro", "tki"}, {"wrot", "ki"}, {"wrotk", "i"}, {"wrotki", ""} };
    std::string t{"wrotki"};
    for (auto i = 0u; i < splits.size(); ++i)
    {
        SuffixTree::Edge e1(t, 0);
        auto e2 = e1.split(i)->edges.back();
        EXPECT_EQ(e1.suffix(), splits[i].first);
        EXPECT_EQ(e2.suffix(), splits[i].second);
    }
    EXPECT_THROW(SuffixTree::Edge(t, 0).split(7), const char*);
    EXPECT_EQ(SuffixTree::Edge(t, 0).matches("wr", 0), 2);
    EXPECT_EQ(SuffixTree::Edge(t, 0).matches("wrotki", 0), 6);
    EXPECT_EQ(SuffixTree::Edge(t, 0).matches("wrotkisuffix", 0), 6);
    EXPECT_EQ(SuffixTree::Edge(t, 0).matches("kolowrotek", 0), 0);
    EXPECT_EQ(SuffixTree::Edge(t, 0).matches("kolowrotek", 4), 4);
    EXPECT_EQ(SuffixTree::Edge(t, 1).matches("kolowrotek", 5), 3);
}

TEST(SuffixTree, SuffixTree)
{
    SuffixTree tree;
    tree.addWord("banana");
    tree.addWord("banana");
    EXPECT_EQ(tree.edgeExists("banana$", 1), 1);
    EXPECT_EQ(tree.edgeExists("na", 1), 1);
    EXPECT_EQ(tree.edgeExists("a", 1), 1);
    EXPECT_EQ(tree.edgeExists("$", 1), 1);
    EXPECT_EQ(tree.edgeExists("na$", 2), 1);
    EXPECT_EQ(tree.edgeExists("na", 2), 1);
    EXPECT_EQ(tree.edgeExists("$", 2), 2);
    EXPECT_EQ(tree.edgeExists("na$", 3), 1);
    EXPECT_EQ(tree.edgeExists("$", 3), 1);
}

TEST(SuffixTree, GeneralizedTree)
{
    SuffixTree tree;
    tree.addWord("toyota", '$');
    tree.addWord("toyota", '$');
    EXPECT_EQ(tree.edgeExists("t", 1), 1);
    EXPECT_EQ(tree.edgeExists("o", 1), 1);
    EXPECT_EQ(tree.edgeExists("$", 1), 1);
    EXPECT_EQ(tree.edgeExists("yota$", 1), 1);
    EXPECT_EQ(tree.edgeExists("a$", 1), 1);
    EXPECT_EQ(tree.edgeExists("yota$", 2), 1);
    EXPECT_EQ(tree.edgeExists("ta$", 2), 1);
    EXPECT_EQ(tree.edgeExists("oyota$", 2), 1);
    EXPECT_EQ(tree.edgeExists("a$", 2), 1);
}

TEST(SuffixTree, Palindrome)
{
    {
        SuffixTree tree;
        tree.addWord("toyota", '$');
        tree.addWord("atoyot", '#');
        EXPECT_EQ(tree.palindrome(), 5);
    }
    {
        SuffixTree tree;
        tree.addWord("banana", '$');
        tree.addWord("ananab", '#');
        EXPECT_EQ(tree.palindrome(), 5);
    }
    {
        SuffixTree tree;
        tree.addWord("sroka", '$');
        tree.addWord("akors", '#');
        EXPECT_EQ(tree.palindrome(), 1);
    }
    {
        SuffixTree tree;
        tree.addWord("oko", '$');
        tree.addWord("oko", '#');
        EXPECT_EQ(tree.palindrome(), 3);
    }
    {
        SuffixTree tree;
        tree.addWord("bla Animal loots foliated detail of stool lamina", '$');
        tree.addWord("Animal loots foliated detail of stool lamina bla", '#');
        EXPECT_EQ(tree.palindrome(), 44);
    }

}
