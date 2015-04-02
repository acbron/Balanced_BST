#include "ui_window.h"

const int BASE_HEIGHT = 600;
const int BASE_WIDTH = 1200;
const int MAX_TOOLBAR_HEIGHT = 48;
const int MAX_LINE_EDIT_LENGTH = 128;
const int MAX_LINE_INPUT_LENGTH = 4;
const int MIN_LINE_INPUT_LENGTH = 1;

MainWindow::MainWindow()
{
    createActions();
    createMenus();

    vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(0, 0, 0, 0);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    toolbar = new ToolBar(centralWidget);
    bst = new NormalBst(centralWidget);
    bst->setMinimumSize(BASE_WIDTH, BASE_HEIGHT);

    vlayout->addWidget(toolbar);
    vlayout->addWidget(bst);
    centralWidget->setLayout(vlayout);
    createStatusBar();

    connect(toolbar, SIGNAL(sendInsertClicked(const QString &)), bst, SLOT(RcvInsertClicked(const QString &)));
    connect(toolbar, SIGNAL(sendRemoveClicked(const QString &)), bst, SLOT(RcvDeleteClicked(const QString &)));
    connect(toolbar, SIGNAL(sendSearchClicked(const QString &)), bst, SLOT(RcvSearchClicked(const QString &)));
}

MainWindow::~MainWindow()
{

}



void MainWindow::createActions()
{
    bstAction = new QAction(tr("&Binary Search Tree"), this);
    avlAction = new QAction(tr("&AVL Tree"), this);
    rbtAction = new QAction(tr("&Red Black Tree"), this);
    sbtAction = new QAction(tr("&Size Balanced Tree"), this);

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    selectMenu = menuBar()->addMenu(tr("&Select"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    selectMenu->addAction(bstAction);
    selectMenu->addAction(avlAction);
    selectMenu->addAction(rbtAction);
    selectMenu->addAction(sbtAction);

    helpMenu->addAction(aboutAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Status Bar"));
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

    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeClicked()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchClicked()));
}

void ToolBar::initialize()
{
    initSize();
    initElements();
    initLayout();
    /*
 * Set Background
 *
    QPixmap pixmap = QPixmap(":/img/ToolBar.png").scaled(this->size());
    QPalette Pal(palette());
    Pal.setBrush(QPalette::Background, QBrush(pixmap));
    setAutoFillBackground(true);
    setPalette(Pal);
*/

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
