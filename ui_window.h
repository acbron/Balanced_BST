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
#include "bst_base.h"
#include "normal_bst.h"
#include "avl_tree.h"
#include "red_black_tree.h"
#include "size_balance_tree.h"

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

protected:
    void resizeEvent(QResizeEvent *);

protected slots:
    void setBST(int);
    void updateStatusBar(const QString &, int, bool);

private:
    void createToolBars();
    void createLayouts();
    void createStatusBar();

private:
    QWidget *centralWidget;
    QVBoxLayout *vlayout;
    BinaryTree *bst;
    ToolBar *toolbar;
    QLabel *status_bar_msg;
};

/*
 * ToolBar
 */
class LineEdit;

class ToolBar : public QWidget {
    Q_OBJECT

private:
    ToolBar();

public:
    ToolBar(QWidget *);
    ~ToolBar();

private:
    void initSize();
    void initLayout();
    void initElements();
    void initialize();

signals:
    void itemChanged(int) const;
    void sendInsertClicked(const QString &) const;
    void sendRemoveClicked(const QString &) const;
    void sendSearchClicked(const QString &) const;

public slots:
    void comboChanged(int);
    void insertClicked();
    void removeClicked();
    void searchClicked();

private:
    QHBoxLayout *hlayout;
    QComboBox *combo;
    LineEdit *insertLine;
    LineEdit *removeLine;
    LineEdit *searchLine;
    QPushButton *insertButton;
    QPushButton *removeButton;
    QPushButton *searchButton;
};

/*
 * LineEdit
 */
class LineEdit : public QLineEdit {
    Q_OBJECT
public:
    LineEdit();
    LineEdit(QWidget *);
    ~LineEdit();
protected:
    void mousePressEvent(QMouseEvent *);
    void focusOutEvent(QFocusEvent *);
};

#endif // UI_WINDOW_H
