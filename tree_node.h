#ifndef TREE_NODE_H
#define TREE_NODE_H

/*
 * tree node's color
 */
enum Color {
    normal, red, black
};

struct TreeNode {

    TreeNode() : weight(0),id(0),height(0),x(0),y(0),color(normal),
        leftWidths(0), rightWidths(0), leftChild(nullptr),rightChild(nullptr)
    {
        // no content
    }

    TreeNode(int w, int _id) : weight(w),id(_id),height(0),x(0),y(0),color(normal),
        leftWidths(0), rightWidths(0), leftChild(nullptr),rightChild(nullptr)
    {
        // no content
    }

    TreeNode(const TreeNode &rhs) {
        weight = rhs.weight;
        id = rhs.id;
        height = rhs.height;
        x = rhs.x;
        y = rhs.y;
        color = rhs.color;
        leftWidths = rhs.leftWidths;
        rightWidths = rhs.rightWidths;

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
        id = rhs.id;
        height = rhs.height;
        x = rhs.x;
        y = rhs.y;
        color = rhs.color;
        leftWidths = rhs.leftWidths;
        rightWidths = rhs.rightWidths;

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
    int id;
    int height;
    int x;
    int y;
    Color color;
    int leftWidths;
    int rightWidths;
    TreeNode *leftChild;
    TreeNode *rightChild;
};


#endif // TREE_NODE_H
