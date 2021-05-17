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
};
