#pragma once

#include <QWidget>
#include<QLineEdit>

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(QWidget *parent = nullptr);
	~Window();
public slots:
	void echoChanged(int);
	void validatorChanged(int);
	void alignmentChanged(int);
	void inputMaskChanged(int);
	void accessChanged(int);
private:
	QLineEdit* echoLineEdit;		//显示模式
	QLineEdit* validatorLineEdit;	//验证器
	QLineEdit* alignmentLineEdit;	//对其方式
	QLineEdit* inputMaskLineEdit;	//输入模板
	QLineEdit* accessLineEdit;		//访问（读/写）？
};
