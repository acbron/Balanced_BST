#ifndef TREE_NODE_H
#define TREE_NODE_H

/*
 * tree node's color
 */
enum Color {
    normal, red, black
};

struct TreeNode {

    TreeNode() : weight(0),height(0),x(0),y(0),color(normal),leftChild(nullptr),rightChild(nullptr) {
        // no content
    }

    TreeNode(int w) : weight(w),height(0),x(0),y(0),color(normal),leftChild(nullptr),rightChild(nullptr) {
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
    int x;
    int y;
    Color color;
    TreeNode *leftChild;
    TreeNode *rightChild;
};

#endif // TREE_NODE_H
