#include "red_black_tree.h"
#include "ui_window.h"

RBTree::RBTree() : BinaryTree() {}

RBTree::RBTree(QWidget *parent) : BinaryTree(parent)
{
    setParent(parent);
}

RBTree::~RBTree()
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

void RBTree::insertNode(int w)
{
    sequential->clear();

    TreeNode *new_node = new TreeNode(w, red);
    this->setNodeLabel(&new_node);
    TreeNode *curr = root, *prev = nullptr;

    while (curr != nullptr) {
        this->setHighLight(curr->x, curr->y);

        prev = curr;

        if (curr->weight <= w) {
            curr = curr->rightChild;
        } else {
            curr = curr->leftChild;
        }
    }

    if (prev == nullptr) {
        root = new_node;
    } else {

        if (prev->weight <= w) {
            prev->rightChild = new_node;
        } else {
            prev->leftChild = new_node;
        }
        new_node->parent = prev;
    }

    this->insertFixed(&new_node);

    node_adjust->resizeTree(&root);

    sequential->start();
    int total = sequential->animationCount();
    connect(sequential, SIGNAL(finished()), this, SLOT(setNodePos()));

    if (total > 0)
        connect(sequential->animationAt(total - 1), SIGNAL(finished()), this, SLOT(unsetHighLight()));

    connect(sequential, SIGNAL(finished()), this, SLOT(edgeUpdate()));
    connect(sequential, SIGNAL(finished()), this, SLOT(colorUpdate()));

    if (sequential->duration() == 0) {
        this->unsetHighLight();
        this->setNodePos();
        this->edgeUpdate();
        this->colorUpdate();
    }
}

void RBTree::insertFixed(TreeNode **curr)
{
    if ((*curr) == nullptr)
        return;

    TreeNode *parent = nullptr;
    TreeNode *tmp = (*curr);

    while (tmp->color == red) {
        parent = tmp->parent;

        if (parent == nullptr || parent->color != red || parent->parent == nullptr)
            break;

        TreeNode *grandparent = parent->parent;
        TreeNode *uncle = nullptr;

        if (grandparent->leftChild == parent)
            uncle = grandparent->rightChild;
        else if (grandparent->rightChild == parent)
            uncle = grandparent->leftChild;

        if (uncle != nullptr && uncle->color == red) {
            parent->color = black;
            uncle->color = black;
            grandparent->color = red;
        } else {
            if (parent == grandparent->leftChild) {
                if (tmp == parent->rightChild)
                    this->rotateLeft(&parent);

                parent->color = black;
                grandparent->color = red;
                this->rotateRight(&grandparent);

            } else  if (parent == grandparent->rightChild) {
                if (tmp == parent->leftChild)
                    this->rotateRight(&parent);

                parent->color = black;
                grandparent->color = red;
                this->rotateLeft(&grandparent);
            }
        }
        tmp = grandparent;
    }
    root->color = black;
}

void RBTree::deleteNode(int w)
{
    TreeNode *found = nullptr;
    found = this->findNode(w);

    if (found == nullptr)
        return;

    Color delete_color;
    Direction direction;
    TreeNode *parent = nullptr;

    if (found->leftChild != nullptr && found->rightChild != nullptr) {
        TreeNode *successor = found->rightChild;

        while (successor->leftChild != nullptr)
            successor = successor->leftChild;

        parent = successor->parent;

        if (parent->leftChild == successor) {
            parent->leftChild = successor->rightChild;
            direction = _left;
        } else if (parent->rightChild == successor) {
            parent->rightChild = successor->rightChild;
            direction = _right;
        }

        if (successor->rightChild != nullptr)
            successor->rightChild->parent = parent;

        found->weight = successor->weight;
        delete_color = successor->color;
        delete successor;
        successor = nullptr;
    } else if (found->leftChild != nullptr) {
        TreeNode *child = found->leftChild;
        parent = found->parent;
        found->weight = child->weight;
        found->leftChild = nullptr;
        delete_color = child->color;

        if (parent != nullptr) {
            if (parent->leftChild == found)
                direction = _left;
            else if (parent->rightChild == found)
                direction = _right;
        }

        delete child;
        child = nullptr;
    } else if (found->rightChild != nullptr) {
        TreeNode *child = found->rightChild;
        parent = found->parent;
        found->weight = child->weight;
        found->rightChild = nullptr;
        delete_color = child->color;

        if (parent != nullptr) {
            if (parent->leftChild == found)
                direction = _left;
            else if (parent->rightChild == found)
                direction = _right;
        }

        delete child;
        child = nullptr;
    } else {
        parent = found->parent;
        delete_color = found->color;
        if (parent != nullptr) {
            if (parent->leftChild == found) {
                direction = _left;
                parent->leftChild = nullptr;
            } else if (parent->rightChild == found) {
                direction = _right;
                parent->rightChild = nullptr;
            }
        }

        delete found;
        found = nullptr;
    }

    if (parent == nullptr)
        root->color = black;
    else if (delete_color == black)
        this->deleteFixed(&parent, direction);

    node_adjust->resizeTree(&root);

    connect(sequential, SIGNAL(finished()), this, SLOT(setNodePos()));

    if (sequential->duration() == 0) {
        this->setNodePos();
    }

    connect(sequential, SIGNAL(finished()), this, SLOT(edgeUpdate()));
}


