#include "tree_base_class.h"
#include "ui_window.h"

const int INIT_X = 568;
const int INIT_Y = 0;
const int VERTICAL_OFFSET = 32;
const int ADD_X = 64;
const int ADD_Y = 64;

Tree::Tree() {
    node_adjust = new NodeAdjust;
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

void Tree::addEdge(const TreeNode *first, const TreeNode *second, int index)
{
    Edge *edge = new Edge(first->x, first->y, second->x, second->y, index);

    if (first->leftChild == second)
        edge->setDirection(left_edge);
    else
        edge->setDirection(right_edge);

    if (edge->getDirection() == left_edge)
        edge->setStartCoodinate(edge->getStartX() + LEFT_X_OFFSET, edge->getStartY() + Y_OFFSET + VERTICAL_OFFSET);
    else
        edge->setStartCoodinate(edge->getStartX() + RIGHT_X_OFFSET, edge->getStartY() + Y_OFFSET + VERTICAL_OFFSET);

    edge->setEndCoodinate(edge->getEndX() + MIDDLE_X_OFFSET, edge->getEndY() + VERTICAL_OFFSET);

    edges << edge;
}
