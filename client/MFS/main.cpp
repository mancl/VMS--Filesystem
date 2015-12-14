#include <QApplication>
#include"mainpage.h"
#include<QTextCodec>
#include <QApplication>
#include <QtPlugin> //这个


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForTr(codec);
//    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());//windows zhongwen OK

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());


    MainPage page;
    page.show();
    return a.exec();
}
