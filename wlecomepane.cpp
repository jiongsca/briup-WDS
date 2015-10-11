#include "wlecomepane.h"
#include "ui_wlecomepane.h"
#include"widget.h"
#include"doorpane.h"
#include"panesave.h"



char *HYbg[]={":/source/HYbg.jpg"};//这个数组里面存的是char* 指针的对象 就是个字符串咯
char *TCbg1[]={":/source/eixt.png"};

WlecomePane::WlecomePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WlecomePane)
{
    ui->setupUi(this);
    //程序的名字修改
    setWindowTitle(tr("Homie"));
   //背景透明的设置

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->ui->HYlabel->setStyleSheet(tr("background-image:url(%1)").arg(HYbg[0]));
    this->ui->TClabel->setStyleSheet(tr("background-image:url(%1)").arg(TCbg1[0]));
    //界面出现的动画效果
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    //在这里第一次的new 了animation后面就不要再new了
    paneSave::instance()->animation=new QPropertyAnimation(this,"windowOpacity");
//    animation=new QPropertyAnimation(this, "windowOpacity");
    paneSave::instance()->animation->setDuration(1000);
    paneSave::instance()->animation->setStartValue(0);
    paneSave::instance()->animation->setEndValue(1);
    paneSave::instance()->animation->start();

}

WlecomePane::~WlecomePane()
{
    delete ui;
}
//进入系统

void WlecomePane::on_JRXTButton_clicked()
{
//   Widget* widget=new Widget(this);//显示新的UI界面
//    widget->show();

//   Doorpane* door=new Doorpane(this);
//     door->show();
    io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Points));

    //只能new一次 这是第一次 doorpane


     paneSave::instance()->door=new Doorpane(this);//只能一次
     paneSave::instance()->door->show();
//      paneSave::instance()->wlecomepane->hide();

}
  //退出
void WlecomePane::on_TCButton_clicked()
{
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
          paneSave::instance()->animation->setDuration(1000);
          paneSave::instance()->animation->setStartValue(1);
          paneSave::instance()->animation->setEndValue(0);
          paneSave::instance()->animation->start();
          connect(paneSave::instance()->animation, SIGNAL(finished()), this, SLOT(close()));
//       QApplication* app;
//           app->exit(0);
}
 //整体的退出按钮
void WlecomePane::on_EXITButton_clicked()
{
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
           paneSave::instance()->animation->setDuration(1000);
           paneSave::instance()->animation->setStartValue(1);
           paneSave::instance()->animation->setEndValue(0);
           paneSave::instance()->animation->start();
            connect(paneSave::instance()->animation, SIGNAL(finished()), this, SLOT(close()));
//    QApplication* app;
//        app->exit(0);

}
