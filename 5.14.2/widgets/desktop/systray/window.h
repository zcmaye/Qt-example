#ifndef WINDOW_H
#define WINDOW_H
#include<QDialog>
#include<QGroupBox>
#include<QLabel>
#include<QCheckBox>
#include<QComboBox>
#include<QHlay>
class Window :
    public QDialog
{
public:
    Window(QWidget* parent = nullptr);
    void createIconGroupBox();
private:
    //tray Icon
    QGroupBox* iconGroupBox = nullptr;
    QLabel* iconLabel = nullptr;
    QComboBox* iconComboBox = nullptr;
    QCheckBox* showIconCheckBox = nullptr;


};

#endif // !WINDOW_H



