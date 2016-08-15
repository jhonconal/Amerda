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
#ifndef AMERDAWIDGET_H
#define AMERDAWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QDate>
#include <QPen>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDesktopWidget>
#include"dirent.h"
#include "qcustomplot.h"
#include "helper.h"
#include "amerdathread.h"
#include "messagebox.h"

#define DESKTOP
//#define iMX6

namespace Ui {
class AmerdaWidget;
}

class AmerdaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AmerdaWidget(QWidget *parent = 0);
    ~AmerdaWidget();
    /**
     * @brief init
     * 初始化环境
     */
    void init();
    /**
     * @brief setLanguage
     * @param language
     * @return
     * 设置程序语言
     */
    bool setLanguage(QString language);
    /**
     * @brief initAmerdaCruve
     * 初始化压力曲线面板
     */
    void initAmerdaCruve();
    /**
     * @brief initParametersValue
     * 初始化参数值
     */
    void initParametersValue();
    /**
     * @brief setyAxisValue
     * @param value
     * 设置y轴坐标值
     */
    void setyAxisValue(double value);
    /**
     * @brief setParametersValue
     * @param Max
     * @param Min
     * @param Frquency
     * @param Status
     * 设置获取采集的参数值
     */
    void setParametersValue(qreal Max,qreal Min,qreal Frquency,bool Status );
    /**
     * @brief AmerdaLogSave
     * 测试日志保存
     */
    bool AmerdaLogSave();
    /**
     * @brief AmerdaCruveSave
     * @return
     * 测试压力曲线保存
     */
    bool AmerdaCruveSave();
    /**
     * @brief UDiskSpecialFileDetection
     * @return default -1 未检测到U盘
     * 0;//检测到U盘并且里面包含Ameda_data文件夹
     * 1;//检测到U盘文件、但未发现Ameda_data文件夹、创建这个文件夹
     * U盘挂载检测函数
     */

    int UDiskDetection();
    /**
     * @brief SLEEP
     * @param ms  睡眠时间
     * 睡眠函数
     */
    void SLEEP(int ms);


protected:
    void paintEvent(QPaintEvent*);

private slots:
    /**
     * @brief on_TestButton_clicked
     * 启动选择档位测试槽函数
     */
    void on_TestButton_clicked();
    /**
     * @brief on_SaveButton_clicked
     * 保存日志槽函数
     */
    void on_SaveButton_clicked();
    /**
     * @brief RealTimeDataSlot
     * 实时数据槽函数
     */
    void RealTimeDataSlot();
    /**
     * @brief on_LanguageButton_clicked
     * 语言设置槽函数
     */
    void on_LanguageButton_clicked();

    void SystemTimeSlot();
    void on_LogButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::AmerdaWidget *ui;
    QTimer *updateTimer,*systemTimer;
    float Data1,TempData,Data2;
    double xAxisValue,yAxisValue;
    int width,height;
    qreal Max,Min,Frequency;
    bool Status  //测试通过状态标志
         ,isEnglish
         ,isPreview//是否预览
         ,isStopTesting;//termirate the testing or not
    QTextEdit *edit;//预览文本框
    int  UDISK_STATUS;//U Disk状态
    Helper *help;
    AmerdaThread *amerda;
//    MessageBox *messageBox;
    QString text ;//log save QString
    QDesktopWidget *desktop;

    double xAxisKey;
};

#endif // AMERDAWIDGET_H
