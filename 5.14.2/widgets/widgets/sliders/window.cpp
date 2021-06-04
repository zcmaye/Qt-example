#include "window.h"
#include<QHBoxLayout>
#include<QGridLayout>
#include<QDebug>
Window::Window(QWidget *parent)
	: QWidget(parent)
{
	//创建两个不同方向的sliderGroup
	horizontalSliders = new SlidersGroup(Qt::Orientation::Horizontal, "Horizontal", this);
	verticalSliders = new SlidersGroup(Qt::Orientation::Vertical, "Vertical", this);
	//添加到堆栈窗口
	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget(horizontalSliders);
	stackedWidget->addWidget(verticalSliders);

	createControls();

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(controlsGroup);
	layout->addWidget(stackedWidget);
	
	this->setLayout(layout);

}

Window::~Window()
{

}

void Window::createControls()
{
	controlsGroup = new QGroupBox("controls group");

	minValLabel = new QLabel("Minimum value:");
	maxValLabel = new QLabel("Maximum value:");
	curValLabel = new QLabel("Current value:");

	minValSpin = new QSpinBox;
	maxValSpin = new QSpinBox;
	curValSpin = new QSpinBox;


	invertedAppearance = new QCheckBox("Inverted appearance");
	invertedKeyBindings = new QCheckBox("Inverted key bindings");


	orientationCombo = new QComboBox;
	orientationCombo->addItem("Horizontal slider-like widgets");
	orientationCombo->addItem("vertical slider-line widgets");
	
	connect(orientationCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), stackedWidget, &QStackedWidget::setCurrentIndex);
	connect(minValSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int val)
		{
			horizontalSliders->setMinimum(val);
			verticalSliders->setMinimum(val);
		});
	connect(maxValSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int val)
		{
			horizontalSliders->setMaximum(val);
			verticalSliders->setMaximum(val);
		});
	connect(horizontalSliders, &SlidersGroup::valueChange, curValSpin, &QSpinBox::setValue);
	connect(verticalSliders, &SlidersGroup::valueChange, curValSpin, &QSpinBox::setValue);
	connect(invertedAppearance, &QCheckBox::stateChanged, this, [=](bool isCheck) 
		{
			horizontalSliders->invertAppearance(isCheck);
			verticalSliders->invertAppearance(isCheck);
		});
	connect(invertedKeyBindings, &QCheckBox::stateChanged, this, [=](bool isCheck)
		{
			horizontalSliders->invertKeyBindings(isCheck);
			verticalSliders->invertKeyBindings(isCheck);
		});

	minValSpin->setValue(0);
	maxValSpin->setValue(20);
	curValSpin->setValue(5);



	QGridLayout* layout = new QGridLayout;
	layout->addWidget(minValLabel, 0, 0);
	layout->addWidget(minValSpin, 0, 1);
	layout->addWidget(invertedAppearance,0,2);
	layout->addWidget(maxValLabel, 1, 0);
	layout->addWidget(maxValSpin, 1, 1);
	layout->addWidget(invertedKeyBindings);
	layout->addWidget(curValLabel, 2, 0);
	layout->addWidget(curValSpin, 2, 1);
	layout->addWidget(orientationCombo, 3, 0, 1, 3);
	controlsGroup->setLayout(layout);

}
