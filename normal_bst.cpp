#include "normal_bst.h"
#include "ui_window.h"

NormalBst::NormalBst() {}

NormalBst::NormalBst(QWidget *parent) : BinaryTree()
{
    setParent(parent);
    root = nullptr;
    node_adjust = new NodeAdjust;
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

    while (curr != nullptr) {
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
    }

    node_adjust->resizeTree(&root);
    this->setNodePos(root);
    this->edgeUpdate();
}

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

TreeNode * NormalBst::findNode(int w)
{
    TreeNode *prev = nullptr;
    TreeNode *curr = root;

    while (curr != nullptr) {
        if (prev != nullptr) {
            this->unsetHightLight(prev);
        }
        this->setHightLight(curr);
        if (curr->weight == w)
            break;
        else if (curr->weight > w)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }
    if (prev != nullptr) {
        this->unsetHightLight(prev);
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
    qDebug() << "sucker";
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
