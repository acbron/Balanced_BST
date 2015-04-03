#ifndef NORMAL_BST_H
#define NORMAL_BST_H

#include <QWidget>
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
    void unsetHighLight();

protected:
    void paintEvent(QPaintEvent *);

private:
    void edgeUpdate();
    void edgeUpdateHelper(TreeNode *);
    void setHighLight(QSequentialAnimationGroup **, int, int);

private:
    QLabel *high_light;
};

#endif // NORMAL_BST_H
