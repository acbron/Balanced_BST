#include "avl_tree.h"
#include "ui_window.h"

AVLTree::AVLTree() {}

AVLTree::AVLTree(QWidget *parent) : BinaryTree()
{
    setParent(parent);
    root = nullptr;
    node_adjust = new NodeAdjust;
    high_light = new QLabel(this);
    high_light->setGeometry(INIT_X - HIGHT_LIGHT_OFFSET,  INIT_Y - HIGHT_LIGHT_OFFSET, HIGH_LIGHT_X, HIGH_LIGHT_Y);
    high_light->setPixmap(QPixmap(":/img/highlight.png"));
    high_light->setVisible(false);

    sequential = new QSequentialAnimationGroup;
    parallel = new QParallelAnimationGroup;
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
   connect(parallel, SIGNAL(finished()), this, SLOT(edgeUpdate()));
   if (parallel->duration() == 0) {
       this->edgeUpdate();
   }
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

void AVLTree::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach (Edge *edge, edges) {
        edge->paint(painter);
    }
}

void AVLTree::RcvInsertClicked(const QString &str)
{
    int value = str.toInt();
    this->insertNode(value);
}

void AVLTree::RcvDeleteClicked(const QString &str)
{
    int value = str.toInt();
    this->deleteNode(value);
}

void AVLTree::RcvSearchClicked(const QString &str)
{
    int value = str.toInt();
    this->findNode(value);
}

void AVLTree::setNodePos()
{
    this->parallel->clear();
    this->setPosHelper(root);
    this->parallel->start();
}

void AVLTree::setNodeLabel(TreeNode **curr)
{
    (*curr)->label = new NodeLabel(this, (*curr)->weight);
    (*curr)->label->setGeometry((*curr)->x, (*curr)->y, FIXED_WIDTH, FIXED_HEIGHT);
    (*curr)->label->show();
}

void AVLTree::setPosHelper(TreeNode *curr)
{
    if (curr == nullptr)
        return;

    int x = curr->x;
    int y = curr->y;
    curr->label->setWeight(curr->weight);

    if (curr->label->x() != x || curr->label->y() != y) {
        QPropertyAnimation *animate = new QPropertyAnimation(curr->label, "pos");
        animate->setDuration(1000);
        animate->setStartValue(QPoint(curr->label->x(), curr->label->y()));
        animate->setEndValue((QPoint(x, y)));
        this->parallel->addAnimation(animate);
    }
    setPosHelper(curr->leftChild);
    setPosHelper(curr->rightChild);
}

void AVLTree::edgeUpdate()
{
    edges.clear();
    edgeUpdateHelper(root);
    update();
}

void AVLTree::edgeUpdateHelper(TreeNode *curr)
{
    if (curr == nullptr)
        return;
    if (curr->leftChild != nullptr) {
        int start_x = curr->x + LEFT_EDGE_X_OFFSET;
        int start_y = curr->y + PARENT_Y_OFFSET;
        int end_x = curr->leftChild->x + SON_X_OFFSET;
        int end_y = curr->leftChild->y;
        Edge *edge = new Edge(start_x, start_y, end_x, end_y);
        edges << edge;
        edgeUpdateHelper(curr->leftChild);
    }
    if (curr->rightChild != nullptr) {
        int start_x = curr->x + RIGHT_EDGE_X_OFFSET;
        int start_y = curr->y + PARENT_Y_OFFSET;
        int end_x = curr->rightChild->x + SON_X_OFFSET;
        int end_y = curr->rightChild->y;
        Edge *edge = new Edge(start_x, start_y, end_x, end_y);
        edges << edge;
        edgeUpdateHelper(curr->rightChild);
    }
}

void AVLTree::setHighLight(int curr_x, int curr_y)
{
    high_light->show();
    high_light->setVisible(true);
    QPropertyAnimation *animate = new QPropertyAnimation(high_light, "pos");

    int start_x = curr_x - HIGHT_LIGHT_OFFSET, start_y = curr_y - HIGHT_LIGHT_OFFSET;
    int end_x = curr_x - HIGHT_LIGHT_OFFSET, end_y = curr_y - HIGHT_LIGHT_OFFSET;

    animate->setStartValue(QPoint(start_x, start_y));
    animate->setEndValue(QPoint(end_x, end_y));
    animate->setDuration(800);

    sequential->addAnimation(animate);
}

void AVLTree::unsetHighLight()
{
    high_light->setVisible(false);
    high_light->setGeometry(INIT_X - HIGHT_LIGHT_OFFSET, INIT_Y - HIGHT_LIGHT_OFFSET, HIGH_LIGHT_X, HIGH_LIGHT_Y);
}
