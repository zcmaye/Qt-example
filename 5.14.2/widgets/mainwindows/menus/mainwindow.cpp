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
    file = menuBar()->addMenu("文件(&F)");
    file->addAction(newAct);
    file->addAction(openAct);
    file->addAction(saveAct);
    file->addAction(printAct);
    file->addSeparator();
    file->addAction(exitAct);

    edit = menuBar()->addMenu("编辑(&E)");
    edit->addAction(undoAct);
    edit->addAction(redoAct);
    edit->addAction(cutAct);
    edit->addAction(copyAct);
    edit->addAction(pasteAct);
    edit->addSeparator();

    formatMenu = new QMenu("Format");
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText("Alignment");
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(lineSpaceAct);
    formatMenu->addAction(paragraphSpaceAct);

    edit->addMenu(formatMenu);


    help = menuBar()->addMenu("帮助(&H)");
    help->addAction(aboutAct);
    help->addAction(aboutQtAct);
}

void MainWindow::createActions()
{
    newAct = new QAction("&New");
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip("Create New File");
    connect(newAct,&QAction::toggled,this,&MainWindow::newFile);

    openAct = new QAction("&Open");
    openAct->setShortcuts();

    saveAct = new QAction("&Save");
    printAct = new QAction("&Print");
    exitAct = new QAction("&Exit");

    undoAct = new QAction("Undo");
    redoAct = new QAction("Redo");
    cutAct = new QAction("Cut");
    copyAct = new QAction("Copy");
    pasteAct = new QAction("Paste");


    boldAct = new QAction("Bold");
    italicAct = new QAction("Italic");
    leftAlignAct = new QAction("Left Alignment");
    rightAlignAct = new QAction("Right Alignment");
    justifyAct = new QAction("Justify");
    centerAct = new QAction("Center Alignment");
    lineSpaceAct = new QAction("set Line Spacing");
    paragraphSpaceAct = new QAction("set Paragraph Spacing");

    aboutAct = new QAction("About");
    aboutQtAct = new QAction("AboutQt");
}

void MainWindow::newFile()
{

}
void MainWindow::open()
{

}
void MainWindow::save()
{

}
void MainWindow::print()
{

}
void MainWindow::undo()
{

}
void MainWindow::redo()
{

}
void MainWindow::cut()
{

}
void MainWindow::copy()
{

}
void MainWindow::paste()
{

}
void MainWindow::bold()
{

}
void MainWindow::italic()
{

}
void MainWindow::leftAlign()
{

}
void MainWindow::rightAlign()
{

}
void MainWindow::justify()
{

}
void MainWindow::center()
{

}
void MainWindow::setLineSpacing()
{

}
void MainWindow::setParagraphSpacing()
{

}
void MainWindow::about()
{

}
void MainWindow::aboutQt()
{

}
