#pragma once

#include <QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QCheckBox>
#include<QDialogButtonBox>

class FindDialog : public QDialog
{
	Q_OBJECT

public:
	FindDialog(QWidget *parent = nullptr);
	~FindDialog();
private:
	QLabel* label;
	QLineEdit* lineEdit;
	QCheckBox* caseCheckBox;	//区分大小写
	QCheckBox* fromStartCheckBox;	//从开始搜索
	QCheckBox* wholeWrodsCheckBox;	//全匹配
	QCheckBox* selectionCheckBox;
	QCheckBox* backwardCheckBox;	//向后查找
	QDialogButtonBox* btnBox;
	QPushButton* findBtn;
	QPushButton* moreBtn;
	QWidget* extension;
};
