#include "ui_tree_edge.h"
#include "ui_window.h"

const int LEFT_X_OFFSET = 6;
const int RIGHT_X_OFFSET = 26;
const int MIDDLE_X_OFFSET = 16;
const int Y_OFFSET = 30;

Edge::Edge() {}
Edge::Edge(const Edge &) {}
Edge::~Edge() {}

Edge::Edge(int start_x, int start_y, int end_x, int end_y, int s_index, int e_index) :
    startX(start_x), startY(start_y), endX(end_x), endY(end_y),
    startLabelIndex(s_index), endLabelIndex(e_index), dir(left_edge)
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

void Edge::setDirection(EdgeDirection directon)
{
    dir = directon;
}

int Edge::getStartX() const
{
    return startX;
}

int Edge::getStartY() const
{
    return startY;
}

int Edge::getEndX() const
{
    return endX;
}

int Edge::getEndY() const
{
    return endY;
}

EdgeDirection Edge::getDirection() const
{
    return dir;
}

int Edge::getStartIndex() const
{
    return startLabelIndex;
}

int Edge::getEndIndex() const
{
    return endLabelIndex;
}

void Edge::paint(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
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
