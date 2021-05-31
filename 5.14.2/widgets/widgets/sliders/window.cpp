#include "window.h"

Window::Window(QWidget *parent)
	: QWidget(parent)
{
	horizontalSliders = new SlidersGroup(Qt::Orientation::Horizontal, "HelloWorld", this);;
}

Window::~Window()
{

}

void Window::createControls()
{

}
