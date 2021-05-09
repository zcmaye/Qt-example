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

    //更新label中的图片
    void updateScreenshootLabel();
public slots:
    void updateCheckBox();
    void shootScreen();         //截图
    void saveScreenshot();      //保存截图
    void newScreenshot();
private:
    QLabel* screenshotLabel = nullptr;
    QSpinBox* delaySpinBox = nullptr;
    QCheckBox* hideThisWindowCheckBox = nullptr;

    QPushButton* newScreenBtn = nullptr;
    QPixmap originalPixmap;
};
