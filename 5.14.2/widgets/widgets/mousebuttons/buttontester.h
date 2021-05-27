#pragma once

#include <QWidget>
#include<QTextEdit>
#include<QMouseEvent>
#include<QWheelEvent>

class ButtonTester : public QTextEdit
{
	Q_OBJECT
public:
	ButtonTester(QWidget *parent = nullptr);
	~ButtonTester();

	void mousePressEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent* ev) override;
	void mouseReleaseEvent(QMouseEvent* ev) override;
	void wheelEvent(QWheelEvent* ev) override;
	
	void whatBtn(QMouseEvent* ev);
	//给按钮编个号
	static int buttonByNumber(const Qt::MouseButton btn);
	//返回对应按钮的字符串
	static QString enumNameFromValue(const Qt::MouseButton button);
	//判断当前有哪些按钮按下，并把按下的按钮拼接成字符串
	static QString enumNamesFromMouseButtons(const Qt::MouseButtons buttons);
};
