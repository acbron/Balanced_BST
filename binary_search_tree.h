#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "tree_node.h"

class BinarySearchTree {

private:
    BinarySearchTree(const BinarySearchTree &);
    BinarySearchTree & operator = (const BinarySearchTree &);

public:
    BinarySearchTree();
    ~BinarySearchTree();

public:
    void insert(int);
    void remove(int);
    bool search(int);

private:
    void freeMemory(TreeNode *);

private:
    TreeNode *root;
};

#endif // BINARY_SEARCH_TREE