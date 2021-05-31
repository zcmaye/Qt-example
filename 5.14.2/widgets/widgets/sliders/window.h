#pragma once

#include <QWidget>
#include"slidersgroup.h"

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(QWidget *parent = nullptr);
	~Window();

	void createControls();
private:
	SlidersGroup* horizontalSliders;
};
