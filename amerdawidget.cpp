#include "amerdawidget.h"
#include "ui_amerdawidget.h"
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
#include <QStandardPaths>
#else
#endif
#include <QDesktopWidget>
AmerdaWidget::AmerdaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AmerdaWidget)
{
    ui->setupUi(this);
    help = new Helper(this);
    setLanguage("English");
    initAmerdaCruve();
    isEnglish = true;

    QDesktopWidget *desktop = QApplication::desktop();
    int width  = desktop->screenGeometry().width();
    int heigh  = desktop->screenGeometry().height();
    updateTimer = new QTimer(this);
    updateTimer->setInterval(5*1000);

    connect(updateTimer,SIGNAL(timeout()),this,SLOT(RealTimeDataSlot()));
    updateTimer->start(0);

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

    ui->qCustomPlot->legend->setVisible(true);
    ui->qCustomPlot->legend->setTextColor(Qt::blue);
    ui->qCustomPlot->addGraph();

    QPen pen;
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    pen.setWidth(1);
    pen.setColor(QColor(255, 0, 127));
    if(setLanguage("English")){
        ui->qCustomPlot->graph()->setName("Pressure Cruve");
    }else {
        ui->qCustomPlot->graph()->setName("压力曲线");
    }

//    ui->qCustomPlot->plotLayout()->insertRow(0);
//    ui->qCustomPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->qCustomPlot, "Pressure Cruve"));
    ui->qCustomPlot->graph()->setPen(pen);
    ui->qCustomPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(3));
    ui->qCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(11)));
    //绘制y轴信息
    ui->qCustomPlot->yAxis->setLabelFont(font);
    ui->qCustomPlot->yAxis->setLabelColor("#FF007F");
//    ui->qCustomPlot->yAxis->setRangeReversed(false);
    ui->qCustomPlot->yAxis->setRange(0,1000,Qt::AlignHCenter);
    ui->qCustomPlot->yAxis->setAutoTickStep(false);
    ui->qCustomPlot->yAxis->setTickStep(50);
    ui->qCustomPlot->yAxis->setLabel("(mmg/H)");
    ui->qCustomPlot->yAxis->setTickLabelRotation(22.5);//标签翻转角度
    //绘制x轴信息
    ui->qCustomPlot->xAxis->setLabelFont(font);
    ui->qCustomPlot->xAxis->setLabelColor("#FF007F");
    ui->qCustomPlot->xAxis->setLabel("(time/ms)");
    ui->qCustomPlot->xAxis->setTickLabelRotation(22.5);
    ui->qCustomPlot->xAxis->setLabelPadding(-3);

}

void AmerdaWidget::setyAxisValue(qreal value)
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
        ui->StatusLabel->setStyleSheet("background-color:rgb(0, 255, 128);color: rgb(255, 255, 255)");
    }
}
/**
  * @brief AmerdaLogSave
  * 保存log日志文档
  */
bool AmerdaWidget::AmerdaLogSave()
{

    QString logName = "./ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".log";
    qDebug()<<"Log File Path: "+logName;
    QString text =NULL;

    bool result = help->WriteSaveFile(logName,text);
    if(result){
        return true;
    }
    return false;
}
/**
 * @brief AmerdaCruveSave
 * 获取压力曲线pdf文档
 */
bool AmerdaWidget::AmerdaCruveSave()
{

//    QString pdfPath = QStandardPaths::displayName(QStandardPaths::DocumentsLocation);
    QString pdfName = "./ameda-"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".pdf";
    qDebug()<<"Pdf File Path: "+pdfName;
    /*
      保存pdf文档
    */
    if(ui->qCustomPlot->savePdf(pdfName,false,1024,768,"null","ameda test")){
//         QMessageBox::about(NULL,"SAVE DATA","save data sussess.");
         return true;
     }else {
//         QMessageBox::about(NULL,"SAVE DATA","save data failed.");
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
     * 保存压力曲线文档pdf  路径：app运行路径下
     * 文件保存格式："ameda-2016-08-04-15-06-32.pdf"
     * ameda-year-month-day-hour-min-mesc.pdf
     */
    isPdf = AmerdaCruveSave();
    if(isLog&&isPdf){
        QMessageBox::about(NULL,"SAVE AMEDA DATA","save Ameda data sussess.");
    }else if (isLog==true||isPdf==false) {
        QMessageBox::about(NULL,"SAVE AMEDA DATA","save Ameda Log sussess.");
    }else if (isLog==false||isPdf==true) {
        QMessageBox::about(NULL,"SAVE AMEDA DATA","save Ameda Cruve sussess.");
    }else {
        QMessageBox::about(NULL,"SAVE AMEDA DATA","save all Ameda data failed.");
    }
}
/**
 * @brief AmerdaWidget::RealTimeDataSlot
 * 实时yValue
 */
void AmerdaWidget::RealTimeDataSlot()
{
   QPen pen;
   pen.setWidth(2);
   pen.setColor(QColor(255,0,127));
   ui->qCustomPlot->graph()->setPen(pen);
   ui->qCustomPlot->graph()->setAntialiasedFill(true);
   ui->qCustomPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
   ui->qCustomPlot->xAxis->setDateTimeFormat("mm:ss");
//     ui->qCustomPlot->xAxis->setDateTimeFormat("hh:mm:ss");
   ui->qCustomPlot->xAxis->setAutoTickStep(false);
   ui->qCustomPlot->xAxis->setTickStep(1);
   ui->qCustomPlot->axisRect()->setupFullAxesBox();

   double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

   static double lastPointKey = 0.0;

   if(key - lastPointKey >0.1)
   {
       QTime time;
       time = QTime::currentTime();
       qsrand(time.msec()+time.second()*1000);
       int yValue = qrand()%1000-1;
       ui->qCustomPlot->graph()->addData(key,yValue);
       ui->qCustomPlot->graph()->removeDataBefore(key-8);
       ui->qCustomPlot->graph()->rescaleValueAxis();
       lastPointKey = key;
   }
   ui->qCustomPlot->xAxis->setRange(key+0.25,8,Qt::AlignRight);//x轴8大格每小格0.25*
//   ui->qCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
//   ui->qCustomPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%9+1)));
   ui->qCustomPlot->replot();

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
