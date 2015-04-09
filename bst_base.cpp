#include "bst_base.h"

const int HIGH_LIGHT_X = 42;
const int HIGH_LIGHT_Y = 42;
const int HIGHT_LIGHT_OFFSET = 5;

BinaryTree::BinaryTree() {}

BinaryTree::~BinaryTree() {}

void BinaryTree::freeMemory(TreeNode *curr)
{
    if (curr == nullptr)
        return;

    freeMemory(curr->leftChild);
    freeMemory(curr->rightChild);

    delete curr;
    curr = nullptr;
}

