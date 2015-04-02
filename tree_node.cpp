#include "tree_node.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>

const int INIT_X = 568;
const int INIT_Y = 0;
const int INIT_POS_X = 100;
const int INIT_POS_Y = 100;

TreeNode::TreeNode(){}

TreeNode::TreeNode(int w) :
    weight(w), height(0), x(INIT_POS_X), y(INIT_POS_X), color(normal), leftWidths(0), rightWidths(0),
    leftChild(nullptr), rightChild(nullptr), label(nullptr) {}

TreeNode::TreeNode(const TreeNode &rhs) {
    weight = rhs.weight;
    height = rhs.height;
    x = rhs.x;
    y = rhs.y;
    color = rhs.color;
    leftWidths = rhs.leftWidths;
    rightWidths = rhs.rightWidths;

    if (leftChild != nullptr) {
        delete leftChild;
    }
    if (rightChild != nullptr) {
        delete rightChild;
    }
    leftChild = new TreeNode(*rhs.leftChild);
    rightChild = new TreeNode(*rhs.rightChild);
}

TreeNode & TreeNode::operator = (const TreeNode &rhs) {
    weight = rhs.weight;
    height = rhs.height;
    x = rhs.x;
    y = rhs.y;
    color = rhs.color;
    leftWidths = rhs.leftWidths;
    rightWidths = rhs.rightWidths;

    if (leftChild != nullptr) {
        delete leftChild;
    }
    if (rightChild != nullptr) {
        delete rightChild;
    }

    leftChild = new TreeNode(*rhs.leftChild);
    rightChild = new TreeNode(*rhs.rightChild);

    return *this;
}

TreeNode::~TreeNode()
{
    if (label != nullptr) {
        delete label;
        label = nullptr;
    }
}
