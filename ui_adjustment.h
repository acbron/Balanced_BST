#ifndef UI_ADJUSTMENT_H
#define UI_ADJUSTMENT_H

#include <vector>
#include "tree_node.h"

extern const int POSX_OFFSET;
extern const int POSY_OFFSET;

class NodeAdjust {

public:
    NodeAdjust();
    ~NodeAdjust();

public:
    void resizeTree(TreeNode **);
    int resizeWidths(TreeNode **);
    void adjustNodePosition(TreeNode **, int, int, int);
};

#endif // UI_ADJUSTMENT_H
