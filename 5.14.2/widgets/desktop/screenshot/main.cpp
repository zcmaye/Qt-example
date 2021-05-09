#include "screenshot.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screenshot w;
    w.show();
    return a.exec();
}
