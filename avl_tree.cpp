#include "avl_tree.h"
#include "ui_window.h"

AVLTree::AVLTree() : BinaryTree() {}

AVLTree::AVLTree(QWidget *parent) : BinaryTree(parent)
{
    setParent(parent);
}

AVLTree::~AVLTree()
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

void AVLTree::insertNode(int w)
{
    sequential->clear();

    this->insertHelper(&root, w);

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

    connect(sequential, SIGNAL(finished()), this, SLOT(edgeUpdate()));
}

void AVLTree::insertHelper(TreeNode **curr, int w)
{
    if (*curr == nullptr) {
        (*curr) = new TreeNode(w);
        this->setNodeLabel(curr);
        node_adjust->resizeTree(&root);
        connect(sequential, SIGNAL(finished()), this, SLOT(setNodePos()));
        return;
    }

    this->setHighLight((*curr)->x, (*curr)->y);

    if ((*curr)->weight <= w)
        insertHelper(&(*curr)->rightChild, w);
    else
        insertHelper(&(*curr)->leftChild, w);

    Cases condition = this->checkCase(*curr);

    switch (condition) {
    case left_left:
        caseLeftLeft(curr);
        break;
    case left_right:
        caseLeftRight(curr);
        break;
    case right_right:
        caseRightRight(curr);
        break;
    case right_left:
        caseRightLeft(curr);
        break;
    default:
        break;
    }

    this->adjustHeight(curr);
}

void AVLTree::deleteNode(int w)
{
    TreeNode *found = nullptr;
    found = this->findNode(w);

    if (found == nullptr)
        return;

    deleteHelper(&root, w);
    node_adjust->resizeTree(&root);

    connect(sequential, SIGNAL(finished()), this, SLOT(setNodePos()));
    if (sequential->duration() == 0) {
        this->setNodePos();
    }

    connect(sequential, SIGNAL(finished()), this, SLOT(edgeUpdate()));
}


void AVLTree::deleteHelper(TreeNode **curr, int w)
{
    if ((*curr) == nullptr)
        return;

    if ((*curr)->weight == w) {
        if((*curr)->leftChild != nullptr && (*curr)->rightChild != nullptr) {
            TreeNode *tmp = (*curr)->rightChild;

            while (tmp->leftChild)
                tmp = tmp->leftChild;
            (*curr)->weight = tmp->weight;
            deleteHelper(&((*curr)->rightChild), (*curr)->weight);

        } else if ((*curr)->leftChild != nullptr) {
            (*curr)->weight = (*curr)->leftChild->weight;
            deleteHelper(&((*curr)->leftChild), (*curr)->weight);

        } else if ((*curr)->rightChild != nullptr) {
            (*curr)->weight = (*curr)->rightChild->weight;
            deleteHelper(&((*curr)->rightChild), (*curr)->weight);

        } else {
            delete (*curr);
            (*curr) = nullptr;
            return;
        }
    } else if ((*curr)->weight <= w) {
        deleteHelper(&((*curr)->rightChild), w);
    } else {
        deleteHelper(&((*curr)->leftChild), w);
    }

    Cases condition = this->checkCase((*curr));

    switch (condition) {
    case left_left:
        this->caseLeftLeft(curr);
        break;
    case left_right:
        this->caseLeftRight(curr);
        break;
    case right_right:
        this->caseRightRight(curr);
        break;
    case right_left:
        this->caseRightLeft(curr);
        break;
    default:
        break;
    }
    this->adjustHeight(curr);
}

TreeNode * AVLTree::findNode(int w)
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

void AVLTree::adjustHeight(TreeNode **curr)
{
    if ((*curr) == nullptr)
        return;

    int left_height = -1, right_height = -1;

    if ((*curr)->leftChild != nullptr)
        left_height = (*curr)->leftChild->height;
    if ((*curr)->rightChild != nullptr)
        right_height = (*curr)->rightChild->height;

    (*curr)->height = (left_height > right_height ? left_height : right_height) + 1;
}

void AVLTree::rotateLeft(TreeNode **curr)
{
    if ((*curr) == nullptr || (*curr)->rightChild == nullptr)
        return;

    TreeNode *tmp = (*curr)->rightChild;
    (*curr)->rightChild = tmp->leftChild;
    tmp->leftChild = (*curr);
    (*curr) = tmp;

    this->adjustHeight(&(*curr)->leftChild);
    this->adjustHeight(&(*curr)->rightChild);
    this->adjustHeight(curr);
}

void AVLTree::rotateRight(TreeNode **curr)
{
    if ((*curr) == nullptr || (*curr)->leftChild == nullptr)
        return;

    TreeNode *tmp = (*curr)->leftChild;
    (*curr)->leftChild = tmp->rightChild;
    tmp->rightChild = (*curr);
    (*curr) = tmp;

    this->adjustHeight(&(*curr)->leftChild);
    this->adjustHeight(&(*curr)->rightChild);
    this->adjustHeight(curr);
}

Cases AVLTree::checkCase(TreeNode *curr)
{
    if (curr == nullptr)
        return none;

    int left_height = -1, right_height = -1;
    if (curr->leftChild != nullptr)
        left_height = curr->leftChild->height;
    if (curr->rightChild != nullptr)
        right_height = curr->rightChild->height;

    int delta = left_height - right_height;

    TreeNode *tmp = curr;
    if (delta > -2 && delta < 2) {
        return none;
    } else if (delta == 2) {
        tmp = tmp->leftChild;
        if (tmp->leftChild != nullptr)
            left_height = tmp->leftChild->height;
        else
            left_height = -1;

        if (tmp->rightChild != nullptr)
            right_height = tmp->rightChild->height;
        else
            right_height = -1;

        if (left_height >= right_height)
            return left_left;
        else
            return left_right;
    } else if (delta == -2) {
        tmp = tmp->rightChild;
        if (tmp->leftChild != nullptr)
            left_height = tmp->leftChild->height;
        else
            left_height = -1;

        if (tmp->rightChild != nullptr)
            right_height = tmp->rightChild->height;
        else
            right_height = -1;

        if (left_height <= right_height)
            return right_right;
        else
            return right_left;
    }
    return none;
}

void AVLTree::caseLeftLeft(TreeNode **curr)
{
    if ((*curr) == nullptr)
        return;
    rotateRight(curr);
}

void AVLTree::caseLeftRight(TreeNode **curr)
{
    if ((*curr) == nullptr || (*curr)->leftChild == nullptr)
        return;
    rotateLeft(&(*curr)->leftChild);
    rotateRight(curr);
}

void AVLTree::caseRightRight(TreeNode **curr)
{
    if ((*curr) == nullptr)
        return;
    rotateLeft(curr);
}

void AVLTree::caseRightLeft(TreeNode **curr)
{
    if ((*curr) == nullptr || (*curr)->rightChild == nullptr)
        return;
    rotateRight(&(*curr)->rightChild);
    rotateLeft(curr);
}
