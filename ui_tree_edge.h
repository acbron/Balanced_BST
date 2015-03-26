#ifndef UI_TREE_EDGE_H
#define UI_TREE_EDGE_H

#include <QString>
#include <QPainter>
#include <QWidget>
#include "tree_node.h"

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
    /*
    void setStartCoodinate(int, int);
    void setEndCoodinate(int, int);
    void setDirection(EdgeDirection);
    int getStartX() const;
    int getStartY() const;
    int getEndX() const;
    int getEndY() const;
    EdgeDirection getDirection() const;
    int getStartIndex() const;
    int getEndIndex() const;
*/
private:
    int startX;
    int startY;
    int endX;
    int endY;
    /*
    int startLabelIndex;
    int endLabelIndex;
    EdgeDirection dir;
    */
};

#endif // UI_TREE_EDGE_H
