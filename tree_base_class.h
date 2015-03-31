#ifndef TREE_BASE_CLASS_H
#define TREE_BASE_CLASS_H

#include <vector>
#include <QPoint>
#include "tree_node.h"
#include "ui_tree_edge.h"
#include "ui_adjustment.h"

extern const int INIT_X;
extern const int INIT_Y;
extern const int VERTICAL_OFFSET;
extern const int ADD_X;
extern const int ADD_Y;

class NodeAdjust;

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
    virtual TreeNode *getRoot() = 0;

protected:
    void freeMemory(TreeNode *);

public:
    NodeAdjust *node_adjust;
    static int node_index;
    std::vector <TreeNode *> treeNodeTabel;
    std::vector <int> nodeBitmap;
};

#endif // TREE_BASE_CLASS_H
