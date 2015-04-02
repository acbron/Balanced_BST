#ifndef UI_TREE_EDGE_H
#define UI_TREE_EDGE_H

#include <QString>
#include <QPainter>
#include <QWidget>

extern const int LEFT_EDGE_X_OFFSET;
extern const int RIGHT_EDGE_X_OFFSET;
extern const int SON_X_OFFSET;
extern const int PARENT_Y_OFFSET;

enum EdgeDirection {
    left_edge, right_edge
};

class Edge {

private:
    Edge();
    Edge(const Edge &);

public:
    Edge(int, int, int, int);
    ~Edge();
    void paint(QPainter &);

private:
    int startX;
    int startY;
    int endX;
    int endY;
};

#endif // UI_TREE_EDGE_H
