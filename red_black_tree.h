#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <QWidget>
#include "bst_base.h"

enum Direction {
    _left, _right
};

class RBTree : public BinaryTree {
    Q_OBJECT
private:
    RBTree();

public:
    RBTree(QWidget *);
    ~RBTree();

public:
    void insertNode(int);
    void  deleteNode(int);
    TreeNode * findNode(int);

private:
    void insertFixed(TreeNode **);
    void deleteFixed(TreeNode **, Direction);
    void adjustHeight(TreeNode **);
    void rotateLeft(TreeNode **);
    void rotateRight(TreeNode **);

public slots:
    void colorUpdate();

private:
    void colorUpdateHelper(TreeNode *);
};

#endif // RED_BLACK_TREE_H
