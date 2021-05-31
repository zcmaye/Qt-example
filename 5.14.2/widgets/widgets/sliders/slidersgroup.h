#pragma once

#include <QGroupBox>
#include<QBoxLayout>

class QSlider;
class QScrollBar;
class QDial;

class SlidersGroup : public QGroupBox
{
	Q_OBJECT

public:
	SlidersGroup(Qt::Orientation orientation, const QString& title = "Null", QWidget* parent = nullptr);
	~SlidersGroup();

private:
	QSlider* slider;
	QScrollBar* scrollBar;
	QDial* dial;
};
