/**********************************************************
**This is available in all editors.
**Copyright (c) 2016
**Contact: http://www.ebulent.com.cn/
**Author: qain.yang
**Postion: Softwere engineer
**email:qian.yang@ebulent.com.cn jhonconal@outlook.com
**This app sourcecode are for ameda test
**
***********************************************************/
#include "amerdawidget.h"
#include <QApplication>
#include <QTextCodec>
#include <stdio.h>
#include "helper.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    #if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)//判断QT版本是否大于5.0
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));       //支持Tr中文
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));//支持中文文件名显示
    #else
        QFont font;
        font.setFamily(("kaiti.TTF"));
        font.setBold(false);
        a.setFont(font);
        Helper *help = new Helper();
        help->SetChinese();
    #endif
    AmerdaWidget w;
    w.show();

    return a.exec();
}
