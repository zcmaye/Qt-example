#include "finddialog.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
FindDialog::FindDialog(QWidget *parent)
	: QDialog(parent)
{
	label = new QLabel("Find What", this);
	lineEdit = new QLineEdit(this);

	findBtn = new QPushButton("Find", this);
	findBtn->setDefault(true);

	moreBtn = new QPushButton("More", this);
	moreBtn->setCheckable(true);				//设置按钮可以被选中，就是按下去之后可以不自动弹起
	moreBtn->setAutoDefault(false);
	
	btnBox = new QDialogButtonBox(Qt::Vertical);
	btnBox->addButton(findBtn,QDialogButtonBox::ActionRole);
	btnBox->addButton(moreBtn, QDialogButtonBox::ActionRole);


	caseCheckBox = new QCheckBox("Match case", this);
	fromStartCheckBox = new QCheckBox("Search from start", this);
	fromStartCheckBox->setChecked(true);

	wholeWrodsCheckBox = new QCheckBox("Whole words", this);
	backwardCheckBox = new QCheckBox("Search backward", this);
	selectionCheckBox = new QCheckBox("Search selection", this);
	
	//可以隐藏的more区域
	extension = new QWidget;
	connect(moreBtn, &QPushButton::toggled, extension, &QWidget::setVisible);

	QVBoxLayout* extensionLayout = new QVBoxLayout;
	extensionLayout->setContentsMargins(0, 0, 0, 0);
	extensionLayout->addWidget(wholeWrodsCheckBox);
	extensionLayout->addWidget(backwardCheckBox);
	extensionLayout->addWidget(selectionCheckBox);
	extension->setLayout(extensionLayout);

	//
	QHBoxLayout* topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);

	//
	QVBoxLayout* leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	leftLayout->addWidget(caseCheckBox);
	leftLayout->addWidget(fromStartCheckBox);

	QGridLayout* mainLayout = new QGridLayout(this);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);//设置大小限制
	mainLayout->addLayout(leftLayout, 0, 0);
	mainLayout->addWidget(btnBox, 0, 1);
	mainLayout->addWidget(extension, 1, 0, 1, 2);
	//mainLayout->setRowStretch(2, 1);

	setLayout(mainLayout);
	extension->hide();

}

FindDialog::~FindDialog()
{
}
