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
signals:
	void valueChange(int value);
public slots:
	void setValue(int val);
	void setMinimum(int val);
	void setMaximum(int val);
	void invertAppearance(bool invert);		//倒转最大值和最小值的位置
	void invertKeyBindings(bool invert);	//倒转控制方向（按键盘上的上下键 或者 page Up/page Down）

private:
	QSlider* slider;
	QScrollBar* scrollBar;
	QDial* dial;
};
