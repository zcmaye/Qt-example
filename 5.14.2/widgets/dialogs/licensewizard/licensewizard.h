#pragma once

#if defined(WIN32)
#pragma execution_character_set("utf-8")
#endif

#include <QWizard>

class LicenseWizard : public QWizard
{
	Q_OBJECT

public:
	LicenseWizard(QWidget *parent = nullptr);
	~LicenseWizard();
};


//前导页面
class IntroPage : public QWizardPage
{
	Q_OBJECT
public:
	IntroPage(QWidget* parent = nullptr);

private:
};
