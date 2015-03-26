#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtGui>
#include <QObject>
#include <cstdio>
#include <QList>
#include <QString>
#include <QWidget>
#include <QtWidgets>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>
#include <QBrush>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include <QPropertyAnimation>
#include "ui_tree_edge.h"
#include "ui_tree_node.h"
#include "tree_base_class.h"
#include "binary_search_tree.h"
#include <queue>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
QT_END_NAMESPACE

using namespace std;

extern const int BASE_HEIGHT;
extern const int BASE_WIDTH;
extern const int MAX_TOOLBAR_HEIGHT;
extern const int MAX_LINE_EDIT_LENGTH;
extern const int MAX_LINE_INPUT_LENGTH;
extern const int MIN_LINE_INPUT_LENGTH;

const int MAX_LABEL_NUM = 10000;

class WorksWidget;
class ToolBar;

/*
 * MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    MainWindow();
    ~MainWindow();

private:

    void createActions();
    void createMenus();
    void createToolBars();
    void createLayouts();
    void createStatusBar();

private:

    QVBoxLayout *vlayout;
    WorksWidget *workspace;
    ToolBar *toolbar;
    QMenu *selectMenu;
    QMenu *helpMenu;
    QAction *bstAction;
    QAction *avlAction;
    QAction *rbtAction;
    QAction *sbtAction;
    QAction *aboutAction;
};

/*
 * Working Area Widget
 */
class WorksWidget : public QWidget {
    Q_OBJECT

private:
    WorksWidget();

public:
    WorksWidget(QWidget *);
    ~WorksWidget();
    void edgeUpdateHelper(TreeNode *);

protected:
   void paintEvent(QPaintEvent *);

signals:
    void insertSignal() const;
    void removeSignal() const;
    void searchSignal() const;

public slots:
    void insertSlot(const QString &);
    void removeSlot(const QString &);
    void searchSlot(const QString &);
    void labelUpdate();
    void edgeUpdate();

private:
    void sequentialAnimation(QSequentialAnimationGroup *);
    void parallelAnimation(QParallelAnimationGroup *);

private:
    UiNode *label[MAX_LABEL_NUM];
    QList <Edge *> edges;
    bool labelUsed[MAX_LABEL_NUM];

private:
    Tree *bst;
};


/*
 * ToolBar
 */
class ToolBar : public QWidget {
    Q_OBJECT

private:
    ToolBar();

public:
    ToolBar(QWidget *);
    ~ToolBar();

    void paintEvent(QPaintEvent *)
    {
        QPainter p(this);
        p.setPen(QColor(211, 211, 211));
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawRoundedRect(0, 0, width(), height(), 5, 5);
    }

private:
    void initSize();
    void initLayout();
    void initElements();
    void initialize();

signals:
     void sendPaintingSignal(const QString &) const;

public slots:
    void emitPaintingSignal();

private:
    QHBoxLayout *hlayout;
    QLineEdit *insertLine;
    QLineEdit *removeLine;
    QLineEdit *searchLine;
    QPushButton *insertButton;
    QPushButton *removeButton;
    QPushButton *searchButton;
};

#endif // UI_WINDOW_H
