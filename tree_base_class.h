#ifndef TREE_BASE_CLASS_H
#define TREE_BASE_CLASS_H

#include <queue>
#include <QPoint>
#include "tree_node.h"
#include "ui_tree_edge.h"
#include "ui_adjustment.h"

extern const int INIT_X;
extern const int INIT_Y;
extern const int VERTICAL_OFFSET;
extern const int ADD_X;
extern const int ADD_Y;

enum ActionType {
    no_type, move_left, move_right
};

struct ActionTuple {
    int value;
    int index;
    ActionType type;
    int x;
    int y;

    ActionTuple() : value(0), index(0), type(no_type), x(0), y(0) {

    }

    ActionTuple(int v, int i, ActionType t, int _x, int _y) : value(v), index(i), type(t), x(_x), y(_y) {

    }
};

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
    void addEdge(const TreeNode *, const TreeNode *, int);

protected:
    void freeMemory(TreeNode *);

public:
    std::queue <ActionTuple> sequentialMovement;
    std::queue <ActionTuple> parallelMovement;
    NodeAdjust *node_adjust;
    QList <Edge *> edges;
};

#endif // TREE_BASE_CLASS_H
