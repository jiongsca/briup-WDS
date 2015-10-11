#include "wenshidu.h"
#include "ui_wenshidu.h"
#include"panesave.h"

char *TCbg3[]={":/source/eixt.png"};
//char *CJbg2[]={":/source/home_close1.jpg",":/source/home_close2.jpg",
//              ":/source/home_close3.jpg",":/source/home_close4.jpg",
//              ":/source/home_close5.jpg",
//              ":/source/home_close6.jpg",":/source/home_close7.jpg",":/source/home_closeall.jpg"};
char *Bbg[]={":/source/wsdB.png"};
Wenshidu::Wenshidu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wenshidu)
{
    ui->setupUi(this);
    //加一个开启的特效
    paneSave::instance()->animation->setDuration(1000);
    paneSave::instance()->animation->setStartValue(0);
    paneSave::instance()->animation->setEndValue(1);
    paneSave::instance()->animation->start();

    this->ui->TClabel->setStyleSheet(tr("background-image:url(%1)").arg(TCbg3[0]));
    this->ui->Blabel->setStyleSheet(tr("background-image:url(%1)").arg(Bbg[0]));
    Xtimer=new QTimer(this);
    Wtimer=new QTimer(this);
    this->ui->WSDlabel->setStyleSheet("color:#000000;font:20pt\"Modern\";");

    showtime();
    connect(Xtimer, SIGNAL(timeout()), this, SLOT(showtime()));
    connect(Wtimer,SIGNAL(timeout()),this,SLOT(on_NEWButton_clicked()));//这里因为只要一点进去就会触发，会一直触发这个点击的事件，都不需要你去点击刷新
//    Xtimer->start(1000);
}

Wenshidu::~Wenshidu()
{
    delete ui;
}
QString text1;
QString text2;
//在这个UI界面显示时间
void Wenshidu::showtime(){
    QTime time = QTime::currentTime();
    QDate Date = QDate::currentDate();
    text1 = Date.toString("yyyyMMdd\n");
    text2 = time.toString("  hh:mm:ss");
    if ((time.second() % 2) == 0)
 //           text2[4] = ' ';
            text2[7] = ' ';
//    qDebug()<<"riqi"<<text1;
    QString text3 =text1+" "+text2;
   this->ui->Timelabel->setStyleSheet(" color: #000000;font: 20pt \"Modern\";");
   this->ui->Timelabel->setText(text3);
}


void Wenshidu::on_TCButton_clicked()
{
//    Widget* widget1=new Widget(this);//显示新的UI界面
//     paneSave::instance()->widget->ui->CJlabel->setStyleSheet(tr("background-image:url(%1)").arg(CJbg2[1]));//在这里要重新的设置UI的界面背景
         //这里是记录之前那个面板的背景再设回去
//        widget1->show();
      Xtimer->stop();//定时器一定要关不然会有错误的
      Wtimer->stop();
      paneSave::instance()->wenshidu->hide();//要把之前的ui面板关闭了再去显示新的界面
//    paneSave::instance()->wenshidu->close();
      paneSave::instance()->widget->show();
      paneSave::instance()->widget->setBackground();



}




//void Wenshidu::on_EXIT2Button_clicked()
//{

//    QApplication* app;
//    app->exit(0);
////    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
////      animation2->setDuration(1000);
////      animation2->setStartValue(1);
////      animation2->setEndValue(0);
////      animation2->start();
////      connect(animation2, SIGNAL(finished()), this, SLOT(close()));
//}

void Wenshidu::on_EXITButton_clicked()
{   //退出的特效
//    paneSave::instance()->animation->setDuration(1000);
//    paneSave::instance()->animation->setStartValue(1);
//    paneSave::instance()->animation->setEndValue(0);
//    paneSave::instance()->animation->start();
//    connect(paneSave::instance()->animation, SIGNAL(finished()), this, SLOT(close()));
       QApplication* app;
       app->exit(0);
//          animation2->setDuration(1000);
//          animation2->setStartValue(1);
//          animation2->setEndValue(0);
//          animation2->start();
//          connect(animation2, SIGNAL(finished()), this, SLOT(close()));

}

void Wenshidu::on_NEWButton_clicked()
{    //实时监听
    io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Txs1));
     QString wenduz=FrameParse::instance()->wenduz;
     QString wendux=FrameParse::instance()->wendux;
     QString shidu=FrameParse::instance()->shidu;
     qDebug()<<"实时的："<<wenduz;
     qDebug()<<"实时的:"<<wendux;
     qDebug()<<"实时的:"<<shidu;
     paneSave::instance()->wenshidu->ui->WSDlabel->setText("\n\n"+tr("   实时温度:")+wenduz+"."+wendux+"℃\n\n\r"+
                                                           tr("  实时湿度:")+shidu+"%");
//     paneSave::instance()->wenshidu->ui->WSDlabel->setText();

//     paneSave::instance()->widget->ui->
//     Widget* widget=new Widget(this);
//     widget->wsd->ui->WSDlabel->setText(wendu+shidu);






}
