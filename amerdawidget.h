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
#include "qcustomplot.h"
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
    void setyAxisValue(qreal value);
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
     * @brief AmerdaLog
     * 测试日志保存
     */
    bool AmerdaLogSave();
    bool AmerdaCruveSave();

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

private:
    Ui::AmerdaWidget *ui;
    QTimer *updateTimer;
    float Data1,TempData,Data2;
    qreal xAxisValue,yAxisValue;

    qreal Max,Min,Frequency;
    bool Status,isEnglish;
};

#endif // AMERDAWIDGET_H
