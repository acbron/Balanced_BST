#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "tree_base_class.h"

class BinarySearchTree : public Tree{

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
    TreeNode *root;
};

#endif // BINARY_SEARCH_TREE
