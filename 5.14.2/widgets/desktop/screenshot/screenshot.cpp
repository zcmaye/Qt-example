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
    //��ʾͼƬ��label
    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setAlignment(Qt::AlignCenter);

    //��ȡ��Ļ��С��������ʾͼƬ��label��С����һ��
    const QRect screenGeometry = screen()->geometry();
    screenshotLabel->setMinimumSize(screenGeometry.width() / 8, screenGeometry.height() / 8);

    //��label��ӽ���ֱ����
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(screenshotLabel);

    //����һ����Ͽ򣬲�����ʱ��΢���������Ͽ�
    QGroupBox* optGroupBox = new QGroupBox("Options",this);
    delaySpinBox = new QSpinBox(optGroupBox);
    delaySpinBox->setSuffix("s");
    delaySpinBox->setValue(2);
    delaySpinBox->setMaximum(60);

    //������ʱ��ͼʱ�Ƿ���ʾ�����򴰿ڵ�ѡ��ť
    hideThisWindowCheckBox = new QCheckBox("hide this window",optGroupBox);

    //1,void (QSpinBox::*pfun)(int) = &QSpinBox::valueChanged;
    connect(delaySpinBox, qOverload<const QString&>(&QSpinBox::valueChanged), this,&Screenshot::updateCheckBox);

    //����Ͽ򴴽����񲼾֣����Ѹ��������ӽ�����
    QGridLayout* optGroupBoxLayout = new QGridLayout(optGroupBox);
    optGroupBoxLayout->addWidget(new QLabel("Screenshot Delay:", optGroupBox), 0, 0);
    optGroupBoxLayout->addWidget(delaySpinBox,0,1);
    optGroupBoxLayout->addWidget(hideThisWindowCheckBox, 1, 0, 1,2);
    //����Ͽ��������ֱ����
    mainLayout->addWidget(optGroupBox);

    //����ˮƽ����
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
    quitBtn->setShortcut(QKeySequence("Ctrl+Q"));   //����ť�󶨿�ݼ�

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
    //���ڴ�С�����仯ʱ������ͼƬ��С
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
    if (screenshotLabel->pixmap())  //���label��ͼƬ�͸���
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
    //��ȡ����Ļ
    QScreen* screen = QApplication::primaryScreen();
    if (!screen)
        return;
    //��ȡ��Ļ��ͼ
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
    //��ȡ�û�ͼƬ�ļ�Ŀ¼ "C:/Users/Maye/Pictures"
    QString picturesPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (picturesPath.isEmpty())
    {
        picturesPath = QDir::currentPath();
    }
    picturesPath += "/untitled";//untitled Ĭ���ļ���

    QFileDialog filedialog(this, "Save as", picturesPath);
    filedialog.setAcceptMode(QFileDialog::AcceptSave);  //���öԻ������ģʽ
    filedialog.setFileMode(QFileDialog::FileMode::AnyFile);

    //��ȡ֧�ֱ����ͼƬģʽ
    QStringList mimeTypes;
    QByteArrayList baMimeTypes =  QImageWriter::supportedMimeTypes();
    for (QByteArray& bf : baMimeTypes)
    {
        mimeTypes.append(bf);
        qDebug() << bf;
    }
    filedialog.setMimeTypeFilters(mimeTypes);           //�������пɱ��������
    filedialog.selectMimeTypeFilter("image/png");       //����Ĭ��ѡ�������
    filedialog.setDefaultSuffix(".png");                //����Ĭ�Ϻ�׺
    if (filedialog.exec() != QDialog::Accepted)
    {
        return;
    }
    //��ȡѡ��ı����ļ�Ŀ¼
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
    newScreenBtn->setDisabled(true);        //���ý�ͼ��ť
    QTimer::singleShot(delaySpinBox->value() * 1000, this, &Screenshot::shootScreen);
}
