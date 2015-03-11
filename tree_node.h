#ifndef TREE_NODE_H
#define TREE_NODE_H

/*
 * tree node's color
 */
enum Color {
    normal, red, black
};

struct TreeNode {

    TreeNode() : x(0), y(0), weight(0),height(0),color(normal),leftChild(nullptr),rightChild(nullptr) {
        // no content
    }

    TreeNode(int w) : x(0), y(0), weight(w),height(0),color(normal),leftChild(nullptr),rightChild(nullptr) {
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

    int x;
    int y;
    int weight;
    int height;
    Color color;
    TreeNode *leftChild;
    TreeNode *rightChild;
};

#endif // TREE_NODE_H
