#include "slidersgroup.h"
#include<QSlider>
#include<QScrollBar>
#include<QDial>
#include<QBoxLayout>

SlidersGroup::SlidersGroup(Qt::Orientation orientation, const QString& title, QWidget* parent)
	: QGroupBox(title,parent)
{
	slider = new QSlider(orientation, this);
	slider->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	slider->setTickPosition(QSlider::TickPosition::TicksBothSides);
	slider->setTickInterval(10);	//刻度间隔
	slider->setSingleStep(1);		//拉动滑块的步长
	slider->setPageStep(2);			//点击槽时的步长


	scrollBar = new QScrollBar(orientation, this);
	scrollBar->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

	dial = new QDial(this);
	dial->setFocus();
	
	//滑动其中一个其他两个都跟着改变
	connect(slider, &QSlider::valueChanged, scrollBar, &QScrollBar::setValue);
	connect(scrollBar, &QScrollBar::valueChanged, dial, &QDial::setValue);
	connect(dial, &QDial::valueChanged, slider, &QSlider::setValue);
	//发送值改变信号
	connect(dial, &QDial::valueChanged, this,&SlidersGroup::valueChange);


	QBoxLayout::Direction direction;	//布局方向
	direction = orientation == Qt::Horizontal ? 
		QBoxLayout::Direction::TopToBottom :
		QBoxLayout::Direction::LeftToRight;
	QBoxLayout* slidersLayout = new QBoxLayout(direction);
	slidersLayout->addWidget(slider);
	slidersLayout->addWidget(scrollBar);
	slidersLayout->addWidget(dial);
	this->setLayout(slidersLayout);

}
SlidersGroup::~SlidersGroup()
{

}

void SlidersGroup::setValue(int val)
{
	slider->setValue(val);
}

void SlidersGroup::setMinimum(int val)
{
	this->slider->setMinimum(val);
	this->scrollBar->setMinimum(val);
	this->dial->setMaximum(val);
}

void SlidersGroup::setMaximum(int val)
{
	this->slider->setMaximum(val);
	this->scrollBar->setMaximum(val);
	this->dial->setMaximum(val);
}

void SlidersGroup::invertAppearance(bool invert)
{
	slider->setInvertedAppearance(invert);
	scrollBar->setInvertedAppearance(invert);
	dial->setInvertedAppearance(invert);
}

void SlidersGroup::invertKeyBindings(bool invert)
{
	slider->setInvertedControls(invert);
	scrollBar->setInvertedControls(invert);
	dial->setInvertedControls(invert);
}
