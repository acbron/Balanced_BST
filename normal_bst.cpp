#include "normal_bst.h"
#include "ui_window.h"

NormalBst::NormalBst() {}

NormalBst::NormalBst(QWidget *parent) : BinaryTree()
{
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

NormalBst::~NormalBst()
{
    if (root != nullptr) {
        delete root;
        root = nullptr;
    }
    if (node_adjust != nullptr) {
        delete node_adjust;
        node_adjust = nullptr;
    }
}

void NormalBst::insertNode(int w)
{
    TreeNode *prev = nullptr;
    TreeNode *curr = root;

    TreeNode *new_node = new TreeNode(w);
    this->setNodeLabel(&new_node);
    sequential->clear();

    while (curr != nullptr) {
        this->setHighLight(curr->x, curr->y);

        prev = curr;

        if (curr->weight > w)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }

    if (prev == nullptr) {
        root = new_node;
    } else {
        if (prev->weight > w)
            prev->leftChild = new_node;
        else
            prev->rightChild = new_node;
        new_node->parent = prev;
    }

    node_adjust->resizeTree(&root);

    sequential->start();
    int total = sequential->animationCount();
    connect(sequential, SIGNAL(finished()), this, SLOT(setNodePos()));

    if (total > 0)
        connect(sequential->animationAt(total - 1), SIGNAL(finished()), this, SLOT(unsetHighLight()));

    if (sequential->duration() == 0) {
        this->unsetHighLight();
        this->setNodePos();
    }

   connect(parallel, SIGNAL(finished()), this, SLOT(edgeUpdate()));
   if (parallel->duration() == 0) {
       this->edgeUpdate();
   }
}

void NormalBst::deleteNode(int w)
{
    TreeNode *curr = nullptr;

    curr = this->findNode(w);

    if (curr != nullptr) {
        if (curr->leftChild == nullptr && curr->rightChild == nullptr) {
            if (curr == root) {
                root = nullptr;
            } else {
                if (curr->parent->leftChild == curr)
                    curr->parent->leftChild = nullptr;
                else if (curr->parent->rightChild == curr)
                    curr->parent->rightChild = nullptr;
            }
            delete curr;
            curr = nullptr;
        } else if (curr->leftChild != nullptr && curr->rightChild != nullptr) {
            TreeNode *successor = curr->rightChild;

            while (successor->leftChild != nullptr)
                successor = successor->leftChild;

            if (successor->parent->leftChild == successor)
                successor->parent->leftChild = successor->rightChild;
            else if (successor->parent->rightChild == successor)
                successor->parent->rightChild = successor->rightChild;

            if (successor->rightChild != nullptr)
                successor->rightChild->parent = successor->parent;

            if (curr->parent->leftChild == curr) {
                curr->parent->leftChild = successor;
                successor->parent = curr->parent;
            } else if (curr->parent->rightChild == curr) {
                curr->parent->rightChild = successor;
                successor->parent = curr->parent;
            }
            successor->leftChild = curr->leftChild;
            successor->rightChild = curr->rightChild;

            if (curr->leftChild != nullptr)
                curr->leftChild->parent = successor;
            if (curr->rightChild != nullptr)
                curr->rightChild->parent = successor;

            delete curr;
            curr = nullptr;
        } else {
            if (curr->leftChild != nullptr) {
                if (curr->parent->leftChild == curr)
                    curr->parent->leftChild = curr->leftChild;
                else if (curr->parent->rightChild == curr)
                    curr->parent->rightChild = curr->leftChild;

                curr->leftChild->parent = curr->parent;

                delete curr;
                curr = nullptr;
            } else if (curr->rightChild != nullptr) {
                if (curr->parent->leftChild == curr)
                    curr->parent->leftChild = curr->rightChild;
                else if (curr->parent->rightChild == curr)
                    curr->parent->rightChild = curr->rightChild;

                curr->rightChild->parent = curr->parent;
                delete curr;
                curr = nullptr;
            }
        }
    }
    node_adjust->resizeTree(&root);
    connect(sequential, SIGNAL(finished()), this, SLOT(setNodePos()));
    if (sequential->duration() == 0) {
        this->setNodePos();
    }
   connect(parallel, SIGNAL(finished()), this, SLOT(edgeUpdate()));
   if (parallel->duration() == 0) {
       this->edgeUpdate();
   }
}

TreeNode * NormalBst::findNode(int w)
{
    TreeNode *curr = root;
    sequential->clear();

    while (curr != nullptr) {
        this->setHighLight(curr->x, curr->y);

        if (curr->weight == w)
            break;
        else if (curr->weight > w)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }

    sequential->start();
    connect(sequential, SIGNAL(finished()), this, SLOT(unsetHighLight()));
    if (sequential->duration() == 0) {
        this->unsetHighLight();
    }

    return curr;
}

void NormalBst::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach (Edge *edge, edges) {
        edge->paint(painter);
    }
}

void NormalBst::RcvInsertClicked(const QString &str)
{
    int value = str.toInt();
    this->insertNode(value);
}

void NormalBst::RcvDeleteClicked(const QString &str)
{
    int value = str.toInt();
    this->deleteNode(value);
}

void NormalBst::RcvSearchClicked(const QString &str)
{
    int value = str.toInt();
    this->findNode(value);
}

void NormalBst::setNodePos()
{
    this->parallel->clear();
    this->setPosHelper(root);
    this->parallel->start();
}

void NormalBst::setNodeLabel(TreeNode **curr)
{
    (*curr)->label = new NodeLabel(this, (*curr)->weight, normal);
    (*curr)->label->setGeometry((*curr)->x, (*curr)->y, FIXED_WIDTH, FIXED_HEIGHT);
    (*curr)->label->show();
}

void NormalBst::setPosHelper(TreeNode *curr)
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

void NormalBst::edgeUpdate()
{
    edges.clear();
    edgeUpdateHelper(root);
    update();
}

void NormalBst::edgeUpdateHelper(TreeNode *curr)
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

void NormalBst::setHighLight(int curr_x, int curr_y)
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

void NormalBst::unsetHighLight()
{
    high_light->setVisible(false);
    high_light->setGeometry(INIT_X - HIGHT_LIGHT_OFFSET, INIT_Y - HIGHT_LIGHT_OFFSET, HIGH_LIGHT_X, HIGH_LIGHT_Y);
}
