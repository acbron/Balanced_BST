#include "size_balance_tree.h"

SBTree::SBTree() : BinaryTree() {}

SBTree::SBTree(QWidget *parent) : BinaryTree(parent)
{
    setParent(parent);
}

SBTree::~SBTree()
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

void SBTree::insertNode(int w)
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

void SBTree::insertHelper(TreeNode **curr, int w)
{
    if (*curr == nullptr) {
        (*curr) = new TreeNode(w);
        this->setNodeLabel(curr);
        node_adjust->resizeTree(&root);
        connect(sequential, SIGNAL(finished()), this, SLOT(setNodePos()));
        return;
    }

    this->setHighLight((*curr)->x, (*curr)->y);

    (*curr)->sizes++;
    if ((*curr)->weight <= w)
        insertHelper(&(*curr)->rightChild, w);
    else
        insertHelper(&(*curr)->leftChild, w);

    this->maintain(curr);
}

void SBTree::deleteNode(int w)
{
    TreeNode *found = nullptr;
    found = this->findNode(w);

    if (found == nullptr)
        return;

    this->deleteHelper(&root, w);
    node_adjust->resizeTree(&root);

    connect(sequential, SIGNAL(finished()), this, SLOT(setNodePos()));
    if (sequential->duration() == 0) {
        this->setNodePos();
    }

    connect(sequential, SIGNAL(finished()), this, SLOT(edgeUpdate()));
}


void SBTree::deleteHelper(TreeNode **curr, int w)
{
    if ((*curr) == nullptr)
        return;

    (*curr)->sizes--;
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
    this->maintain(curr);
}

TreeNode * SBTree::findNode(int w)
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

void SBTree::rotateLeft(TreeNode **curr)
{
    if ((*curr) == nullptr || (*curr)->rightChild == nullptr)
        return;

    TreeNode *tmp = (*curr)->rightChild;
    (*curr)->rightChild = tmp->leftChild;
    tmp->leftChild = (*curr);

    tmp->sizes = (*curr)->sizes;
    int leftSize = (*curr)->leftChild == nullptr ? 0 : (*curr)->leftChild->sizes;
    int rightSize = (*curr)->rightChild == nullptr ? 0 : (*curr)->rightChild->sizes;
    (*curr)->sizes = leftSize + rightSize + 1;
    (*curr) = tmp;
}

void SBTree::rotateRight(TreeNode **curr)
{
    if ((*curr) == nullptr || (*curr)->leftChild == nullptr)
        return;

    TreeNode *tmp = (*curr)->leftChild;
    (*curr)->leftChild = tmp->rightChild;
    tmp->rightChild = (*curr);

    tmp->sizes = (*curr)->sizes;
    int leftSize = (*curr)->leftChild == nullptr ? 0 : (*curr)->leftChild->sizes;
    int rightSize = (*curr)->rightChild == nullptr ? 0 : (*curr)->rightChild->sizes;
    (*curr)->sizes = leftSize + rightSize + 1;
    (*curr) = tmp;
}

void SBTree::maintain(TreeNode **curr)
{
    if ((*curr)->leftChild != nullptr) {
        if ((*curr)->leftChild->leftChild != nullptr &&
                ((*curr)->rightChild == nullptr || (*curr)->leftChild->leftChild->sizes > (*curr)->rightChild->sizes)) {
            this->rotateRight(curr);
            this->maintain(&(*curr)->rightChild);
            this->maintain(curr);
            return;
        }
        if ((*curr)->leftChild->rightChild != nullptr &&
                ((*curr)->rightChild == nullptr || (*curr)->leftChild->rightChild->sizes > (*curr)->rightChild->sizes)) {
            this->rotateLeft(&(*curr)->leftChild);
            this->rotateRight(curr);
            this->maintain(&(*curr)->leftChild);
            this->maintain(&(*curr)->rightChild);
            this->maintain(curr);
            return;
        }
    }
    if ((*curr)->rightChild != nullptr) {
        if ((*curr)->rightChild->rightChild != nullptr &&
                ((*curr)->leftChild == nullptr || (*curr)->rightChild->rightChild->sizes > (*curr)->leftChild->sizes)) {
            this->rotateLeft(curr);
            this->maintain(&(*curr)->leftChild);
            this->maintain(curr);
            return;
        }
        if ((*curr)->rightChild->leftChild != nullptr &&
                ((*curr)->leftChild == nullptr || (*curr)->rightChild->leftChild->sizes > (*curr)->leftChild->sizes)) {
            this->rotateRight(&(*curr)->rightChild);
            this->rotateLeft(curr);
            this->maintain(&(*curr)->leftChild);
            this->maintain(&(*curr)->rightChild);
            this->maintain(curr);
            return;
        }
    }
}
