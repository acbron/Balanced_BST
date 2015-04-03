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
    this->setNodeLabel(this, &new_node);

    QSequentialAnimationGroup *sg = new QSequentialAnimationGroup;

    while (curr != nullptr) {
        prev = curr;
        this->setHighLight(&sg, curr->x, curr->y);

        if (curr->weight > w)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }

    sg->start();
    connect(sg, SIGNAL(finished()), this, SLOT(unsetHighLight()));

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
    this->setNodePos(root);
    this->edgeUpdate();
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

            if (curr->parent->leftChild == curr)
                curr->parent->leftChild = successor;
            else if (curr->parent->rightChild == curr)
                curr->parent->rightChild = successor;
            successor->leftChild = curr->leftChild;
            successor->rightChild = curr->rightChild;

            delete curr;
            curr = nullptr;
        } else {
            if (curr->leftChild != nullptr) {
                if (curr->parent->leftChild == curr)
                    curr->parent->leftChild = curr->leftChild;
                else if (curr->parent->rightChild == curr)
                    curr->parent->rightChild = curr->leftChild;

                delete curr;
                curr = nullptr;
            } else if (curr->rightChild != nullptr) {
                if (curr->parent->leftChild == curr)
                    curr->parent->leftChild = curr->rightChild;
                else if (curr->parent->rightChild == curr)
                    curr->parent->rightChild = curr->rightChild;

                delete curr;
                curr = nullptr;
            }
        }
    }
    node_adjust->resizeTree(&root);
    this->setNodePos(root);
    this->edgeUpdate();
}

TreeNode * NormalBst::findNode(int w)
{
    QSequentialAnimationGroup *sg = new QSequentialAnimationGroup;

    TreeNode *curr = root;

    while (curr != nullptr) {
        this->setHighLight(&sg, curr->x, curr->y);
        if (curr->weight == w)
            break;
        else if (curr->weight > w)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }

    sg->start();
    connect(sg, SIGNAL(finished()), this, SLOT(unsetHighLight()));

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

void NormalBst::setHighLight(QSequentialAnimationGroup **sg, int pos_x, int pos_y)
{
    high_light->show();
    high_light->setVisible(true);
    QPropertyAnimation *animate = new QPropertyAnimation(high_light, "pos");

    pos_x -= HIGHT_LIGHT_OFFSET;
    pos_y -= HIGHT_LIGHT_OFFSET;

    animate->setStartValue(QPoint(high_light->x(), high_light->y()));
    animate->setEndValue(QPoint(pos_x, pos_y));

    if (pos_x == high_light->x() && pos_y == high_light->y()) {
        animate->setDuration(500);
        high_light->setGeometry(pos_x, pos_y, HIGH_LIGHT_X, HIGH_LIGHT_Y);
        (*sg)->addAnimation(animate);
    } else {
        animate->setDuration(1000);
        high_light->setGeometry(pos_x, pos_y, HIGH_LIGHT_X, HIGH_LIGHT_Y);
        (*sg)->addAnimation(animate);

        QPropertyAnimation *stay = new QPropertyAnimation(high_light, "pos");
        stay->setDuration(500);
        stay->setStartValue(QPoint(high_light->x(), high_light->y()));
        stay->setEndValue(QPoint(high_light->x(), high_light->y()));
        (*sg)->addAnimation(stay);
    }
}

void NormalBst::unsetHighLight()
{
    high_light->setGeometry(root->x, root->y, HIGH_LIGHT_X, HIGH_LIGHT_Y);
    high_light->setVisible(false);
}

/*
 * buffer
 *
void NormalBst::deleteNode(int w)
{
    TreeNode *prev = nullptr;
    TreeNode *curr = root;

    while (curr != nullptr) {
        if (curr->weight == w) {
            break;
        } else {
            prev = curr;

            if (curr->weight > w)
                curr = curr->leftChild;
            else
                curr = curr->rightChild;
        }
    }

    if (curr != nullptr) {
        if (curr->leftChild == nullptr && curr->rightChild == nullptr) {
            if (curr == root) {
                root = nullptr;
            } else {
                if (prev->leftChild == curr)
                    prev->leftChild = nullptr;
                else if (prev->rightChild == curr)
                    prev->rightChild = nullptr;
            }
            delete curr;
            curr = nullptr;
        } else if (curr->leftChild != nullptr && curr->rightChild != nullptr) {
            TreeNode *successor = curr->rightChild;
            TreeNode *parent = curr;

            while (successor->leftChild != nullptr) {
                parent = successor;
                successor = successor->leftChild;
            }

            if (parent->leftChild == successor)
                parent->leftChild = successor->rightChild;
            else if (parent->rightChild == successor)
                parent->rightChild = successor->rightChild;

            curr->weight = successor->weight;

            delete successor;
            successor = nullptr;
        } else {
            if (curr->leftChild != nullptr) {
                TreeNode *tmp = curr->leftChild;
                curr->leftChild = tmp->leftChild;
                curr->rightChild = tmp->rightChild;
                curr->weight = tmp->weight;

                delete tmp;
                tmp = nullptr;
            } else if (curr->rightChild != nullptr) {
                TreeNode *tmp = curr->rightChild;
                curr->leftChild = tmp->leftChild;
                curr->rightChild = tmp->rightChild;
                curr->weight = tmp->weight;

                delete tmp;
                tmp = nullptr;
            }
        }
    }
    node_adjust->resizeTree(&root);
    this->setNodePos(root);
    this->edgeUpdate();
}
*/
