/*
 * HackerRank - Password Checker
 * https://www.hackerrank.com/challenges/password-cracker/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl

class Node
{
public:

    int depth;
    std::vector<Node*> children{'z' - 'a' + 1, nullptr};
    int words{0};

    Node(int depth) : depth(depth) { };

    void add(const std::string& word, size_t position)
    {
        if (position == word.size())
        {
            ++words;
        }
        else
        {
            auto index = word[position] - 'a';
            if (children[index] == nullptr)
            {
                children[index] = new Node(depth + 1);
            }
            children[index]->add(word, position + 1);
        }
    }

    void remove(const std::string& word, size_t position)
    {
        if (position == word.size())
        {
            --words;
        }
        else
        {
            auto index = word[position] - 'a';
            children[index]->remove(word, position + 1);
        }
    }

    Node* find(const std::string& string, size_t position)
    {
        if (position == string.size())
        {
            return nullptr;
        }
        auto index = string[position] - 'a';
        if (children[index] == nullptr)
        {
            return nullptr;
        }
        else
        {
            if (children[index]->words > 0)
            {
                return children[index];
            }
            else
            {
                return children[index]->find(string, position + 1);
            }
        }
    }

    ~Node()
    {
        for (auto child : children)
        {
            delete child;
        }
    }
};

bool verify(Node* trie, Node* current, std::vector<int>& answer, std::vector<bool>& visited, std::string& attempt, size_t position)
{
    if (trie == current)
    {
        // It is possible that we got here before and we start matching from the beginning once again.
        // For example, for passwords aa and aaa we can match attempt aaaaaa in two ways: aa aa aa or aaa aaa
        if (visited[position])
        {
            return false;
        }
        else
        {
            visited[position] = true;
        }
    }
    if (position == attempt.size())
    {
        return true;
    }
    auto found = current->find(attempt, position);
    if (found != nullptr)
    {
        // There is password that matches at the current position.
        // Let's check if we can match passwords after this one.
        if (verify(trie, trie, answer, visited, attempt, position + found->depth - current->depth))
        {
            answer.push_back(found->depth);
            return true;
        }
        // This matched password might be a suffix of another password(s).
        // Let's check if we can match longer password.
        if (verify(trie, found, answer, visited, attempt, position + found->depth - current->depth))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::cin >> N;
        auto trie = new Node(0);
        std::vector<std::string> passwords;
        for (int i = 0; i < N; ++i)
        {
            std::string password;
            std::cin >> password;
            trie->add(password, 0);
            passwords.push_back(password);
        }
        // Remove passwords that can be created by concatenating other passwords.
        std::sort(passwords.begin(), passwords.end(), [](const std::string& a, const std::string& b) { return a.size() < b.size(); });
        for (auto password : passwords)
        {
            std::vector<int> answer;
            std::vector<bool> visited(password.size());
            trie->remove(password, 0);
            bool success = verify(trie, trie, answer, visited, password, 0);
            if (!success)
            {
                trie->add(password, 0);
            }
        }
        std::string attempt;
        std::cin >> attempt;
        std::vector<int> answer;
        std::vector<bool> visited(attempt.size());
        auto success = verify(trie, trie, answer, visited, attempt, 0);
        if (success)
        {
            std::reverse(answer.begin(), answer.end());
            int current = 0;
            for (auto length : answer)
            {
                std::cout << attempt.substr(current, length) << " ";
                current += length;
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "WRONG PASSWORD" << std::endl;
        }
        delete trie;
    }
}

