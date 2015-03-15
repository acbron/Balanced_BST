#include "tree_base_class.h"

const int INIT_X = 568;
const int INIT_Y = 0;
const int VERTICAL_OFFSET = 32;
const int ADD_X = 64;
const int ADD_Y = 64;

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
