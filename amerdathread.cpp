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
#include "amerdathread.h"

AmerdaThread::AmerdaThread(QObject*parent):
    QThread(parent)
{

}
/**
* @brief shiftDetection
* @return default 0
* 档速检测函数、通过检测霍尔器件来判断档速切换
*/
int AmerdaThread::shiftDetection()
{
    return 0;
}

void AmerdaThread::run()
{
//     while(1){
//         qDebug()<<"线程开启测试...";
//     }
}
