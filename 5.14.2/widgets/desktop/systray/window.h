#ifndef WINDOW_H
#define WINDOW_H
#include<QDialog>
#include<QGroupBox>
#include<QLabel>
#include<QCheckBox>
#include<QComboBox>
#include<QHBoxLayout>
#include<QSpinBox>
#include<QGridLayout>
#include<QSystemTrayIcon>
#include<QLineEdit>
#include<QPushButton>
#include<QTextEdit>
#include<QMenu>
class Window :
    public QDialog
{
public:
    Window(QWidget* parent = nullptr);
    void createIconGroupBox();          
    void createMessageGroupBox();       
    void createTrayIcon();
public slots:
    void showMessage();
private:
    //tray Icon
    QGroupBox* iconGroupBox = nullptr;
    QLabel* iconLabel = nullptr;
    QComboBox* iconComboBox = nullptr;
    QCheckBox* showIconCheckBox = nullptr;

    //balloom message
    QGroupBox* messageGroupBox      = nullptr;
    QLabel* typeLabel               = nullptr;
    QComboBox* typeComboBox         = nullptr;
    QLabel* durationLabel           = nullptr;
    QSpinBox* durationSpinBox       = nullptr;
    QLabel* durationWarningLabel    = nullptr;
    QLabel* titleLabel              = nullptr;
    QLineEdit* titleEdit            = nullptr;
    QLabel* bodyLabel                = nullptr;
    QTextEdit* bodyEdit             = nullptr;
    QPushButton* showMessageBtn     = nullptr;
    QGridLayout* messageLayout      = nullptr;

    QSystemTrayIcon* trayIcon = nullptr;
    QMenu* trayIconMenu;
};

#endif // !WINDOW_H



