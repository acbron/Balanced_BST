#ifndef NORMAL_BST_H
#define NORMAL_BST_H

#include <QWidget>
#include <QTimer>
#include "bst_base.h"

class NormalBst : public QWidget,BinaryTree {
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

#endif // NORMAL_BST_H
