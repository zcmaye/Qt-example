#include "mainwindow.h"
#include<QVBoxLayout>
#include<QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    createMenu();

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



}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenu()
{
    file = menuBar()->addMenu("文件");
    edit = menuBar()->addMenu("编辑");
    help = menuBar()->addMenu("帮助");

}

