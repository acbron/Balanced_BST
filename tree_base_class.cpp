#include "tree_base_class.h"

void Tree::freeMemory(TreeNode *curr) {
    if (curr == nullptr)
        return;

    freeMemory(curr->leftChild);
    freeMemory(curr->rightChild);

    delete curr;
    curr = nullptr;

}
