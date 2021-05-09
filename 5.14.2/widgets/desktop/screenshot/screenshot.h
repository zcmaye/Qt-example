#pragma once

#include <QtWidgets/QWidget>
#include<QLabel>
#include<QSpinBox>
#include<QCheckBox>
#include<QPushButton>
#include<QPixmap>
#include<QResizeEvent>

class Screenshot : public QWidget
{
    Q_OBJECT

public:
    Screenshot(QWidget *parent = Q_NULLPTR);

    void resizeEvent(QResizeEvent* ev) override;

    //����label�е�ͼƬ
    void updateScreenshootLabel();
public slots:
    void updateCheckBox();
    void shootScreen();         //��ͼ
    void saveScreenshot();      //�����ͼ
    void newScreenshot();
private:
    QLabel* screenshotLabel = nullptr;
    QSpinBox* delaySpinBox = nullptr;
    QCheckBox* hideThisWindowCheckBox = nullptr;

    QPushButton* newScreenBtn = nullptr;
    QPixmap originalPixmap;
};
