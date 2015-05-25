#include "bst_base.h"

const int HIGH_LIGHT_X = 42;
const int HIGH_LIGHT_Y = 42;
const int HIGHT_LIGHT_OFFSET = 5;

BinaryTree::BinaryTree() {}

BinaryTree::BinaryTree(QWidget *parent) {
    setParent(parent);

    root = nullptr;
    node_adjust = new NodeAdjust;

    high_light = new QLabel(this);
    high_light->setGeometry(INIT_X - HIGHT_LIGHT_OFFSET,  INIT_Y - HIGHT_LIGHT_OFFSET, HIGH_LIGHT_X, HIGH_LIGHT_Y);
    high_light->setPixmap(QPixmap(":/img/highlight.png"));
    high_light->setVisible(false);

    sequential = new QSequentialAnimationGroup;
    parallel = new QParallelAnimationGroup;
}

BinaryTree::~BinaryTree() {}

void BinaryTree::freeMemory(TreeNode *curr)
{
    if (curr == nullptr)
        return;

    freeMemory(curr->leftChild);
    freeMemory(curr->rightChild);

    delete curr;
    curr = nullptr;
}

void BinaryTree::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach (Edge *edge, edges) {
        edge->paint(painter);
    }
}

void BinaryTree::RcvInsertClicked(const QString &str)
{
    int value = str.toInt();
    this->insertNode(value);
}

void BinaryTree::RcvDeleteClicked(const QString &str)
{
    int value = str.toInt();
    this->deleteNode(value);
}

void BinaryTree::RcvSearchClicked(const QString &str)
{
    int value = str.toInt();
    this->findNode(value);
}

void BinaryTree::setNodePos()
{
    this->parallel->clear();
    this->setPosHelper(root);
    this->parallel->start();
}

void BinaryTree::setNodeLabel(TreeNode **curr)
{
    (*curr)->label = new NodeLabel(this, (*curr)->weight, (*curr)->color);
    (*curr)->label->setGeometry((*curr)->x, (*curr)->y, FIXED_WIDTH, FIXED_HEIGHT);
    (*curr)->label->show();
}

void BinaryTree::setPosHelper(TreeNode *curr)
{
    if (curr == nullptr)
        return;

    int x = curr->x;
    int y = curr->y;

    QPropertyAnimation *animate = new QPropertyAnimation(curr->label, "pos");
    animate->setDuration(1000);
    animate->setStartValue(QPoint(curr->label->x(), curr->label->y()));
    animate->setEndValue((QPoint(x, y)));
    this->parallel->addAnimation(animate);

    setPosHelper(curr->leftChild);
    setPosHelper(curr->rightChild);
}

void BinaryTree::edgeUpdate()
{
    edges.clear();
    edgeUpdateHelper(root);
    update();
}

void BinaryTree::edgeUpdateHelper(TreeNode *curr)
{
    if (curr == nullptr)
        return;
    if (curr->leftChild != nullptr) {
        int start_x = curr->x + LEFT_EDGE_X_OFFSET;
        int start_y = curr->y + PARENT_Y_OFFSET;
        int end_x = curr->leftChild->x + SON_X_OFFSET;
        int end_y = curr->leftChild->y;
        Edge *edge = new Edge(start_x, start_y, end_x, end_y);
        edges << edge;
        edgeUpdateHelper(curr->leftChild);
    }
    if (curr->rightChild != nullptr) {
        int start_x = curr->x + RIGHT_EDGE_X_OFFSET;
        int start_y = curr->y + PARENT_Y_OFFSET;
        int end_x = curr->rightChild->x + SON_X_OFFSET;
        int end_y = curr->rightChild->y;
        Edge *edge = new Edge(start_x, start_y, end_x, end_y);
        edges << edge;
        edgeUpdateHelper(curr->rightChild);
    }
}

void BinaryTree::setHighLight(int curr_x, int curr_y)
{
    high_light->show();
    high_light->setVisible(true);
    QPropertyAnimation *animate = new QPropertyAnimation(high_light, "pos");

    int start_x = curr_x - HIGHT_LIGHT_OFFSET, start_y = curr_y - HIGHT_LIGHT_OFFSET;
    int end_x = curr_x - HIGHT_LIGHT_OFFSET, end_y = curr_y - HIGHT_LIGHT_OFFSET;

    animate->setStartValue(QPoint(start_x, start_y));
    animate->setEndValue(QPoint(end_x, end_y));
    animate->setDuration(800);

    sequential->addAnimation(animate);
}

void BinaryTree::unsetHighLight()
{
    high_light->setVisible(false);
    high_light->setGeometry(INIT_X - HIGHT_LIGHT_OFFSET, INIT_Y - HIGHT_LIGHT_OFFSET, HIGH_LIGHT_X, HIGH_LIGHT_Y);
}
