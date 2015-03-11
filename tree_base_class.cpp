#include "tree_base_class.h"

const int INIT_X = 600;
const int INIT_Y = 300;

Tree::Tree() {

}

Tree::~Tree() {

}

void Tree::freeMemory(TreeNode *curr) {
    if (curr == nullptr)
        return;

    freeMemory(curr->leftChild);
    freeMemory(curr->rightChild);

    delete curr;
    curr = nullptr;

}
