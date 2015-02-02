#include "ui_tree_element.h"

Point::Point() : centerX(0), centerY(0), color(NoColor), weight("")
{

}

Point::Point(int center_x, int center_y, Color _color, const QString &_weight) :
    centerX(center_x), centerY(center_y), color(_color), weight(_weight)
{

}

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
    painter.drawEllipse(centerX, centerY, 32, 32); // change magic number later

    QFont newFont;
    newFont.setPointSize(10); //magic number
    painter.setPen(Qt::white);
    painter.setFont(newFont);
    painter.drawText(centerX, centerY, 32, 32, Qt::AlignCenter, weight);
}

void Point::setCenter(int center_x, int center_y)
{
    centerX = center_x;
    centerY = center_y;
}

void Point::setColor(Color _color)
{
    color = _color;
}

void Point::setWeight(const QString &_weight)
{
    weight = _weight;
}

Edge::Edge() : startX(0), startY(0), endX(0), endY(0)
{

}

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
