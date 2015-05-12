#include "tree_node.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>

const int INIT_X = 568;
const int INIT_Y = 10;
const int INIT_POS_X = 100;
const int INIT_POS_Y = 100;

TreeNode::TreeNode() {}

TreeNode::TreeNode(int w) :
    weight(w), height(0), x(INIT_POS_X), y(INIT_POS_X), color(normal), sizes(0), leftWidths(0), rightWidths(0),
    leftChild(nullptr), rightChild(nullptr), parent(nullptr), label(nullptr) {}

TreeNode::TreeNode(int w, Color c) :
    weight(w), height(0), x(INIT_POS_X), y(INIT_POS_Y), color(c), sizes(0), leftWidths(0), rightWidths(0),
    leftChild(nullptr), rightChild(nullptr), parent(nullptr), label(nullptr) {}

TreeNode::TreeNode(const TreeNode &rhs) {
    weight = rhs.weight;
    height = rhs.height;
    x = rhs.x;
    y = rhs.y;
    color = rhs.color;
    sizes = rhs.sizes;
    leftWidths = rhs.leftWidths;
    rightWidths = rhs.rightWidths;

    if (leftChild != nullptr) {
        delete leftChild;
    }
    if (rightChild != nullptr) {
        delete rightChild;
    }
    if (parent != nullptr) {
        delete parent;
    }

    leftChild = new TreeNode(*rhs.leftChild);
    rightChild = new TreeNode(*rhs.rightChild);
    parent = new TreeNode(*rhs.parent);
}

TreeNode & TreeNode::operator = (const TreeNode &rhs) {
    weight = rhs.weight;
    height = rhs.height;
    x = rhs.x;
    y = rhs.y;
    color = rhs.color;
    sizes = rhs.sizes;
    leftWidths = rhs.leftWidths;
    rightWidths = rhs.rightWidths;

    if (leftChild != nullptr) {
        delete leftChild;
    }
    if (rightChild != nullptr) {
        delete rightChild;
    }
    if (parent != nullptr) {
        delete parent;
    }

    leftChild = new TreeNode(*rhs.leftChild);
    rightChild = new TreeNode(*rhs.rightChild);
    parent = new TreeNode(*rhs.parent);

    return *this;
}

TreeNode::~TreeNode()
{
    if (label != nullptr) {
        delete label;
        label = nullptr;
    }
}

