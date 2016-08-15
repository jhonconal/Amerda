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
#include "qstring.h"
AmerdaWidget::AmerdaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AmerdaWidget)
{
    ui->setupUi(this);
    init();//初始化参数

    updateTimer->setInterval(1000);
    systemTimer->setInterval(1000);

    connect(updateTimer,SIGNAL(timeout()),this,SLOT(RealTimeDataSlot()));
    connect(systemTimer,SIGNAL(timeout()),this,SLOT(SystemTimeSlot()));
    updateTimer->start(0);
    systemTimer->start(0);
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

    this->resize(width,height);
    //    this->resize(1024,768);
    //    setWindowFlags(Qt::FramelessWindowHint);
}

AmerdaWidget::~AmerdaWidget()
{
    delete ui;
}

void AmerdaWidget::init()
{
    help = new Helper(this);
    setLanguage("English");

    initAmerdaCruve();
    initParametersValue();
    isEnglish = true;
    isPreview = true;
    isStopTesting = false;
    UDISK_STATUS = -1;

    desktop = QApplication::desktop();
    width  = desktop->screenGeometry().width();
    height  = desktop->screenGeometry().height();

    edit = new QTextEdit();
    edit->setReadOnly(true);
    updateTimer = new QTimer(this);
    systemTimer = new QTimer(this);
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
        ui->Label_2->setText("TestingChoice:");
        ui->Label_3->setText("StardandArea :");
        ui->SpeedAreaLabel->setText("SpeedArea:");
        ui->PressureAreaLabel->setText("PressureArea:");
        ui->Label_4->setText("TestingStatus:");
        ui->Label_5->setText("Parameters:");
        ui->TestButton->setText("Start");
        ui->MaxValueLabel->setText("MaxValue(mmHg)");
        ui->MinValueLabel->setText("MinValue(mmHg)");
        ui->FrequenceLabel->setText("Period/Frequency");
        ui->LanguageButton->setText("Language");
        ui->LogButton->setText("Log Preview");
        ui->SaveButton->setText("Save");
        return true;
    }else {
        ui->Label_2->setText("测试选项:");
        ui->Label_3->setText("标准区间:");
        ui->SpeedAreaLabel->setText("速度范围:");
        ui->PressureAreaLabel->setText("压力范围:");
        ui->Label_4->setText("测试状态:");
        ui->Label_5->setText("参数输出:");
        ui->TestButton->setText("启动");
        ui->MaxValueLabel->setText("最大值(mmHg)");
        ui->MinValueLabel->setText("最小值(mmHg)");
        ui->FrequenceLabel->setText("周期/频率");
        ui->LanguageButton->setText("语言");
        ui->LogButton->setText("日志预览");
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
    QPen pen,pen2;
    QFont font,font2;
    font.setBold(true);
    font2.setBold(true);
    font2.setPointSize(15);
    font.setPointSize(12);
    pen.setWidth(1);
    pen2.setWidth(2);
    pen2.setColor(QColor(255, 0, 127));
    pen.setColor(Qt::blue);
    ui->qCustomPlot->legend->setVisible(true);
    ui->qCustomPlot->legend->setTextColor(Qt::blue);
    ui->qCustomPlot->addGraph();
    ui->qCustomPlot->graph(0)->setPen(pen);
    ui->qCustomPlot->graph()->setAntialiasedFill(true);
    if(setLanguage("English")){
        ui->qCustomPlot->graph(0)->setName("Pressure Cruve");
    }else {
        ui->qCustomPlot->graph(0)->setName("压力曲线");
    }
    //添加 Upper Lower 刻度线
    //===================================================================
    ui->qCustomPlot->addGraph();
    ui->qCustomPlot->graph(1)->setPen(pen2);

    ui->qCustomPlot->addGraph();
    ui->qCustomPlot->graph(2)->setPen(pen2);
    ui->qCustomPlot->legend->removeItem(ui->qCustomPlot->legend->itemCount()-1);
    ui->qCustomPlot->legend->removeItem(ui->qCustomPlot->legend->itemCount()-1);
   //===================================================================
    ui->qCustomPlot->axisRect()->setupFullAxesBox();
    //  ui->qCustomPlot->plotLayout()->insertRow(0);
    //  ui->qCustomPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->qCustomPlot, "Pressure Cruve"));
    ui->qCustomPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    ui->qCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    //绘制y轴信息
    ui->qCustomPlot->yAxis->setLabelPadding(0);
    ui->qCustomPlot->yAxis->setTickLabelFont(font);
    ui->qCustomPlot->yAxis->setLabelFont(font2);
    ui->qCustomPlot->yAxis->setAutoTickStep(false);
    ui->qCustomPlot->yAxis->setRangeReversed(false);
    ui->qCustomPlot->yAxis->setLabelColor("#FF007F");
    ui->qCustomPlot->yAxis->setRange(300,800);
    ui->qCustomPlot->yAxis->setTickStep(50);
    ui->qCustomPlot->yAxis->setLabel("(pressure/mmHg)");
    //    ui->qCustomPlot->yAxis->setLabel("(pressure/Mpa)");
    ui->qCustomPlot->yAxis->setTickLabelRotation(22.5);//标签翻转角度
    //绘制y2轴信息
    ui->qCustomPlot->yAxis2->setAutoTickStep(false);
    ui->qCustomPlot->yAxis2->setRangeReversed(false);
    ui->qCustomPlot->yAxis2->setRange(300,800);
    ui->qCustomPlot->yAxis2->setTickStep(50);
    //绘制x轴信息
    ui->qCustomPlot->xAxis->setTickLabelFont(font);
    ui->qCustomPlot->xAxis->setLabelFont(font);
    ui->qCustomPlot->xAxis->setAutoTickStep(false);
    ui->qCustomPlot->xAxis->setTickStep(1);
    ui->qCustomPlot->xAxis->setLabelColor("#FF007F");
    ui->qCustomPlot->xAxis->setLabel("(time/s)");
    //    ui->qCustomPlot->xAxis->setTickLabelRotation(12.5);
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
    QPen pen;
    pen.setWidth(2);
    QTime time;
    time = QTime::currentTime();
    //获取x轴坐标
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    xAxisKey =key;
    static double lastPointKey = 0.0;

    if(key - lastPointKey >0.025)
    {
        qsrand(time.msec()+time.second()*10+1);
        yAxisValue = qrand()%500+301;
        ui->qCustomPlot->graph(0)->addData(key,yAxisValue);
        ui->qCustomPlot->graph(0)->removeDataBefore(key-8);
//        ui->qCustomPlot->graph(0)->rescaleValueAxis();//坐标值自动缩放
        lastPointKey = key;
    }
    //添加标定刻度线
    ui->qCustomPlot->graph(1)->addData(0,400);
    ui->qCustomPlot->graph(1)->addData(xAxisKey+1,400);
    ui->qCustomPlot->graph(2)->addData(0,600);
    ui->qCustomPlot->graph(2)->addData(xAxisKey+1,600);


    //    qDebug()<<"(xAxis,yAxis)=("<<key<<","<<yAxisValue<<")";
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
    if(this->Status){
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
    text="=====================================================================\n";
    text.append("***                         AMEDA  Inspection Log                 ***\n");
    text.append("***                                                               ***\n");
    text.append("***  INTERNATIONAL STANDARD ATMOSPHERE:1Mpa≈760mmHg              ***\n");
    text.append("***  LOG_TIME :  "+QDateTime::currentDateTime().toString("hh:mm:ss MM/dd/yyyy")+
                " UTC                          ***\n");
    text.append("***  COPYRIGHT :  Copyright(c)2016 ebulent(shenzhen)Co.,LTD.      ***\n");
    text.append("***  PRODUCT :  Ameda                                             ***\n");
    text.append("***  COMPANY :  ebulent                                           ***\n");
    text.append("***  DESCRIPTION :  qian.yang@ebulent.com                         ***\n");
    text.append("***                                                               ***\n");
    text.append("=====================================================================\n");

    text.append("------>Speed Switch : "+tr("[%1").arg(ui->comboBox->currentText())+"]\n");
    text.append("------>Suction Switch : "+tr("[%1").arg(ui->comboBox_2->currentText())+"]\n");
    text.append("------>Pumping Numbers : "+tr("[%1").arg(ui->comboBox_3->currentText())+"]\n");
    text.append("Parameters Output:\n");
    text.append("------>MaxValue in 3 minutes : "+tr("[%1").arg(ui->MaxValueLineEdit->text())+" mmHg]\n");
    text.append("------>MinValue in 3 minutes : "+tr("[%1").arg(ui->MinValueLineEdit->text())+" mmHg]\n");
    text.append("------>Period/Frequency :"+tr("[%1").arg(ui->FrequenceLineEdit->text())+" s]\n");
    text.append("=====================================================================\n");
    text.append("------>测试通过状态 ："+tr("%1").arg(ISPASS));

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
    amerda =new AmerdaThread(this);
    if(isStopTesting){
        connect(updateTimer,SIGNAL(timeout()),this,SLOT(RealTimeDataSlot()));//打开数据停止绘制曲线
        qDebug()<<"Start Inspection:"<<ui->comboBox->currentText()<<"+"<<
                  ui->comboBox_2->currentText()<<"+"<<ui->comboBox_3->currentText();
        if(isEnglish){
            ui->TestButton->setText("Start");
        }else {
            ui->TestButton->setText("启动");
        }
        amerda->start();
    }else {
        qDebug()<<"[kill the thread.]";
        amerda->terminate();
        disconnect(updateTimer,SIGNAL(timeout()),this,SLOT(RealTimeDataSlot()));//关闭数据停止绘制曲线
        if(isEnglish){
            ui->TestButton->setText("Stop");
        }else {
            ui->TestButton->setText("停止");
        }
    }
    isStopTesting = !isStopTesting;
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
    if(!isEnglish){
        setLanguage("English");
        ui->qCustomPlot->graph(0)->setName("Pressure Cruve");
    }else {
        setLanguage("Chinese");
        ui->qCustomPlot->graph(0)->setName("压力曲线");
    }
    isEnglish = !isEnglish;
}
/**
 * @brief AmerdaWidget::SystemTimeSlot
 * 系统时间显示
 */
void AmerdaWidget::SystemTimeSlot()
{
    ui->TimeLabel->setText(QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss"));
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
    for(int i=0;i<1000;i++)
    {
        for(int j=0;j<1000*ms;j++)
        {
            ;
        }
    }
}

void AmerdaWidget::on_LogButton_clicked()
{
    if(isPreview){
        edit->setGeometry(width/2-300,height/2-200,600,400);
        edit->setText(text);
        edit->show();
    }else {
        edit->close();
    }
    isPreview = !isPreview;
}

void AmerdaWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->type()==QEvent::MouseButtonPress) {
        edit->close();
        event->accept();
    }
}
