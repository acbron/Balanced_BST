#ifndef UI_TREE_NODE_H
#define UI_TREE_NODE_H

#include <QLabel>
#include <QPainter>
#include <QWidget>
#include <QString>
#include "tree_node.h"

extern const int FIXED_WIDTH;
extern const int FIXED_HEIGHT;

class UiNode : public QLabel {
    Q_OBJECT

private:
    UiNode(QWidget *);

public:
    UiNode(QWidget *, const QString &);
    ~UiNode();
    void setNumber(const QString &);

protected:
    void paintEvent(QPaintEvent *);

private:
    QString word;
};

#endif // UI_TREE_NODE_H
