#include "window.h"
#include<QVBoxLayout>

Window::Window(QWidget* parent):QDialog(parent)
{
	resize(640, 480);
	createIconGroupBox();
	createMessageGroupBox();

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(iconGroupBox);
	mainLayout->addWidget(messageGroupBox);
	this->setLayout(mainLayout);

}

void Window::createIconGroupBox()
{
	iconGroupBox = new QGroupBox("Tray Icon",this);
	iconLabel = new QLabel("Icon:");
	iconComboBox = new QComboBox;
	showIconCheckBox = new QCheckBox("show icon");
	showIconCheckBox->setChecked(true);

	iconComboBox->addItem(QIcon(":/images/bad.png"), "Bad");
	iconComboBox->addItem(QIcon(":/images/heart.png"), "Heart");
	iconComboBox->addItem(QIcon(":/images/trash.png"), "Trash");


	QHBoxLayout* groupBoxlayout = new QHBoxLayout;
	groupBoxlayout->addWidget(iconLabel);
	groupBoxlayout->addWidget(iconComboBox);
	groupBoxlayout->addStretch();
	groupBoxlayout->addWidget(showIconCheckBox);

	iconGroupBox->setLayout(groupBoxlayout);
}

void Window::createMessageGroupBox()
{
	messageGroupBox = new QGroupBox("Balloon Message",this);
	typeLabel = new QLabel("Type:");
	typeComboBox = new QComboBox;
	typeComboBox->addItem(style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxInformation),
		"Information", QSystemTrayIcon::Information);
	typeComboBox->addItem(style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxWarning),
		"Warning", QSystemTrayIcon::Warning);
	typeComboBox->addItem(style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxCritical),
		"Critical", QSystemTrayIcon::Critical);

	durationLabel = new QLabel("Duration:");
	durationSpinBox = new QSpinBox;
	durationSpinBox->setRange(0, 60);
	durationSpinBox->setSuffix(" s");
	durationWarningLabel = new QLabel("(some systems might ignore this hint)");

	titleLabel = new QLabel("Title:");
	titleEdit = new QLineEdit("Cannot connect to network");

	bodyLabel = new QLabel("Body:");
	bodyEdit = new QTextEdit("what 不相信我。 说实话，我也不知道。  单击此气球获取详细信息。");
	bodyEdit->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);

	showMessageBtn = new QPushButton("Show Message");
	showMessageBtn->setDefault(true);


	messageLayout = new QGridLayout;
	messageLayout->addWidget(typeLabel, 0, 0);
	messageLayout->addWidget(typeComboBox, 0, 1, 1, 2);
	messageLayout->addWidget(durationLabel, 1, 0);
	messageLayout->addWidget(durationSpinBox, 1, 1);
	messageLayout->addWidget(durationWarningLabel, 1, 2, 1, 3);
	messageLayout->addWidget(titleLabel, 2, 0);
	messageLayout->addWidget(titleEdit, 2, 1, 1, 4);
	messageLayout->addWidget(bodyLabel, 3, 0);
	messageLayout->addWidget(bodyEdit, 3, 1, 2, 4);
	messageLayout->addWidget(showMessageBtn, 5, 4);
	messageLayout->setColumnStretch(3, 1);
	messageLayout->setRowStretch(4, 1);

	messageGroupBox->setLayout(messageLayout);

}
