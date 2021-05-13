﻿#include "window.h"
#include<QComboBox>
#include<QLabel>
#include<QGroupBox>
#include<QGridLayout>
#include<QStringList>
#include<QDebug>
#define cout qDebug()<<"line:"<<__LINE__

Window::Window(QWidget* parent)
	: QWidget(parent)
{
	//Echo 创建控件
	QLabel* echoLabel = new QLabel("Mode:");
	QComboBox* echoComboBox = new QComboBox;
	echoComboBox->addItems({ "Normal","Password","PasswordEchoOnEdit","No Echo" });
	echoLineEdit = new QLineEdit;
	echoLineEdit->setPlaceholderText("Placeholder Text");
	//把空间添加到布局
	QGridLayout* echoLayout = new QGridLayout;
	echoLayout->addWidget(echoLabel, 0, 0);
	echoLayout->addWidget(echoComboBox, 0, 1);
	echoLayout->addWidget(echoLineEdit, 1, 0, 1, 2);
	//给groupBox设置布局
	QGroupBox* echoGroup = new QGroupBox("Echo");
	echoGroup->setLayout(echoLayout);

	//validator 
	QLabel* validatorLabel = new QLabel("Type:");
	QComboBox* validatorComboBox = new QComboBox;
	validatorComboBox->addItems({ "No validator", "Integer balidator","Double validator" });
	validatorLineEdit = new QLineEdit;
	validatorLineEdit->setPlaceholderText("Placeholder Text");

	QGridLayout* validatorLayout = new QGridLayout;
	validatorLayout->addWidget(validatorLabel, 0, 0);
	validatorLayout->addWidget(validatorComboBox, 0, 1);
	validatorLayout->addWidget(validatorLineEdit, 1, 0, 1, 2);

	QGroupBox* validatorGroup = new QGroupBox("Validator");
	validatorGroup->setLayout(validatorLayout);

	//alignment 
	QLabel* alignmentLabel = new QLabel("Type:");
	QComboBox* alignmentComboBox = new QComboBox;
	alignmentComboBox->addItems({ "Left","Centered","Right" });
	alignmentLineEdit = new QLineEdit;
	alignmentLineEdit->setPlaceholderText("Placeholder Text");

	QGridLayout* alignmentLayout = new QGridLayout;
	alignmentLayout->addWidget(alignmentLabel, 0, 0);
	alignmentLayout->addWidget(alignmentComboBox, 0, 1);
	alignmentLayout->addWidget(alignmentLineEdit, 1, 0, 1, 2);

	QGroupBox* alignmentGroup = new QGroupBox("Alignment");
	alignmentGroup->setLayout(alignmentLayout);

	//inputMask 
	QLabel* inputMaskLabel = new QLabel("Type:");
	QComboBox* inputMaskComboBox = new QComboBox;
	inputMaskComboBox->addItems({ "No mask","Phone number","ISO date","License key" });
	inputMaskLineEdit = new QLineEdit;
	inputMaskLineEdit->setPlaceholderText("Placeholder Text");

	QGridLayout* inputMaskLayout = new QGridLayout;
	inputMaskLayout->addWidget(inputMaskLabel, 0, 0);
	inputMaskLayout->addWidget(inputMaskComboBox, 0, 1);
	inputMaskLayout->addWidget(inputMaskLineEdit, 1, 0, 1, 2);

	QGroupBox* inputMaskGroup = new QGroupBox("InputMask");
	inputMaskGroup->setLayout(inputMaskLayout);

	//Access 
	QLabel* accessLabel = new QLabel("Read-only:");
	QComboBox* accessComboBox = new QComboBox;
	accessComboBox->addItems({"true","false"});
	accessLineEdit = new QLineEdit;
	accessLineEdit->setPlaceholderText("Placeholder Text");

	QGridLayout* accessLayout = new QGridLayout;
	accessLayout->addWidget(accessLabel, 0, 0);
	accessLayout->addWidget(accessComboBox, 0, 1);
	accessLayout->addWidget(accessLineEdit, 1, 0, 1, 2);

	QGroupBox* accessGroup = new QGroupBox("Access");
	accessGroup->setLayout(accessLayout);

	
	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->addWidget(echoGroup, 0, 0);
	mainLayout->addWidget(validatorGroup, 1, 0);
	mainLayout->addWidget(alignmentGroup, 2, 0);
	mainLayout->addWidget(inputMaskGroup, 0, 1);
	mainLayout->addWidget(accessGroup, 1, 1);

	setLayout(mainLayout);


	//关联信号与槽
	connect(echoComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &Window::echoChanged);
	connect(validatorComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &Window::validatorChanged);
	connect(alignmentComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &Window::alignmentChanged);
	connect(inputMaskComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &Window::inputMaskChanged);
	connect(accessComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &Window::accessChanged);
}

Window::~Window()
{
}

void Window::echoChanged(int index)
{
	cout << __func__;
	switch (index)
	{
	case 0:
		qobject_cast<QLineEdit*>(sender())->setEchoMode(QLineEdit::EchoMode::Normal);
		break;
	case 1:
		echoLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
		break;
	case 2:
		echoLineEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
		break;
	case 3:
		echoLineEdit->setEchoMode(QLineEdit::EchoMode::NoEcho);
		break;
	}

}
void Window::validatorChanged(int index)
{
	cout << __func__;
	switch (index)
	{
	case 0:
		validatorLineEdit->setValidator(nullptr);
		break;
	case 1:
		validatorLineEdit->setValidator(new QIntValidator(100,300,validatorLineEdit));
		break;
	case 2:
		validatorLineEdit->setValidator(new QDoubleValidator(validatorLineEdit));
		break;
	}
	validatorLineEdit->clear();
}

void Window::alignmentChanged(int)
{
	cout << __func__;
}

void Window::inputMaskChanged(int)
{
	cout << __func__;
}

void Window::accessChanged(int)
{
	cout << __func__;
}
