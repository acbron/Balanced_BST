#ifndef UI_TREE_EDGE_H
#define UI_TREE_EDGE_H

#include <QString>
#include <QPainter>
#include <QWidget>

extern int BASE_EDGE_LEN;
extern int MOVE_LEN;

class Edge {

private:
    Edge();
    Edge(const Edge &);

public:
    Edge(int, int, int, int);
    ~Edge();
    void paint(QPainter &);
    void setStartCoodinate(int, int);
    void setEndCoodinate(int, int);

private:
    int startX;
    int startY;
    int endX;
    int endY;
};

#endif // UI_TREE_EDGE_H
