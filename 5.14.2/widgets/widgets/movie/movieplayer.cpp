#include "movieplayer.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QStyle>
#include<QFileDialog>
#include<QApplication>
#include<QDebug>

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
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    resize(640,480);
}

MoviePlayer::~MoviePlayer()
{

}

void MoviePlayer::createContorls()
{
    fitCheckBox = new QCheckBox("Fit to Window");
    connect(fitCheckBox,&QCheckBox::clicked,this,[=](bool checked)
    {
        movieLabel->setScaledContents(checked);
    });

    frameLabel =new QLabel("current frame");
    frameSlider = new QSlider(Qt::Horizontal);
    frameSlider->setTickPosition(QSlider::TickPosition::TicksBelow);    //画刻度
    frameSlider->setTickInterval(5);        //刻度间距
    connect(frameSlider,&QSlider::valueChanged,movie,&QMovie::jumpToFrame);

    speedLabel = new QLabel("Speed:");
    speedSpinBox = new QSpinBox;
    speedSpinBox->setRange(1,200);
    speedSpinBox->setValue(100);
    speedSpinBox->setSuffix("%");
    connect(speedSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),movie,&QMovie::setSpeed);

    controlsLayout = new QGridLayout;
    controlsLayout->addWidget(fitCheckBox,0,0);
    controlsLayout->addWidget(frameLabel,1,0);
    controlsLayout->addWidget(frameSlider,1,1,1,2);
    controlsLayout->addWidget(speedLabel,2,0);
    controlsLayout->addWidget(speedSpinBox,2,1,1,1);
}

void MoviePlayer::createButtons()
{
    QSize iconSize(36,36);
    QString iconPath="F:/gitHub/Qt-example/5.14.2/widgets/desktop/systray/images/heart.png";
    openBtn = new QToolButton(this);
    openBtn->setIcon(style()->standardIcon(QStyle::StandardPixmap::SP_DesktopIcon));
    openBtn->setIconSize(iconSize);
    openBtn->setToolTip("Open File");
    connect(openBtn,&QToolButton::clicked,this,&MoviePlayer::open);

    playBtn = new QToolButton;
    playBtn->setIcon(style()->standardIcon(QStyle::StandardPixmap::SP_MediaPlay));
    playBtn->setIconSize(iconSize);
    connect(playBtn,&QToolButton::clicked,movie,&QMovie::start);

    pauseBtn = new QToolButton;
    pauseBtn->setIcon(style()->standardIcon(QStyle::StandardPixmap::SP_MediaPause));
    pauseBtn->setIconSize(iconSize);
    connect(pauseBtn,&QToolButton::clicked,movie,&QMovie::setPaused);

    stopBtn= new QToolButton;
    stopBtn->setIcon(style()->standardIcon(QStyle::StandardPixmap::SP_MediaStop));
    stopBtn->setIconSize(iconSize);
    connect(stopBtn,&QToolButton::clicked,movie,&QMovie::stop);

    quitBtn = new QToolButton;
    quitBtn->setIcon(style()->standardIcon(QStyle::StandardPixmap::SP_DialogCloseButton));
    quitBtn->setIconSize(iconSize);
    connect(quitBtn,&QToolButton::clicked,qApp,&QApplication::quit);




    btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(openBtn);
    btnLayout->addWidget(playBtn);
    btnLayout->addWidget(pauseBtn);
    btnLayout->addWidget(stopBtn);
    btnLayout->addWidget(quitBtn);
    btnLayout->addStretch();

}

void MoviePlayer::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open Movie","./","GIF(*.gif)");
    if(!fileName.isEmpty())
    {
        curMoviePath = fileName;
        movie->stop();
        movieLabel->setMovie(movie);
        movie->setFileName(fileName);
        movie->start();
        frameSlider->setRange(0,movie->frameCount());   //设置滑块范围
        connect(movie,&QMovie::frameChanged,frameSlider,&QSlider::setValue);

    }
}

