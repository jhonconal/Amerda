#include "helper.h"

Helper::Helper(QObject *parent) : QObject(parent)
{

}
double Helper::Hextodec(char *hex)
{
    int i;
    double Dec=0;
    for(i = 0; hex[i] != '\0'; i++)
    {
        if(hex[i] >= '0' && hex[i] <= '9')
            Dec = Dec * 16 + hex[i] - '0';
        if(hex[i] >= 'a' && hex[i] <= 'f')
            Dec = Dec * 16 + hex[i] - 'a' + 10;
        if(hex[i] >= 'A' && hex[i] <= 'F')
            Dec = Dec * 16 + hex[i] - 'A' + 10;
    }
    return Dec;
}
void Helper::SetUTF8Code()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif
}

void Helper::SetGB232Code()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif
}
//load the qt_zh_CN.qm
void Helper::SetChinese()
{
    QTranslator  *translator =new QTranslator(qApp);
    translator->load(":/fonts/qt_zh_CN.qm");
    qApp->installTranslator(translator);
}

QString Helper::Char2String(char *ch)
{
    return QString(QLatin1String(ch));
}

char *Helper::String2Char(QString str)
{
    char *ch;
    QByteArray ba = str.toLatin1();
    ch = ba.data();
    return ch;
}

void Helper::PlaySound(QString soundName)
{
    //使用绝对路径
#ifdef Q_OS_LINUX
    QSound::play(soundName);
#endif
}

void Helper::SetSystemDateTime(int year, int month, int day, int hour, int min, int sec)
{
    QProcess p(0);
    p.start("cmd");
    p.waitForStarted();
    //    QByteArray ba = QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1();
    p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();

    p.start("cmd");
    p.waitForStarted();
    //    QByteArray ba2 = QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1();
    p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
}

void Helper::SetStyle(const QString &styleName)
{
    QFile file(QString(":/qss/%1.css").arg(styleName));
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}
/**
 * @brief WriteSaveFile
 * @param text 写入文件的内容
 * @param filename  创建文件名
 * @return true 成功返回真
 */
bool Helper::WriteSaveFile(const QString &filename, QString text)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadWrite|QIODevice::Text)){
        QTextStream out(&file);
        if(text!=NULL){//内容不为空写入数据
            out<<text;
            out.flush();
            file.close();
            return true;
        }else {//内容为空拒绝写入日志/写入日志失败,删除创建的文件
            file.close();
            file.remove();//删除文件
            return false;
        }
    }else {//文件不存在时创建文件失败
        file.close();
        return false;
    }
    return false;
}
