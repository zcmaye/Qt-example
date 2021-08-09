#include<QApplication>
#include"licensewizard.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	LicenseWizard wizard;
	wizard.show();


	return a.exec();
}