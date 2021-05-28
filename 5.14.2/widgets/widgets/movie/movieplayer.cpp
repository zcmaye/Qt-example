#include "movieplayer.h"
#include<QVBoxLayout>
#include<QStyle>
#include<QFileDialog>

MoviePlayer::MoviePlayer(QWidget *parent)
    : QWidget(parent)
{
    movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);

    movieLabel = new QLabel("No movie loaded",this);
    movieLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);  //暗黑模式
    movieLabel->setAutoFillBackground(true);        //自动填充背景

    curMoviePath  = "movies";

    createContorls();
    createButtons();

    QVBoxLayout *mainLayout = new  QVBoxLayout(this);
    mainLayout ->addWidget(movieLabel);
    mainLayout->addLayout(controlsLayout);
    setLayout(mainLayout);

    resize(640,480);
}

MoviePlayer::~MoviePlayer()
{

}

void MoviePlayer::createContorls()
{
    fitCheckBox = new QCheckBox("Fit to Window");

    frameLabel =new QLabel("current frame");
    frameSlider = new QSlider(Qt::Horizontal);
    frameSlider->setTickPosition(QSlider::TickPosition::TicksBelow);    //画刻度
    frameSlider->setTickInterval(5);        //刻度间距

    speedLabel = new QLabel("Speed:");
    speedSpinBox = new QSpinBox;
    speedSpinBox->setRange(1,200);
    speedSpinBox->setValue(100);
    speedSpinBox->setSuffix("%");

    controlsLayout = new QGridLayout;
    controlsLayout->addWidget(fitCheckBox,0,0);
    controlsLayout->addWidget(frameLabel,1,0);
    controlsLayout->addWidget(frameSlider,1,1,1,2);
    controlsLayout->addWidget(speedLabel,2,0);
    controlsLayout->addWidget(speedSpinBox,2,1,1,1);
}

void MoviePlayer::createButtons()
{
    QString iconPath="F:/gitHub/Qt-example/5.14.2/widgets/desktop/systray/images/heart.png";
    openBtn = new QToolButton(this);
    openBtn->setIcon(style()->standardIcon(QStyle::StandardPixmap::SP_DesktopIcon));
    openBtn->setIconSize(QSize(36,36));
    openBtn->setToolTip("Open File");
    connect(openBtn,&QToolButton::clicked,this,&MoviePlayer::open);

}

void MoviePlayer::open()
{
    QFileDialog::getOpenFileName();
}