void RBTree::deleteFixed(TreeNode **curr, Direction dir)
{
    if ((*curr) == nullptr)
        return;

    TreeNode *tmp = (*curr);
    TreeNode *current = (dir == _left ? tmp->leftChild : tmp->rightChild);

    while (current != root) {
        if (current != nullptr && current->color == red)
            break;

        TreeNode *brother = (dir == _left ? tmp->rightChild : tmp->leftChild);

        if (brother != nullptr && brother->color == red) {
            brother->color = black;
            tmp->color = red;

            if (dir == _left) {
                this->rotateLeft(&tmp);
                tmp = tmp->leftChild;

                if (tmp != nullptr) {
                    current = tmp->leftChild;
                    brother = tmp->rightChild;
                }
            } else if (dir == _right) {
                this->rotateRight(&tmp);
                tmp = tmp->rightChild;

                if (tmp != nullptr) {
                    current = tmp->rightChild;
                    brother = tmp->leftChild;
                }
            }
        }
        if (brother == nullptr) {
            current = tmp;

            if (tmp != nullptr) {
                tmp = tmp->parent;
                if (tmp != nullptr) {
                    if (tmp->leftChild == current)
                        dir = _left;
                    else if (tmp->rightChild == current)
                        dir = _right;
                }
            }
        } else if ((brother->leftChild == nullptr || brother->leftChild->color == black) &&
                   (brother->rightChild == nullptr || brother->rightChild->color == black)) {
            brother->color = red;
            current = tmp;

            if (tmp != nullptr) {
                tmp = tmp->parent;

                if (tmp != nullptr) {
                    if (tmp->leftChild == current)
                        dir = _left;
                    else if (tmp->rightChild == current)
                        dir = _right;
                }
            }
        } else if (brother != nullptr) {
            if (brother->rightChild == nullptr || brother->rightChild->color == black) {
                if (brother->leftChild != nullptr)
                    brother->leftChild->color = black;

                brother->color = red;
                if (dir == _left)
                    this->rotateLeft(&brother);
                else if (dir == _right)
                    this->rotateRight(&brother);
            }
            brother->color = tmp->color;
            tmp->color = black;

            if (dir == _left) {
                this->rotateLeft(&tmp);
                if (brother->rightChild != nullptr)
                    brother->rightChild->color = black;
            } else if (dir == _right) {
                this->rotateRight(&tmp);
                if (brother->leftChild != nullptr)
                    brother->leftChild->color = black;
            }
            current = root;
        }
    }
    current->color = black;
}

TreeNode * RBTree::findNode(int w)
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

void RBTree::rotateLeft(TreeNode **curr)
{
    if ((*curr) == nullptr || (*curr)->rightChild == nullptr)
        return;

    TreeNode *tmp = (*curr)->rightChild;
    (*curr)->rightChild = tmp->leftChild;

    if (tmp->leftChild != nullptr)
        tmp->leftChild->parent = (*curr);

    if ((*curr)->parent == nullptr) {
        root = tmp;
    } else {
        if ((*curr) == (*curr)->parent->leftChild)
            (*curr)->parent->leftChild = tmp;
        else if ((*curr) == (*curr)->parent->rightChild)
            (*curr)->parent->rightChild = tmp;
    }

    tmp->parent = (*curr)->parent;
    tmp->leftChild = (*curr);
    (*curr)->parent = tmp;
    (*curr) = tmp;
}

void RBTree::rotateRight(TreeNode **curr)
{
    if ((*curr) == nullptr || (*curr)->leftChild == nullptr)
        return;

    TreeNode *tmp = (*curr)->leftChild;
    (*curr)->leftChild = tmp->rightChild;

    if (tmp->rightChild != nullptr)
        tmp->rightChild->parent = (*curr);

    if ((*curr)->parent == nullptr) {
        root = tmp;
    } else {
        if ((*curr) == (*curr)->parent->leftChild)
            (*curr)->parent->leftChild = tmp;
        else if ((*curr) == (*curr)->parent->rightChild)
            (*curr)->parent->rightChild = tmp;
    }

    tmp->parent = (*curr)->parent;
    tmp->rightChild = (*curr);
    (*curr)->parent = tmp;
    (*curr) = tmp;
}

void RBTree::colorUpdate()
{
    colorUpdateHelper(root);
}

void RBTree::colorUpdateHelper(TreeNode *curr)
{
    if (curr == nullptr)
        return;
    curr->label->setColor(curr->color);
    colorUpdateHelper(curr->leftChild);
    colorUpdateHelper(curr->rightChild);
}
