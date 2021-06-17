#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QAction>
#include<QLabel>
#include<QMenu>
#include<QFont>
#include<QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createMenus();
    void createActions();

private slots:
    void newFile();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();
    void aboutQt();

private:
    QLabel *infoLabel;  //中间信息显示

    QMenu *file;
    QMenu *edit;
    QMenu *help;
    //File
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    //Edit
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;    //剪切
    QAction *copyAct;   //复制
    QAction *pasteAct;  //粘贴
        //Format
    QMenu   *formatMenu;
    QAction *boldAct;       //粗体
    QAction *italicAct;     //斜体
    QAction *leftAlignAct;  //左对齐
    QAction *rightAlignAct; //右对齐
    QAction *justifyAct;    //两端对齐
    QAction *centerAct;     //居中对齐
    QAction *lineSpaceAct;      //行间隔
    QAction *paragraphSpaceAct; //段落间隔

    //Help
    QAction *aboutAct;
    QAction *aboutQtAct;
};
#endif // MAINWINDOW_H
