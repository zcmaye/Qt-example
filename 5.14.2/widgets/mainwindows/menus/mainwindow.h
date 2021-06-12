#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QAction>
#include<QLabel>
#include<QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createMenus();
    void createActions();

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
    QAction *cutAct;
    QAction *copyAct;
        //Format
    QMenu   *formatMenu;
    QAction *boldAct;       //粗体
    QAction *italicAct;     //斜体
    QAction *leftAlignAct; //左对齐
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *lineSpaceAct;      //行间隔
    QAction *paragraphSpaceAct; //段落间隔

    //Help
    QAction *about;
    QAction *aboutQt;



};
#endif // MAINWINDOW_H
