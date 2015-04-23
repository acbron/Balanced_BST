#ifndef UI_TREE_NODE_H
#define UI_TREE_NODE_H

#include <QLabel>
#include <QPainter>
#include <QWidget>
#include <QString>

extern const int FIXED_WIDTH;
extern const int FIXED_HEIGHT;

class NodeLabel : public QLabel {
    Q_OBJECT

private:
    NodeLabel(QWidget *);
    NodeLabel(const NodeLabel &);
    NodeLabel & operator = (const NodeLabel &);

public:
    NodeLabel(QWidget *, int);
    ~NodeLabel();
    void setWeight(int);

protected:
    void paintEvent(QPaintEvent *);

private:
    int weight;
};

#endif // UI_TREE_NODE_H
