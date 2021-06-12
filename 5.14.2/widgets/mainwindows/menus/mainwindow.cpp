#include "mainwindow.h"
#include<QVBoxLayout>
#include<QMenuBar>
#include<QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    createActions();
    createMenus();

    infoLabel = new QLabel("<i>Choose a menu option, or right-click to "
                           "invoke a context menu</i>");
    infoLabel->setFrameStyle(QFrame::Shape::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);   //设置布局边距自己的边距(布局与窗口)
    layout->setContentsMargins(5,5,5,5);//设置布局四个方向的边距(布局与元素)

    layout->addStretch();
    layout->addWidget(infoLabel);
    layout->addStretch();
    widget->setLayout(layout);

    statusBar()->showMessage("hello");

}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenus()
{
    file = menuBar()->addMenu("文件");
    file->addAction(newAct);
    file->addAction(openAct);
    file->addAction(saveAct);
    file->addAction(printAct);
    file->addAction(exitAct);

    edit = menuBar()->addMenu("编辑");
    help = menuBar()->addMenu("帮助");
}

void MainWindow::createActions()
{
    newAct = new QAction("&New");
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip("Create New File");

    openAct = new QAction("&Open");
    saveAct = new QAction("&Save");
    printAct = new QAction("&Print");
    exitAct = new QAction("&Exit");
}
