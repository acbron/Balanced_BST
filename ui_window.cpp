#include "ui_window.h"

const int BASE_HEIGHT = 600;
const int BASE_WIDTH = 1200;
const int MAX_TOOLBAR_HEIGHT = 42;
const int MAX_LINE_EDIT_LENGTH = 128;
const int MAX_LINE_INPUT_LENGTH = 4;
const int MIN_LINE_INPUT_LENGTH = 1;

MainWindow::MainWindow()
{
    //setWindowFlags(Qt::FramelessWindowHint);
    vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(0, 0, 0, 0);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    toolbar = new ToolBar(centralWidget);
    bst = nullptr;
    vlayout->addWidget(toolbar);
    this->setBST(0);
    centralWidget->setLayout(vlayout);

    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::white);
    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(p);

    createStatusBar();

    connect(toolbar, SIGNAL(itemChanged(int)), this, SLOT(setBST(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Status Bar"));
}

void MainWindow::setBST(int index)
{
    if (bst != nullptr) {
        delete bst;
        bst = nullptr;
    }
    switch (index) {
    case 0:
        bst = new NormalBst(this->centralWidget);
        break;
    case 1:
        bst = new AVLTree(this->centralWidget);
        break;
    case 2:
        bst = new RBTree(this->centralWidget);
        break;
    case 3:
        bst = new SBTree(this->centralWidget);
        break;
    default:
        break;
    }
    bst->setMinimumSize(BASE_WIDTH, BASE_HEIGHT);
    this->vlayout->addWidget(bst);
    connect(toolbar, SIGNAL(sendInsertClicked(const QString &)), bst, SLOT(RcvInsertClicked(const QString &)));
    connect(toolbar, SIGNAL(sendRemoveClicked(const QString &)), bst, SLOT(RcvDeleteClicked(const QString &)));
    connect(toolbar, SIGNAL(sendSearchClicked(const QString &)), bst, SLOT(RcvSearchClicked(const QString &)));
}

/*
 * ToolBar
 */
ToolBar::ToolBar()
{

}

ToolBar::ToolBar(QWidget *parent)
{
    setParent(parent);
    initialize();
}

ToolBar::~ToolBar()
{

}

void ToolBar::initSize()
{
    setMinimumSize(BASE_WIDTH, MAX_TOOLBAR_HEIGHT);
    setMaximumHeight(MAX_TOOLBAR_HEIGHT);
}

void ToolBar::initLayout()
{
    hlayout = new QHBoxLayout();
    hlayout->setAlignment(Qt::AlignLeft);
    hlayout->addWidget(combo);
    hlayout->addWidget(insertLine);
    hlayout->addWidget(insertButton);
    hlayout->addWidget(removeLine);
    hlayout->addWidget(removeButton);
    hlayout->addWidget(searchLine);
    hlayout->addWidget(searchButton);
    this->setLayout(hlayout);
}

void ToolBar::initElements()
{
    combo = new QComboBox(this);
    combo->setMaximumWidth(180);
    combo->addItem("Binary Search Tree");
    combo->addItem("AVL Tree");
    combo->addItem("Red Black Tree");
    combo->addItem("Size Balanced Tree");
    insertLine = new QLineEdit(this);
    removeLine = new QLineEdit(this);
    searchLine = new QLineEdit(this);

    insertLine->setFixedWidth(MAX_LINE_EDIT_LENGTH);
    removeLine->setFixedWidth(MAX_LINE_EDIT_LENGTH);
    searchLine->setFixedWidth(MAX_LINE_EDIT_LENGTH);

    insertLine->setInputMask(QString("9999"));
    removeLine->setInputMask(QString("9999"));
    searchLine->setInputMask(QString("9999"));

    insertLine->setPlaceholderText(tr("input..."));
    removeLine->setPlaceholderText(tr("input..."));
    searchLine->setPlaceholderText(tr("input..."));

    insertButton = new QPushButton(tr("insert"), this);
    removeButton = new QPushButton(tr("remove"), this);
    searchButton = new QPushButton(tr("search"), this);

    insertButton->setMaximumWidth(60);
    removeButton->setMaximumWidth(60);
    searchButton->setMaximumWidth(60);

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(comboChanged(int)));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeClicked()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchClicked()));
}

void ToolBar::initialize()
{
    initSize();
    initElements();
    initLayout();

    QLinearGradient gradient(0, 0, 0, MAX_TOOLBAR_HEIGHT);
    gradient.setColorAt(0, Qt::gray);
    gradient.setColorAt(1, Qt::black);
    QPalette p(palette());
    QBrush brush(gradient);
    p.setBrush(QPalette::Background, QColor("#d8d8d8"));
    p.setColor(QPalette::Shadow, Qt::red);
    setAutoFillBackground(true);
    setPalette(p);
}

void ToolBar::comboChanged(int index)
{
    emit itemChanged(index);
}

void ToolBar::insertClicked()
{
    QString tmp = insertLine->text();
    emit sendInsertClicked(tmp);
}

void ToolBar::removeClicked()
{
    QString tmp = removeLine->text();
    emit sendRemoveClicked(tmp);
}

void ToolBar::searchClicked()
{
    QString tmp = searchLine->text();
    emit sendSearchClicked(tmp);
}
