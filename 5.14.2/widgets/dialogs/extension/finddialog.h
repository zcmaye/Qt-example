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
	QCheckBox* caseCheckBox;	//���ִ�Сд
	QCheckBox* fromStartCheckBox;	//�ӿ�ʼ����
	QCheckBox* wholeWrodsCheckBox;	//ȫƥ��
	QCheckBox* selectionCheckBox;
	QCheckBox* backwardCheckBox;	//������
	QDialogButtonBox* btnBox;
	QPushButton* findBtn;
	QPushButton* moreBtn;
	QWidget* extension;
};
