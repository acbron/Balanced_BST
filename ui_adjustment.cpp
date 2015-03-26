#include "ui_adjustment.h"
#include "ui_window.h"

const int POSX_OFFSET = 64;
const int POSY_OFFSET = 64;

NodeAdjust::NodeAdjust()
{

}

NodeAdjust::~NodeAdjust()
{

}

void NodeAdjust::resizeTree(TreeNode **ref_node)
{
    this->resizeWidths(ref_node);

    if ((*ref_node) != nullptr)
        this->adjustNodePosition(ref_node, INIT_X, INIT_Y, 0);
}

int NodeAdjust::resizeWidths(TreeNode **ref_node)
{
    if ((*ref_node) == nullptr)
        return 0;

    (*ref_node)->leftWidths = max(resizeWidths(&(*ref_node)->leftChild), POSX_OFFSET / 2);
    (*ref_node)->rightWidths = max(resizeWidths(&(*ref_node)->rightChild), POSY_OFFSET / 2);

    return (*ref_node)->leftWidths + (*ref_node)->rightWidths;
}

void NodeAdjust::adjustNodePosition(TreeNode **ref_node, int x_pos, int y_pos, int side)
{
    if ((*ref_node) != nullptr) {
        (*ref_node)->y = y_pos;

        if (side == -1)
            x_pos = x_pos - (*ref_node)->rightWidths;
        else if (side == 1)
            x_pos = x_pos + (*ref_node)->leftWidths;

        (*ref_node)->x = x_pos;

        adjustNodePosition(&(*ref_node)->leftChild, x_pos, y_pos + POSY_OFFSET, -1);
        adjustNodePosition(&(*ref_node)->rightChild, x_pos, y_pos + POSY_OFFSET, 1);
    }
}

