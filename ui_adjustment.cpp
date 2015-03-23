#include "ui_adjustment.h"

NodeAdjust::NodeAdjust()
{
    reset();
}

NodeAdjust::~NodeAdjust()
{

}

void NodeAdjust::adjustNodePosition(const TreeNode *father, const TreeNode *son, std::queue <ActionTuple> &parallelMovement)
{
    if (father->leftChild == son) {
        for (std::size_t i = 0; i < locateRight.size(); i++) {
            TreeNode *tmp = locateRight[i];
            tmp->x += FIXED_WIDTH;
            parallelMovement.push(ActionTuple(tmp->weight, tmp->id, no_type, tmp->x, tmp->y));
        }
    } else {
        for (std::size_t i = 0; i < locateLeft.size(); i++) {
            TreeNode *tmp = locateLeft[i];
            tmp->x -= FIXED_WIDTH;
            parallelMovement.push(ActionTuple(tmp->weight, tmp->id, no_type, tmp->x, tmp->y));
        }
    }
    reset();
}

void NodeAdjust::addLocateLeft(TreeNode *curr)
{
    locateLeft.push_back(curr);
}

void NodeAdjust::addLocateRight(TreeNode *curr)
{
    locateRight.push_back(curr);
}

void NodeAdjust::reset()
{
    locateLeft.clear();
    locateRight.clear();
}
