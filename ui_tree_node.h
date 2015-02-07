#ifndef UI_TREE_NODE_H
#define UI_TREE_NODE_H

#include <QLabel>
#include <QPainter>
#include <QWidget>

extern const int FIXED_WIDTH;
extern const int FIXED_HEIGHT;

class UiNode : public QLabel {
    Q_OBJECT

private:
    UiNode(QWidget *);

public:
    UiNode(QWidget *, int, int);
    ~UiNode();

protected:
    void paintEvent(QPaintEvent *);

private:
    int x;
    int y;
};

#endif // UI_TREE_NODE_H
