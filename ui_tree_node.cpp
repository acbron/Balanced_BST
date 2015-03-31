#include "ui_tree_node.h"

const int FIXED_WIDTH = 32;
const int FIXED_HEIGHT = 32;

UiNode::UiNode(QWidget *parent) : QLabel(parent) {}

UiNode::UiNode(QWidget *parent, const QString &w) : QLabel(parent), word(w)
{
    setPixmap(QPixmap(":/img/Green.png"));
}

UiNode::~UiNode() {}

void UiNode::setNumber(const QString &num)
{
    word = num;
    update();
}

void UiNode::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.drawText(0, 0, FIXED_WIDTH, FIXED_HEIGHT, Qt::AlignCenter, word);
}
