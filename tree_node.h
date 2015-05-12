#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <QLabel>
#include <QPainter>
#include <QWidget>
#include <QString>
#include "ui_tree_node.h"

extern const int INIT_X;
extern const int INIT_Y;
extern const int INIT_POS_X;
extern const int INIT_POS_Y;

class TreeNode {

private:
    TreeNode();

public:
    TreeNode(int);
    TreeNode(int, Color);
    TreeNode(const TreeNode &);
    TreeNode & operator = (const TreeNode &);
    ~TreeNode();

public:
    int weight;
    int height;
    int x;
    int y;
    Color color;
    int sizes;
    int leftWidths;
    int rightWidths;
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *parent;
    NodeLabel *label;
};

#endif // TREE_NODE_H
