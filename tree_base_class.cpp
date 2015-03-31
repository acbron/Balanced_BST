#include "tree_base_class.h"
#include "ui_window.h"

const int INIT_X = 568;
const int INIT_Y = 0;

int Tree::node_index = 0;

Tree::Tree() {
    node_adjust = new NodeAdjust;
    treeNodeTabel.clear();
    nodeBitmap.clear();
}

Tree::~Tree() {
    delete node_adjust;
    node_adjust = nullptr;
}

void Tree::freeMemory(TreeNode *curr) {
    if (curr == nullptr)
        return;

    freeMemory(curr->leftChild);
    freeMemory(curr->rightChild);

    delete curr;
    curr = nullptr;

}
