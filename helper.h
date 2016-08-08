#ifndef HELPER_H
#define HELPER_H

#include<QObject>
#include<QTranslator>
#include<QDesktopWidget>
#include<QtGui>
#include<QtCore>
#include<QString>
#include <QFile>
#include<QByteArray>
#include<QProcess>
#ifdef Q_OS_LINUX
#include<QSound>
#endif
#include<QApplication>
class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = 0);
    double Hextodec(char *hex);
    //设置编码为UTF8
    void SetUTF8Code();
    void SetGB232Code();
    void SetChinese();
    QString Char2String(char *ch);
    char *String2Char(QString str);
    //播放声音
    void PlaySound(QString soundName);
    //设置系统日期时间
    void SetSystemDateTime(int year,int month,int day,int hour,int min,int sec);
    //设置皮肤颜色
    //设置皮肤样式
    void SetStyle(const QString &styleName);
    /**
     * @brief WriteSaveFile
     * @param text 写入文件的内容
     * @param filename  创建文件名
     * @return true 成功返回真
     */
    bool WriteSaveFile(const QString &filename ,QString text);

signals:

public slots:

};

#endif // HELPER_H
