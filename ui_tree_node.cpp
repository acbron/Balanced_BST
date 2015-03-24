#include "ui_tree_node.h"

const int FIXED_WIDTH = 32;
const int FIXED_HEIGHT = 32;

UiNode::UiNode(QWidget *parent) : QLabel(parent), ref_node(nullptr) {}

UiNode::UiNode(QWidget *parent, const QString &w) : QLabel(parent), word(w), ref_node(nullptr)
{
    setPixmap(QPixmap(":/img/Green.png"));
}

UiNode::~UiNode() {}
/*
void UiNode::setTarget(TreeNode **node)
{
    if (ref_node != nullptr) {
        return;
    }
    ref_node = &(*node);
}*/

void UiNode::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.drawText(0, 0, FIXED_WIDTH, FIXED_HEIGHT, Qt::AlignCenter, word);
}
