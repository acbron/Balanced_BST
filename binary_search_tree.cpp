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
    this->nodeBitmap.push_back(1);

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
        if (curr->leftChild == nullptr && curr->rightChild == nullptr) {
            if (curr == root) {
                this->nodeBitmap[root->id - 1] = 0;
                this->treeNodeTabel[root->id - 1] = nullptr;

                root = nullptr;
            } else {
                if (prev->leftChild == curr)
                    prev->leftChild = nullptr;
                else if (prev->rightChild == curr)
                    prev->rightChild = nullptr;
            }

            this->nodeBitmap[curr->id - 1] = 0;
            this->treeNodeTabel[curr->id - 1] = nullptr;
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

            this->nodeBitmap[successor->id - 1] = 0;
            this->treeNodeTabel[successor->id - 1] = nullptr;

            delete successor;
            successor = nullptr;
        } else {
            if (curr->leftChild != nullptr) {
                TreeNode *tmp = curr->leftChild;
                curr->leftChild = tmp->leftChild;
                curr->rightChild = tmp->rightChild;
                curr->weight = tmp->weight;

                this->nodeBitmap[tmp->id - 1] = 0;
                this->treeNodeTabel[tmp->id - 1] = nullptr;

                delete tmp;
                tmp = nullptr;
            } else if (curr->rightChild != nullptr) {
                TreeNode *tmp = curr->rightChild;
                curr->leftChild = tmp->leftChild;
                curr->rightChild = tmp->rightChild;
                curr->weight = tmp->weight;

                this->nodeBitmap[tmp->id - 1] = 0;
                this->treeNodeTabel[tmp->id - 1] = nullptr;

                delete tmp;
                tmp = nullptr;
            }
        }
    }
    node_adjust->resizeTree(&root);
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
