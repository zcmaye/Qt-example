#include<QApplication>
#include<QWizard>
#include<QwizardPage>
#include<QLabel>
#include<QBoxLayout>
#include<QLineEdit>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

//创建前言页
QWizardPage* createIntroPage()
{
	QWizardPage* page = new QWizardPage;
	page->setTitle("介绍");

	QLabel* label = new QLabel("此向导将帮助您注册超级产品二的副本");
	label->setWordWrap(true);	//设置自动换行(文本过长时)

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(label);

	page->setLayout(layout);
	return page;
}

//创建注册页
QWizardPage* createRegistrationPage()
{
	QWizardPage* page = new QWizardPage;
	page->setTitle("注册");
	page->setSubTitle("请填写两个字段");

	QLabel* nameLabel = new QLabel("Name:");
	QLineEdit* nameEdit = new QLineEdit;

	QLabel* emailLabel = new QLabel("Email address:");
	QLineEdit* emailEdit = new QLineEdit;

	QGridLayout* layout = new QGridLayout;
	layout->addWidget(nameLabel, 0, 0);
	layout->addWidget(nameEdit, 0, 1);
	layout->addWidget(emailLabel, 1, 0);
	layout->addWidget(emailEdit, 1, 1);
	page->setLayout(layout);


	return page;
}

//创建结尾页
QWizardPage* createConclusionPage()
{
	QWizardPage* page = new QWizardPage;
	page->setTitle("完成");

	QLabel* label = new QLabel("您现在已经成功注册,祝你愉快!");
	label->setWordWrap(true);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(label);
	page->setLayout(layout);
	return page;
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QWizard wizard;

	wizard.setWindowTitle("简单的向导");
	wizard.addPage(createIntroPage());
	wizard.addPage(createRegistrationPage());
	wizard.addPage(createConclusionPage());

	wizard.show();

	return a.exec();
}