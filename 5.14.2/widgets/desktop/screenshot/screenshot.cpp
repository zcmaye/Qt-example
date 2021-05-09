#include "screenshot.h"
#include<QScreen>
#include<QLayout>
#include<qdebug.h>
#include<QGroupBox>

#include<QTimer>
#include<QApplication>
#include<QStandardPaths>
#include<QDir>
#include<QFileDialog>
#include<QImageWriter>
#include<QMessageBox>

Screenshot::Screenshot(QWidget *parent)
    : QWidget(parent)
    ,screenshotLabel(new QLabel(this))
{
    //显示图片的label
    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setAlignment(Qt::AlignCenter);

    //获取屏幕大小，并把显示图片的label大小设置一下
    const QRect screenGeometry = screen()->geometry();
    screenshotLabel->setMinimumSize(screenGeometry.width() / 8, screenGeometry.height() / 8);

    //把label添加进垂直布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(screenshotLabel);

    //创建一个组合框，并把延时的微调框加入组合框
    QGroupBox* optGroupBox = new QGroupBox("Options",this);
    delaySpinBox = new QSpinBox(optGroupBox);
    delaySpinBox->setSuffix("s");
    delaySpinBox->setValue(2);
    delaySpinBox->setMaximum(60);

    //创建延时截图时是否显示本程序窗口单选按钮
    hideThisWindowCheckBox = new QCheckBox("hide this window",optGroupBox);

    //1,void (QSpinBox::*pfun)(int) = &QSpinBox::valueChanged;
    connect(delaySpinBox, qOverload<const QString&>(&QSpinBox::valueChanged), this,&Screenshot::updateCheckBox);

    //给组合框创建网格布局，并把各个组件添加进布局
    QGridLayout* optGroupBoxLayout = new QGridLayout(optGroupBox);
    optGroupBoxLayout->addWidget(new QLabel("Screenshot Delay:", optGroupBox), 0, 0);
    optGroupBoxLayout->addWidget(delaySpinBox,0,1);
    optGroupBoxLayout->addWidget(hideThisWindowCheckBox, 1, 0, 1,2);
    //把组合框加入主垂直布局
    mainLayout->addWidget(optGroupBox);

    //创建水平布局
    QHBoxLayout* btnLayout = new QHBoxLayout;
    newScreenBtn = new QPushButton("New screenshot",this);
    btnLayout->addWidget(newScreenBtn);
    connect(newScreenBtn, &QPushButton::clicked, this, &Screenshot::newScreenshot);

    auto saveBtn = new QPushButton("save screenshot", this);
    btnLayout->addWidget(saveBtn);
    connect(saveBtn, &QPushButton::clicked, this, &Screenshot::saveScreenshot);

    auto quitBtn = new QPushButton("Quit", this);
    btnLayout->addWidget(quitBtn);
    connect(quitBtn, &QPushButton::clicked, this, &Screenshot::close);
    quitBtn->setShortcut(QKeySequence("Ctrl+Q"));   //给按钮绑定快捷键

    btnLayout->addStretch();      
    mainLayout->addLayout(btnLayout);

    shootScreen();   
}

void Screenshot::updateCheckBox()
{
    if (delaySpinBox->value() == 0) {
        hideThisWindowCheckBox->setDisabled(true);
        hideThisWindowCheckBox->setChecked(false);
    }
    else {
        hideThisWindowCheckBox->setDisabled(false);
    }
}

void Screenshot::resizeEvent(QResizeEvent* ev)
{
    //窗口大小发生变化时，调整图片大小
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
    if (screenshotLabel->pixmap())  //如果label有图片就更新
    {
        updateScreenshootLabel();
    }
}

void Screenshot::updateScreenshootLabel()
{
    screenshotLabel->setPixmap(originalPixmap.scaled(screenshotLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
}

void Screenshot::shootScreen()
{
    //获取主屏幕
    QScreen* screen = QApplication::primaryScreen();
    if (!screen)
        return;
    //获取屏幕截图
    originalPixmap = screen->grabWindow(0);

    updateScreenshootLabel();

    newScreenBtn->setDisabled(false);
    if (hideThisWindowCheckBox->isChecked())
    {
        this->show();
    }      
}

void Screenshot::saveScreenshot()
{
    //获取用户图片文件目录 "C:/Users/Maye/Pictures"
    QString picturesPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (picturesPath.isEmpty())
    {
        picturesPath = QDir::currentPath();
    }
    picturesPath += "/untitled";//untitled 默认文件名

    QFileDialog filedialog(this, "Save as", picturesPath);
    filedialog.setAcceptMode(QFileDialog::AcceptSave);  //设置对话框访问模式
    filedialog.setFileMode(QFileDialog::FileMode::AnyFile);

    //获取支持保存的图片模式
    QStringList mimeTypes;
    QByteArrayList baMimeTypes =  QImageWriter::supportedMimeTypes();
    for (QByteArray& bf : baMimeTypes)
    {
        mimeTypes.append(bf);
        qDebug() << bf;
    }
    filedialog.setMimeTypeFilters(mimeTypes);           //设置所有可保存的类型
    filedialog.selectMimeTypeFilter("image/png");       //设置默认选择的类型
    filedialog.setDefaultSuffix(".png");                //设置默认后缀
    if (filedialog.exec() != QDialog::Accepted)
    {
        return;
    }
    //获取选择的保存文件目录
    QString fileName = filedialog.selectedFiles().first();
    if (!originalPixmap.save(fileName))
    {
        QMessageBox::warning(this, tr("Save Error"), tr("The image could not be saved to \"%1\".")
            .arg(QDir::toNativeSeparators(fileName)));
    }

}

void Screenshot::newScreenshot()
{
    if (hideThisWindowCheckBox->isChecked())
    {
        this->hide();
    }      
    newScreenBtn->setDisabled(true);        //禁用截图按钮
    QTimer::singleShot(delaySpinBox->value() * 1000, this, &Screenshot::shootScreen);
}
