#include "licensewizard.h"

LicenseWizard::LicenseWizard(QWidget *parent)
	: QWizard(parent)
{
	addPage(new IntroPage);

	//设置向导样式
	setWizardStyle(QWizard::WizardStyle::ModernStyle);
	//色设置帮助按钮
	setOption(WizardOption::HaveHelpButton, true);
	//设置图片
	setPixmap(WizardPixmap::LogoPixmap, QPixmap(":/images/logo.png"));

	setWindowTitle("许可向导");
}

LicenseWizard::~LicenseWizard()
{
}

/*@IntroPage*/
IntroPage::IntroPage(QWidget* parent)
	:QWizardPage(parent)
{
	setTitle("前导页面");
	//左侧图
	setPixmap(QWizard::WizardPixmap::WatermarkPixmap, QPixmap(":/images/watermark.png"));


}
