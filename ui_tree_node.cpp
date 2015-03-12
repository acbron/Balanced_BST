#include "ui_tree_node.h"

const int FIXED_WIDTH = 32;
const int FIXED_HEIGHT = 32;

UiNode::UiNode(QWidget *parent) : QLabel(parent) {}

UiNode::UiNode(QWidget *parent, int _x, int _y, const QString &w) : QLabel(parent), x(_x), y(_y), word(w)
{
    setPixmap(QPixmap(":/img/node.png"));
}

UiNode::~UiNode() {}

void UiNode::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.drawText(0, 0, FIXED_WIDTH, FIXED_HEIGHT, Qt::AlignCenter, word);
}

int UiNode::getX()
{
    return x;
}

int UiNode::getY()
{
    return y;
}

void UiNode::setX(int _x)
{
    x = _x;
}

void UiNode::setY(int _y)
{
    y = _y;
}
