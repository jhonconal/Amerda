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
#include "amerdawidget.h"
#include "ui_amerdawidget.h"
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
#include <QStandardPaths>
#else
#endif
#include <QDesktopWidget>
#include "qstring.h"
AmerdaWidget::AmerdaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AmerdaWidget)
{
    ui->setupUi(this);
    help = new Helper(this);
    setLanguage("English");
    initAmerdaCruve();
    isEnglish = true;
    isPass = false;

    QDesktopWidget *desktop = QApplication::desktop();
    int width  = desktop->screenGeometry().width();
    int heigh  = desktop->screenGeometry().height();
    updateTimer = new QTimer(this);
    updateTimer->setInterval(1000);

    connect(updateTimer,SIGNAL(timeout()),this,SLOT(RealTimeDataSlot()));
    updateTimer->start(0);

    //检测U盘
    int result = UDiskDetection();
    if(result == 0){
        qDebug()<<"UDisk Mounted,Founded the [Ameda_data] floder.";
        //        QMessageBox::about(NULL,"UDisk Detection","UDisk Mounted,and Found [Ameda_data] Floder.");
    }else if (result == 1) {
        qDebug()<<"UDisk Mounted,Create  the  [Ameda_data] floder.";
        //        QMessageBox::about(NULL,"UDisk Detection","UDisk Mounted,and Create [Ameda_data] Floder.");
    }else {
        qDebug()<<"UDisk uMounted.";
        //        QMessageBox::about(NULL,"UDisk Detection","UDisk uMounted.");
    }
    this->resize(width,heigh);

//    this->resize(1024,768);
//    setWindowFlags(Qt::FramelessWindowHint);
}

AmerdaWidget::~AmerdaWidget()
{
    delete ui;
}
/**
 * @brief AmerdaWidget::setLanguage
 * @param language
 * @return
 * 程序语言设置
 */
bool AmerdaWidget::setLanguage(QString language)
{
    if(language == "English"){
        ui->Label_2->setText("TestGear:");
        ui->Label_3->setText("PressureCurve:");
        ui->Label_4->setText("TestStatus:");
        ui->Label_5->setText("Parameters:");
        ui->TestButton->setText("Start");
        ui->MaxValueLabel->setText("MaxValue");
        ui->MinValueLabel->setText("MinValue");
        ui->FrequenceLabel->setText("Period/Frequency");
        ui->LanguageButton->setText("Language");
        ui->SaveButton->setText("Save");
        return true;
    }else {
        ui->Label_2->setText("测试档位:");
        ui->Label_3->setText("压力曲线:");
        ui->Label_4->setText("测试状态:");
        ui->Label_5->setText("参数输出:");
        ui->TestButton->setText("启动");
        ui->MaxValueLabel->setText("最大值");
        ui->MinValueLabel->setText("最小值");
        ui->FrequenceLabel->setText("周期/频率");
        ui->LanguageButton->setText("语言");
        ui->SaveButton->setText("保存");
        return false;
    }
    return false;
}
/**
 * @brief AmerdaWidget::initParametersValue
 * 参数值初始化
 */
void AmerdaWidget::initParametersValue()
{
    this->Max = 0;
    this->Min = 0;
    this->Frequency = 0;
    this->Status = false;
}
/**
 * @brief AmerdaWidget::initAmerdaCruve
 * 压力曲线初始化
 */
void AmerdaWidget::initAmerdaCruve()
{
    QPen pen;
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    pen.setWidth(2);
    pen.setColor(QColor(255, 0, 127));
    ui->qCustomPlot->legend->setVisible(true);
    ui->qCustomPlot->legend->setTextColor(Qt::blue);
    ui->qCustomPlot->addGraph();
    ui->qCustomPlot->graph()->setPen(pen);
    ui->qCustomPlot->graph()->setAntialiasedFill(true);
    if(setLanguage("English")){
        ui->qCustomPlot->graph()->setName("Pressure Cruve");
    }else {
        ui->qCustomPlot->graph()->setName("压力曲线");
    }
    ui->qCustomPlot->axisRect()->setupFullAxesBox();
    //    ui->qCustomPlot->plotLayout()->insertRow(0);
    //    ui->qCustomPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->qCustomPlot, "Pressure Cruve"));
    ui->qCustomPlot->graph(0)->setPen(pen);
    ui->qCustomPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    ui->qCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(11)));
    //绘制y轴信息
    ui->qCustomPlot->yAxis->setAutoTickStep(false);
    ui->qCustomPlot->yAxis->setRangeReversed(false);
    ui->qCustomPlot->yAxis->setLabelFont(font);
    ui->qCustomPlot->yAxis->setLabelColor("#FF007F");
    ui->qCustomPlot->yAxis->setRange(0,10);
    ui->qCustomPlot->yAxis->setTickStep(0.5);
