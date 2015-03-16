#ifndef TREE_BASE_CLASS_H
#define TREE_BASE_CLASS_H

#include <queue>
#include <QPoint>
#include "tree_node.h"

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
    ActionType type;
    int x;
    int y;

    ActionTuple() : value(0), type(no_type), x(0), y(0) {

    }

    ActionTuple(int v, ActionType t, int _x, int _y) : value(v), type(t), x(_x), y(_y) {

    }
};

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
    std::queue <ActionTuple> movement;
};

#endif // TREE_BASE_CLASS_H
