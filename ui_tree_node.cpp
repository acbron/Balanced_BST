#include "ui_tree_node.h"

const int FIXED_WIDTH = 32;
const int FIXED_HEIGHT = 32;

NodeLabel::NodeLabel(QWidget *parent) : QLabel(parent) {}

NodeLabel::NodeLabel(const NodeLabel &rhs) {}

NodeLabel & NodeLabel::operator = (const NodeLabel &rhs)
{
    return *this;
}

NodeLabel::NodeLabel(QWidget *parent, int w) : QLabel(parent), weight(w)
{
    setPixmap(QPixmap(":/img/Green.png"));
}

NodeLabel::~NodeLabel()  {}

void NodeLabel::setWeight(int w)
{
    this->weight = w;
    update();
}

void NodeLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    QString word;
    word.setNum(weight);
    painter.drawText(0, 0, FIXED_WIDTH, FIXED_HEIGHT, Qt::AlignCenter, word);
}
