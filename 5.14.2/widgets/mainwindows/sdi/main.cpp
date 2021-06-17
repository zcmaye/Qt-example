#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(sdi);
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("SDI Example");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCoreApplication::setOrganizationName("MayeQtProject");



    MainWindow w;
    w.show();
    return a.exec();
}
