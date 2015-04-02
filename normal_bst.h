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

protected:
    void paintEvent(QPaintEvent *);

private:
    void edgeUpdate();
    void edgeUpdateHelper(TreeNode *);
};

#endif // NORMAL_BST_H
