#include <QApplication>
#include"window.h"
#include<QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    qApp->setStyle(QStyleFactory::create("Fusion"));
    w.show();
    return a.exec();
}
