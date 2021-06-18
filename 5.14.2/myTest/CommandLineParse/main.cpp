#include<QCoreApplication>
#include<QCommandLineParser>
#include<QCommandLineOption>
#include<QDebug>

int main(int argc ,char*argv[])
{
    QCoreApplication a(argc,argv);

    QCoreApplication::setApplicationName("命令行解析");
    QCoreApplication::setApplicationVersion(QString("Version:") + QT_VERSION_STR);

    QCommandLineParser parser;                  //创建命令行解析
    parser.setApplicationDescription("maye");   //设置helpText()显示的应用程序描述
    parser.addVersionOption();                  //添加-v/--version解析命令
    parser.addHelpOption();                     //添加-h/--help解析命令

    //添加自定义命令选项，name为选项名称，以m为例，程序执行时输入-m/--myself进入自定义的命令
    parser.addOption(QCommandLineOption(QStringList()<<"m"<<"myself","自定义命令m"));

    QCommandLineOption opt(QStringList()<<"y"<<"youself","自定义命令y");
    parser.addOption(opt);

    parser.addOption(QCommandLineOption({"a","age"},"输入年龄","Age","18"));

    parser.process(a);

    if(parser.isSet("m"))
    {
        printf("I'm m\n");
    }
    if(parser.isSet(opt))
    {
        printf("I'm y\n");
        qDebug()<<parser.value(opt);
    }
    if(parser.isSet("age"))
    {
        qDebug()<<"Age is "<<parser.value("age").toInt();
    }
    qDebug()<<"pos "<<parser.positionalArguments();

    return 0;
   // return a.exec();
}
