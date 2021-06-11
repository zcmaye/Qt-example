#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QAction>
#include<QAction>
#include<QLabel>
#include<QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createMenu();
private:
    QLabel *infoLabel;  //中间信息显示

    QMenu *file;
    QMenu *edit;
    QMenu *help;
};
#endif // MAINWINDOW_H
