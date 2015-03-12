#include "binary_search_tree.h"

BinarySearchTree::BinarySearchTree() : root(nullptr)
{
    // no content
}

BinarySearchTree::~BinarySearchTree()
{
    freeMemory(root);
}

void BinarySearchTree::insert(int w)
{
    TreeNode *prev = nullptr;
    TreeNode *curr = root;

    TreeNode *new_node = new TreeNode(w);
    movement.push(std::make_pair(w, QPoint(new_node->x, new_node->y)));

    while (curr != nullptr) {
        prev = curr;

        movement.push(std::make_pair(w, QPoint(curr->x, curr->y)));

        if (curr->weight > w)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }

    if (prev == nullptr) {
        movement.push(std::make_pair(w, QPoint(INIT_X, INIT_Y)));
        new_node->x = INIT_X;
        new_node->y = INIT_Y;
        root = new_node;
    } else {
        if (prev->weight > w)
            prev->leftChild = new_node;
        else
            prev->rightChild = new_node;
    }

    movement.push(std::make_pair(w, QPoint(new_node->x, new_node->y + VERTICAL_OFFSET)));
    new_node->y += VERTICAL_OFFSET;
}

void BinarySearchTree::remove(int w)
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
        if (curr->leftChild != nullptr && curr->rightChild != nullptr) {
            TreeNode *successor = curr->rightChild;
            TreeNode *parent = curr;

            while (successor->leftChild != nullptr) {
                parent = successor;
                successor = successor->leftChild;
            }

            curr->weight = successor->weight;
            parent->leftChild = successor->rightChild;

            delete successor;
            successor = nullptr;

        } else {
            if (curr->leftChild != nullptr) {
                if (prev->leftChild == curr)
                    prev->leftChild = curr->leftChild;
                else
                    prev->rightChild = curr->rightChild;
            } else if (curr->rightChild != nullptr) {
                if (prev->leftChild == curr)
                    prev->leftChild = curr->rightChild;
                else
                    prev->rightChild = curr->rightChild;
            }

            delete curr;
            curr = nullptr;
        }
    }
}

bool BinarySearchTree::search(int w)
{
    TreeNode *curr = root;

    while (curr != nullptr) {
        if (curr->weight == w)
            return true;
        else if (curr->weight > w)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }

    return false;
}

/*
void BinarySearchTree::freeMemory(TreeNode *curr)
{
    if (curr == nullptr)
        return;

    freeMemory(curr->leftChild);
    freeMemory(curr->rightChild);

    delete curr;
    curr = nullptr;
}
*/
