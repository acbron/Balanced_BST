#include "binary_search_tree.h"
#include "ui_window.h"

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

    TreeNode *new_node = new TreeNode(w, ++node_index);
    this->treeNodeTabel.push_back(new_node);

    //sequentialMovement.push(ActionTuple(w, node_index, no_type, new_node->x, new_node->y));

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

TreeNode *BinarySearchTree::getRoot()
{
    return root;
}
