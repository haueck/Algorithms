/*
 * HackerRank - Tree: Huffman Decoding
 * Trees
 * https://www.hackerrank.com/challenges/tree-huffman-decoding
 * Author: Rafal Kozik
 */

void decode_huff(node* root, std::string s)
{
    auto p = 0;
    auto c = root;
    while (p < s.size() || c != root)
    {
        if (c->left == nullptr && c->right == nullptr)
        {
            std::cout << c->data;
            c = root;
        }
        else
        {
            if (s[p++] == '0')
            {
                c = c->left;
            }
            else
            {
                c = c->right;
            }
        }
    }
}

