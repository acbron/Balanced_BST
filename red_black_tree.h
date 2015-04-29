#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <QWidget>
#include "bst_base.h"

enum Direction {
    _left, _right
};

class RBTree : public QWidget,BinaryTree {
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
    void RcvInsertClicked(const QString &);
    void RcvDeleteClicked(const QString &);
    void RcvSearchClicked(const QString &);
    void setNodePos();
    void unsetHighLight();
    void edgeUpdate();
    void colorUpdate();

protected:
    void paintEvent(QPaintEvent *);

private:
    void setNodeLabel(TreeNode **);
    void setPosHelper(TreeNode *);
    void edgeUpdateHelper(TreeNode *);
    void colorUpdateHelper(TreeNode *);
    void setHighLight(int, int);

private:
    QLabel *high_light;
    QSequentialAnimationGroup *sequential;
    QParallelAnimationGroup *parallel;
};

#endif // RED_BLACK_TREE_H
