#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <queue>

/*
 * tree node's color
 */
enum Color {
    normal, red, black
};

enum Action {
    move_left, move_right
};

struct TreeNode {

    TreeNode() : weight(0),height(0),color(normal),leftChild(nullptr),rightChild(nullptr) {
        // no content
    }

    TreeNode(int w) : weight(w),height(0),color(normal),leftChild(nullptr),rightChild(nullptr) {
        // no content
    }

    TreeNode(const TreeNode &rhs) {
        weight = rhs.weight;
        height = rhs.height;
        color = rhs.color;

        if (leftChild != nullptr) {
            delete leftChild;
        }
        if (rightChild != nullptr) {
            delete rightChild;
        }

        leftChild = new TreeNode(*rhs.leftChild);
        rightChild = new TreeNode(*rhs.rightChild);
    }

    TreeNode &operator = (const TreeNode &rhs) {
        weight = rhs.weight;
        height = rhs.height;
        color = rhs.color;

        if (leftChild != nullptr) {
            delete leftChild;
        }
        if (rightChild != nullptr) {
            delete rightChild;
        }

        leftChild = new TreeNode(*rhs.leftChild);
        rightChild = new TreeNode(*rhs.rightChild);

        return *this;
    }

    int weight;
    int height;
    Color color;
    TreeNode *leftChild;
    TreeNode *rightChild;
    std::queue <Action> movement;
};

#endif // TREE_NODE_H
