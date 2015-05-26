#ifndef NORMAL_BST_H
#define NORMAL_BST_H

#include <QWidget>
#include <QTimer>
#include "bst_base.h"

class NormalBst : public BinaryTree {
    Q_OBJECT
private:
    NormalBst();

public:
    NormalBst(QWidget *);
    ~NormalBst();

public:
    void insertNode(int);
    void  deleteNode(int);
    TreeNode * findNode(int);

private:
    void deleteHelper(TreeNode **, int);
};

#endif // NORMAL_BST_H
