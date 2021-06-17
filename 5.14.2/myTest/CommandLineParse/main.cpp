#include<QCoreApplication>
#include<QCommandLineParser>
#include<QCommandLineOption>

int main(int argc ,char*argv[])
{
    QCoreApplication a(argc,argv);

    QCoreApplication::setApplicationName("命令行解析");
    QCoreApplication::setApplicationVersion(QString("Version:") + QT_VERSION_STR);

    QCommandLineParser parser;
    parser.setApplicationDescription("maye");
    parser.addVersionOption();
    parser.addHelpOption();

    parser.addOption(QCommandLineOption("-role","show all"));
    parser.addPositionalArgument("-log","显示所有");




   // parser.showVersion();
    parser.showHelp();
    parser.process(a);

    return a.exec();
}
