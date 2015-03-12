#ifndef UI_TREE_NODE_H
#define UI_TREE_NODE_H

#include <QLabel>
#include <QPainter>
#include <QWidget>
#include <QString>

extern const int FIXED_WIDTH;
extern const int FIXED_HEIGHT;

class UiNode : public QLabel {
    Q_OBJECT

private:
    UiNode(QWidget *);

public:
    UiNode(QWidget *, int, int, const QString &);
    ~UiNode();

public:
    int getX();
    int getY();
    void setX(int);
    void setY(int);

protected:
    void paintEvent(QPaintEvent *);

private:
    int x;
    int y;
    QString word;
};

#endif // UI_TREE_NODE_H
