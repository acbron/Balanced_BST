#include "ui_tree_node.h"

const int FIXED_WIDTH = 32;
const int FIXED_HEIGHT = 32;

NodeLabel::NodeLabel(QWidget *parent) : QLabel(parent) {}

NodeLabel::NodeLabel(QWidget *parent, int w, Color c) : QLabel(parent), weight(w)
{
    if (c == normal)
        setPixmap(QPixmap(":/img/Green.png"));
    else if (c == red)
        setPixmap(QPixmap(":/img/Red.png"));
}

NodeLabel::~NodeLabel()  {}

void NodeLabel::setWeight(int w)
{
    this->weight = w;
    update();
}

void NodeLabel::setColor(Color c)
{
    if (c == normal)
        setPixmap(QPixmap(":/img/Green.png"));
    else if (c == red)
        setPixmap(QPixmap(":/img/Red.png"));
    else if (c == black)
        setPixmap(QPixmap(":/img/Black.png"));
}

void NodeLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    QString word;
    word.setNum(weight);
    painter.setPen(QColor(Qt::white));
    painter.drawText(0, 0, FIXED_WIDTH, FIXED_HEIGHT, Qt::AlignCenter, word);
}
