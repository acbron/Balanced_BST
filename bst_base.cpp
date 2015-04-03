#include "bst_base.h"

const int HIGH_LIGHT_X = 42;
const int HIGH_LIGHT_Y = 42;
const int HIGHT_LIGHT_OFFSET = 5;

BinaryTree::BinaryTree() {}

BinaryTree::~BinaryTree() {}

void BinaryTree::setNodePos(TreeNode *curr)
{
    QParallelAnimationGroup *parallel = new QParallelAnimationGroup;
    setPosHelper(&parallel, curr);
    parallel->start();
}

void BinaryTree::setNodeLabel(QWidget *parent, TreeNode **curr)
{
    (*curr)->label = new NodeLabel(parent, (*curr)->weight);
    (*curr)->label->setGeometry((*curr)->x, (*curr)->y, FIXED_WIDTH, FIXED_HEIGHT);
    (*curr)->label->show();
}

void BinaryTree::setPosHelper(QParallelAnimationGroup **pg, TreeNode *curr)
{
    if (curr == nullptr)
        return;

    int x = curr->x;
    int y = curr->y;
    QPropertyAnimation *animate = new QPropertyAnimation(curr->label, "pos");
    animate->setDuration(1000);
    animate->setStartValue(QPoint(curr->label->x(), curr->label->y()));
    animate->setEndValue((QPoint(x, y)));
    (*pg)->addAnimation(animate);

    setPosHelper(pg, curr->leftChild);
    setPosHelper(pg, curr->rightChild);
}

void BinaryTree::freeMemory(TreeNode *curr)
{
    if (curr == nullptr)
        return;

    freeMemory(curr->leftChild);
    freeMemory(curr->rightChild);

    delete curr;
    curr = nullptr;
}

