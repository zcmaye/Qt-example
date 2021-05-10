#include "window.h"

Window::Window(QWidget* parent):QDialog(parent)
{
	createIconGroupBox();
}

void Window::createIconGroupBox()
{
	iconGroupBox = new QGroupBox("Tray Icon", this);
	iconLabel = new QLabel("Icon:");
	iconComboBox = new QComboBox;
	showIconCheckBox = new QCheckBox("show icon");

	
}