//    ui->qCustomPlot->yAxis->setLabel("(pressure/mmHg)");
    ui->qCustomPlot->yAxis->setLabel("(pressure/Mpa)");
    ui->qCustomPlot->yAxis->setTickLabelRotation(22.5);//标签翻转角度
    //绘制x轴信息
    ui->qCustomPlot->xAxis->setAutoTickStep(false);
    ui->qCustomPlot->xAxis->setTickStep(1);
    ui->qCustomPlot->xAxis->setLabelFont(font);
    ui->qCustomPlot->xAxis->setLabelColor("#FF007F");
    ui->qCustomPlot->xAxis->setLabel("(time/s)");
    ui->qCustomPlot->xAxis->setTickLabelRotation(22.5);
    ui->qCustomPlot->xAxis->setLabelPadding(-3);
    ui->qCustomPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->qCustomPlot->xAxis->setDateTimeFormat("mm:ss");
    //ui->qCustomPlot->xAxis->setDateTimeFormat("hh:mm:ss");

}
/**
 * @brief AmerdaWidget::RealTimeDataSlot
 * 实时yValue
 */
void AmerdaWidget::RealTimeDataSlot()
{
    ui->TimeLabel->setText(QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss"));
    QPen pen;
    pen.setWidth(2);
    //获取x轴坐标
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    static double lastPointKey = 0.0;

    if(key - lastPointKey >0.025)
    {
        QTime time;
        time = QTime::currentTime();
        qsrand(time.msec()+time.second()*10+1);
        yAxisValue = qrand()%11;
        ui->qCustomPlot->graph()->addData(key,yAxisValue);
        ui->qCustomPlot->graph()->removeDataBefore(key-8);
        ui->qCustomPlot->graph()->rescaleValueAxis();
        lastPointKey = key;
    }
    ui->qCustomPlot->xAxis->setRange(key+0.25,8,Qt::AlignRight);//x轴8大格每小格0.25*  移动x坐标
    ui->qCustomPlot->replot();//重绘曲线

}
void AmerdaWidget::setyAxisValue(double value)
{
    yAxisValue = value;
}
/**
 * @brief AmerdaWidget::setParametersValue
 * @param Max
 * @param Min
 * @param Frequency
 * @param Status
 * 参数值获取设置
 */
void AmerdaWidget::setParametersValue(qreal Max, qreal Min, qreal Frequency, bool Status)
{
    this->Max = Max;
    this->Min = Min;
    this->Frequency= Frequency;
    this->Status  = Status;
    if(this->Status==false){
        ui->StatusLabel->setStyleSheet("background-color:rgb(255, 0, 128);color: rgb(255, 255, 255)");
    }else {
        ui->StatusLabel->setStyleSheet("background-color:rgb(0, 215, 125);color: rgb(255, 255, 255)");
    }
}
/**
  * @brief AmerdaLogSave
  * 保存log日志文档
  */
bool AmerdaWidget::AmerdaLogSave()
{
    //获取测试数据值以及状态 操作


    /**
     * 格式化日志文件
     */
    QString ISPASS = NULL, logName=NULL;
    if(isPass){
        ISPASS = "TRUE";
    }else {
        ISPASS = "FALSE";
    }
    if(UDISK_STATUS==0||UDISK_STATUS==1){//UDISK mounted.
#ifdef iMX6
        logName = "/media/sda1/Ameda_data/ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".log";
#else
        logName = "/media/root/JHONCONAL/Ameda_data/ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".log";
#endif
        qDebug()<<"Log File Path: "+logName;
    }else {     //UDISK umounted.
        logName = "./ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".log";
        qDebug()<<"Log File Path: "+logName;
    }
  QString text ="===========================================================================\n";
    text.append("***                         AMEDA  Inspection Log                       ***\n");
    text.append("***                                                                     ***\n");
    text.append("***  LOG_TIME: "+QDateTime::currentDateTime().toString("hh:mm:ss MM/dd/yyyy")+
                " UTC                                  ***\n");
    text.append("***  QMAKE_TARGET_COPYRIGHT = Copyright(c)2016 ebulent(shenzhen)Co.,LTD.***\n");
    text.append("***  QMAKE_TARGET_PRODUCT = Ameda                                       ***\n");
    text.append("***  QMAKE_TARGET_COMPANY = ebulent                                     ***\n");
    text.append("***  QMAKE_TARGET_DESCRIPTION = qian.yang@ebulent.com                   ***\n");
    text.append("***                                                                     ***\n");
    text.append("===========================================================================\n");
    text.append("测试通过状态 ："+tr("%1").arg(ISPASS));


    //保存日志
    bool result = help->WriteSaveFile(logName,text);
    if(result){
        return true;
    }
    return false;
}
/**
 * @brief AmerdaCruveSave
 * 获取压力曲线文档
 */
bool AmerdaWidget::AmerdaCruveSave()
{
    QString pdfName=NULL,bmpName=NULL;
    if(UDISK_STATUS==0||UDISK_STATUS==1){//UDISK mounted.
#ifdef iMX6
        pdfName = "/media/sda1/Ameda_data/ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".pdf";
        bmpName = "/media/sda1/Ameda_data/ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".bmp";
#else
        pdfName = "/media/root/JHONCONAL/Ameda_data/ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".pdf";
        bmpName = "/media/root/JHONCONAL/Ameda_data/ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".bmp";
#endif
        qDebug()<<"Pdf File Path: "+pdfName;
    }else {
        pdfName = "./ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".pdf";
        qDebug()<<"Pdf File Path: "+pdfName;
        bmpName = "./ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".bmp";
        qDebug()<<"Bmp File Path: "+bmpName;
    }
    /*
     *保存pdf/bmp文档
    */
    //if(ui->qCustomPlot->saveBmp(bmpName,1024,768,1.0)){//保存为bmp文档
    if(ui->qCustomPlot->savePdf(pdfName,false,1024,768,"null","ameda test")){//保存为pdf文档
        return true;
    }else {
        return false;
    }
    return false;
}
/**
 * @brief AmerdaWidget::paintEvent
 * 绘图事件
 */
void AmerdaWidget::paintEvent(QPaintEvent *)
{

}
/**
 * @brief AmerdaWidget::on_TestButton_clicked
 * 启动测试
 */
void AmerdaWidget::on_TestButton_clicked()
{
    qDebug()<<"Start Inspection:"<<ui->comboBox->currentText()<<"+"<<ui->comboBox_2->currentText();
    amerda =  new AmerdaThread();
    amerda =new AmerdaThread(this);
    amerda->start();
}
/**
 * @brief AmerdaWidget::on_SaveButton_clicked
 * 保存日志文件
 */
void AmerdaWidget::on_SaveButton_clicked()
{
    /**
     * @brief AmerdaLogSave
     * 保存测试日志文档log
     * 文件保存格式："ameda-2016-08-04-15-06-32.log"
     * ameda-year-month-day-hour-min-mesc.log
     */
    bool isLog,isPdf;
    isLog = AmerdaLogSave();
    /**
     * @brief AmerdaCruveSave
     * 保存压力曲线文档pdf/bmp  路径：app运行路径下
     * 文件保存格式："ameda-2016-08-04-15-06-32.pdf/.bmp"
     * ameda-year-month-day-hour-min-mesc.pdf/.bmp
     */
    isPdf = AmerdaCruveSave();
    if(isLog&&isPdf){
        QMessageBox::about(NULL,"SAVE AMEDA DATA","save all Ameda data sussess.");
    }else if (isLog==true||isPdf==false) {
        QMessageBox::about(NULL,"SAVE AMEDA DATA","save Ameda Log sussess, Ameda Cruve failed.");
    }else if (isLog==false||isPdf==true) {
        QMessageBox::about(NULL,"SAVE AMEDA DATA","save Ameda Cruve sussess, Ameda Log failed.");
    }else {
        QMessageBox::about(NULL,"SAVE AMEDA DATA","save all Ameda data failed.");
    }
}

/**
 * @brief AmerdaWidget::on_LanguageButton_clicked
 * 语言切换槽函数
 */
void AmerdaWidget::on_LanguageButton_clicked()
{
    qDebug()<<"进入设置语言函数:"<<isEnglish;
    isEnglish = !isEnglish;
    if(isEnglish){
        setLanguage("English");
        ui->qCustomPlot->graph(0)->setName("Pressure Cruve");
    }else {
        setLanguage("Chinese");
        ui->qCustomPlot->graph(0)->setName("压力曲线");
    }
}

int AmerdaWidget::UDiskDetection()
{
    DIR *dir=NULL;
#ifdef iMX6
    dir = opendir("/media/sda1/");
#else
    dir= opendir("/media/root/JHONCONAL");
#endif
    if(dir==NULL){
        UDISK_STATUS = -1;
    }else {
#ifdef iMX6
        dir = opendir("/media/sda1/Ameda_data");
#else
        dir= opendir("/media/root/JHONCONAL/Ameda_data");
#endif
        if(dir == NULL){
#ifdef iMX6
            system("mkdir   /media/sda1/Ameda_data");
#else
            system("mkdir  /media/root/JHONCONAL/Ameda_data");
#endif
            UDISK_STATUS = 1;
        }else {
            UDISK_STATUS = 0;
        }
    }
    return UDISK_STATUS;//未检测到U盘
}

void AmerdaWidget::SLEEP(int ms)
{
    for(int i=0;i<10000;i++)
    {
        for(int j=0;j<10*ms;j++)
        {
            ;
        }
    }
}
