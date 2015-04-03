#ifndef BST_BASE_H
#define BST_BASE_H

#include <QWidget>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>
#include "tree_node.h"
#include "ui_tree_node.h"
#include "ui_tree_edge.h"
#include "ui_adjustment.h"

extern const int HIGH_LIGHT_X;
extern const int HIGH_LIGHT_Y;
extern const int HIGHT_LIGHT_OFFSET;

class BinaryTree {
public:
    BinaryTree() ;
    virtual ~BinaryTree();

public:
    virtual void insertNode(int) = 0;
    virtual void deleteNode(int) = 0;
    virtual TreeNode * findNode(int) = 0;
    void setNodePos(TreeNode *);
    void setNodeLabel(QWidget *, TreeNode **);

private:
    void setPosHelper(QParallelAnimationGroup **, TreeNode *);
    void freeMemory(TreeNode *);

public:
    TreeNode *root;
    QList <Edge *> edges;
    NodeAdjust *node_adjust;
};

#endif // BST_BASE_H
