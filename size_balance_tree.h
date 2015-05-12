#ifndef SIZE_BALANCE_TREE_H
#define SIZE_BALANCE_TREE_H

#include <QWidget>
#include "bst_base.h"

class SBTree : public BinaryTree {
    Q_OBJECT
private:
    SBTree();

public:
    SBTree(QWidget *);
    ~SBTree();

public:
    void insertNode(int);
    void  deleteNode(int);
    TreeNode * findNode(int);

private:
    void insertHelper(TreeNode **, int);
    void deleteHelper(TreeNode **, int);
    void maintain(TreeNode **);
    void rotateLeft(TreeNode **);
    void rotateRight(TreeNode **);
};

#endif // SIZE_BALANCE_TREE_H
