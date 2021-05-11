#include "window.h"
#include<QVBoxLayout>
#include<QDebug>
#include<QApplication>

Window::Window(QWidget* parent):QDialog(parent)
{
	resize(640, 480);
	createIconGroupBox();
	createMessageGroupBox();
	//为了对其下面的布局设置一下宽度
	iconLabel->setMinimumWidth(durationLabel->sizeHint().width());

	createTrayIcon();


	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(iconGroupBox);
	mainLayout->addWidget(messageGroupBox);
	this->setLayout(mainLayout);

	connect(showMessageBtn, &QPushButton::clicked, this, &Window::showMessage);
	//点击show icon单选按钮,设置是否显示系统托盘菜单
	connect(showIconCheckBox, &QPushButton::toggled, trayIcon, &QSystemTrayIcon::setVisible);
	//选择不同的iconCombobox切换程序图标和系统托盘图标
	connect(iconComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, [=](int index)
		{
			QIcon icon = iconComboBox->itemIcon(index);
			trayIcon->setIcon(icon);
			this->setWindowIcon(icon);
			trayIcon->setToolTip(iconComboBox->currentText());
		});
	//根据激活系统托盘的原因，进行不同的处理
	connect(trayIcon, &QSystemTrayIcon::activated, this, [=](QSystemTrayIcon::ActivationReason reason)
		{
			switch (reason)
			{
			case QSystemTrayIcon::Context:		//右击打开托盘上下文菜单时触发
				qDebug() << "helo1";
				break;
			case QSystemTrayIcon::DoubleClick:	//双击
			case QSystemTrayIcon::Trigger:		//单击
				iconComboBox->setCurrentIndex
				((iconComboBox->currentIndex() + 1) % iconComboBox->count());
				break;
			case QSystemTrayIcon::MiddleClick:	//中击
				showMessage();
				break;

			}
		});


}
void Window::showMessage()
{
	//显示消息框的时候,把系统托盘显示出来
	showIconCheckBox->setChecked(true);
	//获取当前typeComboBox的QSystemTrayIcon::MessageIcon的枚举值
	int selectedIcon = typeComboBox->currentData().toInt();
	//如果获取失败，使用iconComboBox元素的图标
	if (selectedIcon == -1)
	{
		QIcon icon = iconComboBox->itemIcon(iconComboBox->currentIndex());
		trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(),
			icon, durationSpinBox->value() * 1000);
	}
	else
	{
		trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(),
			QSystemTrayIcon::MessageIcon(selectedIcon), durationSpinBox->value() * 1000);
	}

}

void Window::createIconGroupBox()
{
	iconGroupBox = new QGroupBox("Tray Icon",this);
	iconLabel = new QLabel("Icon:");
	iconComboBox = new QComboBox;
	showIconCheckBox = new QCheckBox("show icon");
	showIconCheckBox->setChecked(true);	//设置默认选中

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

void Window::createTrayIcon()
{
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(":/images/bad.png"));

	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction("Minimize",this,&Window::showMinimized);
	trayIconMenu->addAction("Maximize",this,&Window::showMaximized);
	trayIconMenu->addAction("Restore",this,&Window::showNormal);
	trayIconMenu->addAction("Quit",qApp,&QApplication::quit);

	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->show();
}
