#ifndef TREE_BASE_CLASS_H
#define TREE_BASE_CLASS_H

#include <queue>
#include <QPoint>
#include "tree_node.h"
#include <QDebug>

extern const int INIT_X;
extern const int INIT_Y;
extern const int VERTICAL_OFFSET;
extern const int ADD_X;
extern const int ADD_Y;

class Tree {

private:
    Tree(const Tree &);
    Tree & operator = (const Tree &);

public:
    Tree();
    virtual ~Tree();

public:
    virtual void insert(int) = 0;
    virtual void remove(int) = 0;
    virtual bool search(int) = 0;

protected:
    void freeMemory(TreeNode *);

public:
    std::queue < std::pair<int, QPoint> > movement;
};

#endif // TREE_BASE_CLASS_H
