#include "normal_bst.h"
#include "ui_window.h"

NormalBst::NormalBst() : BinaryTree() {}

NormalBst::NormalBst(QWidget *parent) : BinaryTree(parent)
{
    setParent(parent);
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

    if (curr == nullptr)
        return;

    this->deleteHelper(&root, w);
   /* if (curr != nullptr) {
        if (curr->leftChild == nullptr && curr->rightChild == nullptr) {
            if (curr == root) {
                delete root;
                root = nullptr;
            } else {
                if (curr->parent->leftChild == curr)
                    curr->parent->leftChild = nullptr;
                else if (curr->parent->rightChild == curr)
                    curr->parent->rightChild = nullptr;
                delete curr;
                curr = nullptr;
            }
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

            if (curr->parent != nullptr) {
                if (curr->parent->leftChild == curr) {
                    curr->parent->leftChild = successor;
                    successor->parent = curr->parent;
                } else if (curr->parent->rightChild == curr) {
                    curr->parent->rightChild = successor;
                    successor->parent = curr->parent;
                }
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
                if (curr->parent != nullptr) {
                    if (curr->parent->leftChild == curr)
                        curr->parent->leftChild = curr->leftChild;
                    else if (curr->parent->rightChild == curr)
                        curr->parent->rightChild = curr->leftChild;
                }
                curr->leftChild->parent = curr->parent;

                delete curr;
                curr = nullptr;
            } else if (curr->rightChild != nullptr) {
                if (curr->parent != nullptr) {
                    if (curr->parent->leftChild == curr)
                        curr->parent->leftChild = curr->rightChild;
                    else if (curr->parent->rightChild == curr)
                        curr->parent->rightChild = curr->rightChild;
                }
                curr->rightChild->parent = curr->parent;

                delete curr;
                curr = nullptr;
            }
        }
    }*/
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

void NormalBst::deleteHelper(TreeNode **curr, int w)
{
    if ((*curr)->weight < w) {
        this->deleteHelper(&(*curr)->rightChild, w);
    } else if ((*curr)->weight > w) {
        this->deleteHelper(&(*curr)->leftChild, w);
    } else {
        if ((*curr)->leftChild == nullptr && (*curr)->rightChild == nullptr) {
            delete (*curr);
            (*curr) = nullptr;
            return;
        } else {
            if ((*curr)->leftChild != nullptr && (*curr)->rightChild != nullptr) {
                TreeNode *successor = (*curr)->rightChild;
                while (successor->leftChild)
                    successor = successor->leftChild;
                (*curr)->weight = successor->weight;
                this->deleteHelper(&(*curr)->rightChild, successor->weight);
            } else if ((*curr)->leftChild != nullptr) {
                (*curr)->weight = (*curr)->leftChild->weight;
                this->deleteHelper(&(*curr)->leftChild, (*curr)->leftChild->weight);
            } else {
                (*curr)->weight = (*curr)->rightChild->weight;
                this->deleteHelper(&(*curr)->rightChild, (*curr)->rightChild->weight);
            }
        }
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
