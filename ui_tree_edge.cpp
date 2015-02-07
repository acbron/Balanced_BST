#include "ui_tree_edge.h"

int BASE_EDGE_LEN = 16;
int MOVE_LEN = 16;

Edge::Edge() {}
Edge::Edge(const Edge &) {}
Edge::~Edge() {}

Edge::Edge(int start_x, int start_y, int end_x, int end_y) :
    startX(start_x), startY(start_y), endX(end_x), endY(end_y)
{

}

void Edge::setStartCoodinate(int x, int y)
{
    startX = x;
    startY = y;
}

void Edge::setEndCoodinate(int x, int y)
{
    endX = x;
    endY = y;
}

void Edge::paint(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(startX, startY, endX, endY);
}

/*
void Point::paint(QPainter &painter)
{
    if (color == Red) {
        painter.setBrush(Qt::red);
        painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap));
    } else if (color == Black) {
        painter.setBrush(Qt::black);
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    } else {
        QColor fillColor(30, 144, 255);
        painter.setBrush(fillColor);
        painter.setPen(QPen(fillColor, 2, Qt::SolidLine, Qt::RoundCap));
    }
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawEllipse(centerX, centerY, POINT_DIAMETER, POINT_DIAMETER); // change magic number later

    QFont newFont;
    newFont.setPointSize(10); //magic number
    painter.setPen(Qt::white);
    painter.setFont(newFont);
    painter.drawText(centerX, centerY, POINT_DIAMETER, POINT_DIAMETER, Qt::AlignCenter, weight);
}
*/
