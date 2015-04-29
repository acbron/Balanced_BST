#ifndef BST_BASE_H
#define BST_BASE_H

#include <QWidget>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "tree_node.h"
#include "ui_tree_node.h"
#include "ui_tree_edge.h"
#include "ui_adjustment.h"

extern const int HIGH_LIGHT_X;
extern const int HIGH_LIGHT_Y;
extern const int HIGHT_LIGHT_OFFSET;

class BinaryTree : public QWidget {
    Q_OBJECT
public:
    BinaryTree() ;
    BinaryTree(QWidget *);
    virtual ~BinaryTree();

public:
    virtual void insertNode(int) = 0;
    virtual void deleteNode(int) = 0;
    virtual TreeNode * findNode(int) = 0;

public slots:
    void RcvInsertClicked(const QString &);
    void RcvDeleteClicked(const QString &);
    void RcvSearchClicked(const QString &);
    void setNodePos();
    void unsetHighLight();
    void edgeUpdate();

protected:
    void paintEvent(QPaintEvent *);

protected:
    void setNodeLabel(TreeNode **);
    void setPosHelper(TreeNode *);
    void edgeUpdateHelper(TreeNode *);
    void setHighLight(int, int);

private:
    void freeMemory(TreeNode *);

public:
    TreeNode *root;
    QList <Edge *> edges;
    NodeAdjust *node_adjust;
    QLabel *high_light;
    QSequentialAnimationGroup *sequential;
    QParallelAnimationGroup *parallel;
};

#endif // BST_BASE_H
