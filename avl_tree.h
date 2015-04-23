#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <QWidget>
#include "bst_base.h"

enum Cases {
    none, left_left, left_right, right_right, right_left
};

class AVLTree : public QWidget,BinaryTree {
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

public slots:
    void RcvInsertClicked(const QString &);
    void RcvDeleteClicked(const QString &);
    void RcvSearchClicked(const QString &);
    void setNodePos();
    void unsetHighLight();
    void edgeUpdate();

protected:
    void paintEvent(QPaintEvent *);

private:
    void setNodeLabel(TreeNode **);
    void setPosHelper(TreeNode *);
    void edgeUpdateHelper(TreeNode *);
    void setHighLight(int, int);

private:
    QLabel *high_light;
    QSequentialAnimationGroup *sequential;
    QParallelAnimationGroup *parallel;
};

#endif // AVL_TREE_H
