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

    statusBar()->showMessage("A context menu is available by right-clicking");
    setWindowTitle("Menus");
    setMinimumSize(160,160);
    resize(480,320);

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
    connect(newAct,&QAction::triggered,this,&MainWindow::newFile);

    openAct = new QAction("&Open");
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip("Open an existing file");
    connect(openAct,&QAction::triggered,this,&MainWindow::open);

    saveAct = new QAction("&Save");
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip("Save the document to disk");
    connect(saveAct,&QAction::triggered,this,&MainWindow::save);

    printAct = new QAction("&Print");
    printAct ->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip("Print the document");
    connect(printAct,&QAction::triggered,this,&MainWindow::print);

    exitAct = new QAction("&Exit");
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip("Exit the pplication");
    connect(exitAct,&QAction::triggered,this,&MainWindow::close);

    undoAct = new QAction("Undo");
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip("Undo the last operation");
    connect(undoAct,&QAction::triggered,this,&MainWindow::undo);

    redoAct = new QAction("Redo");
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip("Redo the last operation");
    connect(redoAct,&QAction::triggered,this,&MainWindow::redo);

    cutAct = new QAction("Cut");
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip("Cut the current selection's contents to the clipboard");
    connect(cutAct,&QAction::triggered,this,&MainWindow::cut);

    copyAct = new QAction("Copy");
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip("Copy thie current selection's contents to the clipboard");
    connect(copyAct,&QAction::triggered,this,&MainWindow::copy);

    pasteAct = new QAction("Paste");
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip("Paste thie clipboard's contents into the current selection");
    connect(pasteAct,&QAction::triggered,this,&MainWindow::paste);

    /*Edit/Format*/
    boldAct = new QAction("Bold");
    boldAct->setCheckable(true);
    boldAct->setShortcuts(QKeySequence::Bold);
    boldAct->setStatusTip("Make thie text bold");
    connect(boldAct,&QAction::triggered,this,&MainWindow::bold);

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);


    italicAct = new QAction("Italic");
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    italicAct->setStatusTip(tr("Make the text italic"));
    connect(italicAct, &QAction::triggered, this, &MainWindow::italic);
    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    /*AlignMent*/
    leftAlignAct = new QAction("Left Alignment");
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    connect(leftAlignAct, &QAction::triggered, this, &MainWindow::leftAlign);

    rightAlignAct = new QAction("Right Alignment");
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    connect(rightAlignAct, &QAction::triggered, this, &MainWindow::rightAlign);

    justifyAct = new QAction("Justify");
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    justifyAct->setStatusTip(tr("Justify the selected text"));
    connect(justifyAct, &QAction::triggered, this, &MainWindow::justify);

    centerAct = new QAction("Center Alignment");
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    connect(centerAct, &QAction::triggered, this, &MainWindow::center);

    lineSpaceAct = new QAction("set Line Spacing");
    lineSpaceAct->setStatusTip(tr("Change the gap between the lines of a "
                                       "paragraph"));
    connect(lineSpaceAct, &QAction::triggered, this, &MainWindow::setLineSpacing);

    paragraphSpaceAct = new QAction("set Paragraph Spacing");
    paragraphSpaceAct->setStatusTip(tr("Change the gap between paragraphs"));
    connect(paragraphSpaceAct, &QAction::triggered,
            this, &MainWindow::setParagraphSpacing);

    /*help*/
    aboutAct = new QAction("About");
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction("AboutQt");
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);
}

void MainWindow::newFile()
{
    infoLabel->setText("Invoked <b>File|New</b>");
}
void MainWindow::open()
{
      infoLabel->setText("Invoked <b>File|Open</b>");
}
void MainWindow::save()
{
      infoLabel->setText("Invoked <b>File|Save</b>");
}
void MainWindow::print()
{
      infoLabel->setText("Invoked <b>File|Print</b>");
}
void MainWindow::undo()
{
      infoLabel->setText("Invoked <b>Edit|undo</b>");
}
void MainWindow::redo()
{
      infoLabel->setText("Invoked <b>Edit|redo</b>");
}
void MainWindow::cut()
{
    infoLabel->setText("Invoked <b>Edit|Cut</b>");
}
void MainWindow::copy()
{
    infoLabel->setText("Invoked <b>Edit|Copy</b>");
}
void MainWindow::paste()
{
    infoLabel->setText("Invoked <b>Edit|Paste</b>");
}
void MainWindow::bold()
{
     infoLabel->setText("Invoked <b>Edit|Format|bold</b>");
}
void MainWindow::italic()
{
    infoLabel->setText("Invoked <b>Edit|Format|italic</b>");
}
void MainWindow::leftAlign()
{
    infoLabel->setText("Invoked <b>Edit|Format|LeftAlign</b>");
}
void MainWindow::rightAlign()
{
    infoLabel->setText("Invoked <b>Edit|Format|RightAlign</b>");
}
void MainWindow::justify()
{
    infoLabel->setText("Invoked <b>Edit|Format|Justify</b>");
}
void MainWindow::center()
{
    infoLabel->setText("Invoked <b>Edit|Format|Center</b>");
}
void MainWindow::setLineSpacing()
{
     infoLabel->setText("Invoked <b>Edit|Format|Set Line Spacing</b>");
}
void MainWindow::setParagraphSpacing()
{
     infoLabel->setText("Invoked <b>Edit|Format|Set Paragraph Spacing</b>");
}
void MainWindow::about()
{
     infoLabel->setText("Invoked <b>Help|about</b>");
}
void MainWindow::aboutQt()
{
    infoLabel->setText("Invoked <b>Help|aboutQt</b>");
}
