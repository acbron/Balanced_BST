#include "ui_tree_edge.h"
#include "ui_window.h"

const int LEFT_EDGE_X_OFFSET = 6;
const int RIGHT_EDGE_X_OFFSET = 26;
const int SON_X_OFFSET = 16;
const int PARENT_Y_OFFSET = 30;

Edge::Edge() {}
Edge::Edge(const Edge &) {}
Edge::~Edge() {}

Edge::Edge(int start_x, int start_y, int end_x, int end_y) :
    startX(start_x), startY(start_y), endX(end_x), endY(end_y)
{

}

void Edge::paint(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(startX, startY, endX, endY);
}

