#ifndef UI_ADJUSTMENT_H
#define UI_ADJUSTMENT_H

#include <vector>
#include "tree_node.h"
#include "ui_tree_node.h"
#include "tree_base_class.h"

struct ActionTuple;

class NodeAdjust {

public:
    NodeAdjust();
    ~NodeAdjust();

public:
    void adjustNodePosition(const TreeNode *, const TreeNode *, std::queue <ActionTuple> &parallelMovement);
    void addLocateLeft(TreeNode *);
    void addLocateRight(TreeNode *);
    void reset();

private:
    std::vector <TreeNode *> locateLeft;
    std::vector <TreeNode *> locateRight;
};

#endif // UI_ADJUSTMENT_H
