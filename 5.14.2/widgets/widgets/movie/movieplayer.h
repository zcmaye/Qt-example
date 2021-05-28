#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMovie>
#include<QLabel>
#include<QCheckBox>
#include<QSlider>
#include<QGridLayout>
#include<QSpinBox>
#include<QToolButton>
#include<QHBoxLayout>

class MoviePlayer : public QWidget
{
    Q_OBJECT

public:
    MoviePlayer(QWidget *parent = nullptr);
    ~MoviePlayer();

    void createContorls();
    void createButtons();
private slots:
    void open();
private:
    QLabel *movieLabel =nullptr;    //动画显示label
    QMovie *movie = nullptr;        //动画
    QString curMoviePath;           //当前动画路径

    QCheckBox *fitCheckBox;
    QLabel    *frameLabel;
    QSlider   *frameSlider;
    QLabel    *speedLabel;
    QSpinBox  *speedSpinBox;
    QGridLayout * controlsLayout;

    QToolButton *openBtn;
    QToolButton *playBtn;
    QToolButton *pauseBtn;
    QToolButton *stopBtn;
    QToolButton *quitBtn;
    QHBoxLayout *btnLayout;

};
#endif // WIDGET_H
