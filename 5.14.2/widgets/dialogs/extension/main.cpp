#include<QApplication>
#include"finddialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindDialog w;
    w.show();

    return a.exec();
}
