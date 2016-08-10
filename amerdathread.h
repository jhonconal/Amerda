/**************************************************************
**This is available in all editors.
**Copyright(c)2016 ebulent(shenzhen)Co.,LTD. All Right Reserved.
**Contact: http://www.ebulent.com.cn/
**Author: qain.yang
**Postion: Softwere engineer
**email:qian.yang@ebulent.com.cn jhonconal@outlook.com
**This app sourcecode are for ameda test
**
***************************************************************/
#ifndef AMERDATHREAD_H
#define AMERDATHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
class AmerdaThread : public QThread
{
    Q_OBJECT
public:
   explicit AmerdaThread(QObject *parent=0);
    /**
    * @brief shiftDetection
    * @return default 0  //未识别到任何档速
    * 档速检测函数
    */
   int shiftDetection();
signals:

protected:
    void run();

private:

};

#endif // AMERDATHREAD_H
