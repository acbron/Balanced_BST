#include "ui_window.h"

const int BASE_HEIGHT = 700;
const int BASE_WIDTH = 1200;
const int MAX_TOOLBAR_HEIGHT = 42;
const int MAX_LINE_EDIT_LENGTH = 128;
const int MAX_LINE_INPUT_LENGTH = 4;
const int MIN_LINE_INPUT_LENGTH = 1;

MainWindow::MainWindow()
{
    setMinimumSize(BASE_WIDTH, BASE_HEIGHT);
    setWindowTitle("Binary Search Tree Visualization");

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
    int width = this->width();

    statusBar()->setMinimumSize(width, 100);
    statusBar()->setStyleSheet("background:#404040");
    status_bar_msg = new QLabel(this);
    QFont font;
    font.setWeight(20);
    font.setPixelSize(20);
    status_bar_msg->setFont(font);
    status_bar_msg->setText("Status bar");
    status_bar_msg->setStyleSheet("background:white");
    status_bar_msg->setMinimumSize(width - 6, 92);
    status_bar_msg->setAlignment(Qt::AlignLeft);

    statusBar()->addWidget(status_bar_msg);
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

    this->vlayout->addWidget(bst);
    connect(toolbar, SIGNAL(sendInsertClicked(const QString &)), bst, SLOT(RcvInsertClicked(const QString &)));
    connect(toolbar, SIGNAL(sendRemoveClicked(const QString &)), bst, SLOT(RcvDeleteClicked(const QString &)));
    connect(toolbar, SIGNAL(sendSearchClicked(const QString &)), bst, SLOT(RcvSearchClicked(const QString &)));
    connect(bst, SIGNAL(insertStatusMsg(QString,int,bool)), this, SLOT(updateStatusBar(QString,int,bool)));
    connect(bst, SIGNAL(deleteStatusMsg(QString,int,bool)), this, SLOT(updateStatusBar(QString,int,bool)));
    connect(bst, SIGNAL(searchStatusMsg(QString,int,bool)), this, SLOT(updateStatusBar(QString,int,bool)));
}

void MainWindow::updateStatusBar(const QString &str, int flag, bool isSuccess)
{
    QString msg;
    if (flag == 0) {
        msg = "insert " + str + " successfully.";
    } else if (flag == 1) {
        if (isSuccess)
            msg = "delete " + str + " successfully.";
        else
            msg = str + " can not be found, deletion failed.";
    } else {
        if (isSuccess)
            msg = str + " was found.";
        else
            msg = str + " can not be found.";
    }
    this->status_bar_msg->setText(msg);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    int width = this->width();
    status_bar_msg->resize(width - 6, 92);
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
    insertLine = new LineEdit(this);
    removeLine = new LineEdit(this);
    searchLine = new LineEdit(this);

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
    removeButton = new QPushButton(tr("delete"), this);
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

    QPalette p(palette());
    p.setBrush(QPalette::Background, QColor("#404040"));
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
    insertLine->clear();
    emit sendInsertClicked(tmp);
}

void ToolBar::removeClicked()
{
    QString tmp = removeLine->text();
    removeLine->clear();
    emit sendRemoveClicked(tmp);
}

void ToolBar::searchClicked()
{
    QString tmp = searchLine->text();
    searchLine->clear();
    emit sendSearchClicked(tmp);
}

/*
 * LineEdit
 */
LineEdit::LineEdit() : QLineEdit()
{

}

LineEdit::LineEdit(QWidget *p) : QLineEdit(p)
{
        setParent(p);
}

LineEdit::~LineEdit()
{

}

void LineEdit::mousePressEvent(QMouseEvent *)
{
        setCursorPosition(0);
        setPlaceholderText("");
}

void LineEdit::focusOutEvent(QFocusEvent *e)
{
        QLineEdit::focusOutEvent(e);
        setPlaceholderText("input...");
}
