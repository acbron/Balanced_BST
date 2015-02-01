#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <cstdio>
#include <QList>
#include <QWidget>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QLineEdit>
#include <QPainter>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include "ui_tree_element.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
QT_END_NAMESPACE

extern const int BASE_HEIGHT;
extern const int BASE_WIDTH;

class CentralWidget : public QWidget {
    Q_OBJECT

public:
    CentralWidget() {}
    CentralWidget(QWidget *parent) {
        this->setParent(parent);
    }

    ~CentralWidget() {}

protected:
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        foreach (Point e, list) {
            e.paint(painter);
        }
    }
    void mousePressEvent(QMouseEvent *) {
        ii++;
        Point edge(ii, ii, NoColor, "9527");
        list.push_back(edge);
        update();
    }
private:
    QList <Point>  list;
    static int ii;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    MainWindow();
    ~MainWindow();

    void createActions();
    void createMenus();
    void createToolBars();
    void createLayouts();
    void createStatusBar();

private:

    QMenu *selectMenu;
    QMenu *helpMenu;

    QToolBar *inputToolBar;
    QToolBar *operateToolBar;

    QAction *bstAction;
    QAction *avlAction;
    QAction *rbtAction;
    QAction *sbtAction;
    QAction *aboutAction;
    QAction *inputAction;
    QAction *insertAction;
    QAction *deleteAction;
    QAction *searchAction;

    QLineEdit *inputLine;

    CentralWidget *mainWidget;
    QScrollArea *scrollArea;
};



#endif // UI_WINDOW_H
