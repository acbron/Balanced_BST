#ifndef UI_TREE_NODE_H
#define UI_TREE_NODE_H

#include <QLabel>
#include <QPainter>
#include <QWidget>
#include <QString>

extern const int FIXED_WIDTH;
extern const int FIXED_HEIGHT;


enum Color {
    normal, red, black
};

class NodeLabel : public QLabel {
    Q_OBJECT

private:
    NodeLabel(QWidget *);

public:
    NodeLabel(QWidget *, int, Color);
    ~NodeLabel();
    void setWeight(int);
    void setColor(Color);

protected:
    void paintEvent(QPaintEvent *);

private:
    int weight;
};

#endif // UI_TREE_NODE_H
