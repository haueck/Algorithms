/*
 * HackerRank - Binary Search Tree : Lowest Common Ancestor
 * Trees
 * https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor
 * Author: Rafal Kozik
 */

struct retval
{
    bool found;
    node* lca;
    retval(bool found = false, node* lca = nullptr) : found(found), lca(lca) { }
};

retval find(node* root, int v1, int v2)
{
    if (root == nullptr)
    {
        return {};
    }

    bool self = v1 == root->data || v2 == root->data;

    auto left = find(root->left, v1, v2);
    if (left.lca != nullptr)
    {
        return left;
    }

    auto right = find(root->right, v1, v2);
    if (right.lca != nullptr)
    {
        return right;
    }

    if (left.found && right.found)
    {
        return {true, root};
    }
    else if (left.found || right.found)
    {
        if (self)
        {
            return {true, root};
        }
        else
        {
            return {true};
        }
    }
    else
    {
        return {self};
    }

}

node* lca(node* root, int v1, int v2)
{
    auto result = find(root, v1, v2);
    return result.lca;
}
