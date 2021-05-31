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

	scrollBar = new QScrollBar(orientation, this);
	scrollBar->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

	dial = new QDial(this);
	dial->setFocus();




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
