#include "ui_window.h"
#include <QtWidgets>

const int BASE_HEIGHT = 768;
const int BASE_WIDTH = 1024;

int CentralWidget::ii = 0;

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createToolBars();

    mainWidget = new CentralWidget(this);

    scrollArea = new QScrollArea;

    scrollArea->setWidget(mainWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    setCentralWidget(scrollArea);

    createStatusBar();

    /*
    QLabel *label = new QLabel(mainWidget);
    label->setPixmap(QPixmap(":/img/node.png"));
   // label->setGeometry(BASE_WIDTH >> 1, BASE_HEIGHT >> 4, 64, 64);
    label->setGeometry(-0.5, -0.5, 64, 64);
*/
   /* QLabel *line = new QLabel(mainWidget);
    QMatrix matrix;
    matrix.rotate(135);
    line->setPixmap(QPixmap(":/img/line.png").transformed(matrix, Qt::SmoothTransformation));
  //  line->setGeometry((BASE_WIDTH >> 1) + 32, (BASE_HEIGHT >> 4) + 32, 200, 200);
    line->setGeometry((BASE_WIDTH >> 1) + 32, (BASE_HEIGHT >> 4), 200, 200);*/

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

    inputAction = new QAction(this);
    insertAction = new QAction(QIcon(":/img/insert.png"), tr("Insert"), this);
    deleteAction = new QAction(QIcon(":/img/delete.png"),tr("Delete"), this);
    searchAction = new QAction(QIcon(":/img/search.png"), tr("Search"), this);
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

void MainWindow::createToolBars()
{
    inputToolBar = addToolBar(tr("&Input"));
    inputLine = new QLineEdit(this);
    inputLine->setPlaceholderText(tr("input a number"));
    inputLine->setStatusTip(tr("input a number"));
    inputToolBar->addWidget(inputLine);

    operateToolBar = addToolBar(tr("Operation"));
    operateToolBar->addAction(insertAction);
    operateToolBar->addAction(deleteAction);
    operateToolBar->addAction(searchAction);
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Status Bar"));
}
