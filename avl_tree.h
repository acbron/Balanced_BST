#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <QWidget>
#include "bst_base.h"

enum Cases {
    none, left_left, left_right, right_right, right_left
};

class AVLTree : public BinaryTree {
    Q_OBJECT
private:
    AVLTree();

public:
    AVLTree(QWidget *);
    ~AVLTree();

public:
    void insertNode(int);
    void  deleteNode(int);
    TreeNode * findNode(int);

private:
    void insertHelper(TreeNode **, int);
    void deleteHelper(TreeNode **, int);
    void adjustHeight(TreeNode **);
    void rotateLeft(TreeNode **);
    void rotateRight(TreeNode **);
    Cases checkCase(TreeNode *);
    void caseLeftLeft(TreeNode **);
    void caseLeftRight(TreeNode **);
    void caseRightRight(TreeNode **);
    void caseRightLeft(TreeNode **);
};

#endif // AVL_TREE_H
