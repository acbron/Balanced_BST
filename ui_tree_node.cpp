#include "ui_tree_node.h"

const int FIXED_WIDTH = 32;
const int FIXED_HEIGHT = 32;

UiNode::UiNode(QWidget *parent) : QLabel(parent) {}

UiNode::UiNode(QWidget *parent, int _x, int _y) : QLabel(parent), x(_x), y(_y)
{
    setPixmap(QPixmap(":/img/node.png"));
}

UiNode::~UiNode() {}

void UiNode::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.drawText(0, 0, 32, 32, Qt::AlignCenter, "9527");
}
