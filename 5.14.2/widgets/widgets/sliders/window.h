#pragma once

#include <QWidget>
#include"slidersgroup.h"
#include<QStackedWidget>
#include<QComboBox>
#include<QGroupBox>
#include<QLabel>
#include<QSpinBox>
#include<QCheckBox>

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(QWidget *parent = nullptr);
	~Window();

	void createControls();
private:
	SlidersGroup* horizontalSliders;	//horizontal
	SlidersGroup* verticalSliders;		//vertical
	QStackedWidget* stackedWidget=nullptr;		//滑块组StackedWidget

	QGroupBox* controlsGroup = nullptr;			//控制组

	QLabel* minValLabel;
	QLabel* maxValLabel;
	QLabel* curValLabel;

	QSpinBox* minValSpin;
	QSpinBox* maxValSpin;
	QSpinBox* curValSpin;

	QCheckBox* invertedAppearance;
	QCheckBox* invertedKeyBindings;

	QComboBox* orientationCombo = nullptr;
};
