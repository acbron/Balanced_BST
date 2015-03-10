#ifndef TREE_BASE_CLASS_H
#define TREE_BASE_CLASS_H

#include "tree_node.h"

class Tree {

private:
    Tree(const Tree &);
    Tree & operator = (const Tree &);

public:
    Tree() {}
    virtual ~Tree() {}

public:
    virtual void insert(int) = 0;
    virtual void remove(int) = 0;
    virtual bool search(int) = 0;

protected:
    void freeMemory(TreeNode *);
};

#endif // TREE_BASE_CLASS_H
