#include <QApplication>
#include"buttontester.h"
#include<QPushButton>
#include<QVBoxLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ButtonTester *testArea = new ButtonTester;
    testArea->setMinimumSize(500, 350);
    testArea->setContextMenuPolicy(Qt::NoContextMenu);
    testArea->setTextInteractionFlags(Qt::TextSelectableByMouse);
    testArea->setText("To test your mouse with Qt, press buttons in this area.\nYou may also scroll or tilt your mouse wheel.");
    QPushButton* quitBtn = new QPushButton("Quit");
    
    QObject::connect(quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(testArea);
    layout->addWidget(quitBtn);
    
    QWidget w;
    w.setLayout(layout);
    w.setWindowTitle("Mouse Button Tester");
    w.show();

    return a.exec();
}
