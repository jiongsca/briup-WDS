#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QCloseEvent>
#include"wlecomepane.h"
#include"panesave.h"
#include"ui_wlecomepane.h"
#include"wenshidu.h"
#include"ui_wenshidu.h"

/*这个UI界面剩下的就是发帧调试了呗*/

int pixs_one[]={1,2,3,4,5,6,7};//背景的切换的图片调用数 4.左灯开1 3.右灯开2 1.全灭 2.全开
//char *CJbg1[]={":/source/home_close1.jpg",":/source/home_close2.jpg",
//              ":/source/home_close3.jpg",":/source/home_close4.jpg",
//              ":/source/home_close5.jpg",
//              ":/source/home_close6.jpg",":/source/home_close7.jpg",":/source/home_closeall.jpg"};
//char *DGbg[]={":/source/light_left.jpg",":/source/light_right.jpg",":/source/light_all.jpg",":/source/home_closeall.jpg"};
char *TCbg2[]={":/source/eixt.png"};
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
  ui->setupUi(this);
  //加一开启的特效
  paneSave::instance()->animation->setDuration(1000);
  paneSave::instance()->animation->setStartValue(0);
  paneSave::instance()->animation->setEndValue(1);
  paneSave::instance()->animation->start();
//  this->ui->CJlabel->setStyleSheet(tr("background-image:url(%1)").arg(CJbg1[0]));
  this->ui->TClabel->setStyleSheet(tr("background-image:url(%1)").arg(TCbg2[0]));
  currentIndex=0;
  isleftOn=false;
  isrightOn=false;
  this->ui->CJlabel->setStyleSheet("background-image:url(:/source/1.1.jpg);");

}

Widget::~Widget()
{
    delete ui;

}

int index=1;//记录次数

//还要重写啊 如果我哪里要是没有注释的话 说明那里就不需要去实例了 说明可能在哪已经实例了一遍
void Widget::setBackground(){
   //这个是退出温湿度UI界面之后显示之前的场景的UI界面不变
  this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.%2.jpg)").arg(pixs_one[currentIndex]).arg(index));
}

void Widget::paintEvent(QPaintEvent *){
//这个抽象函数声明出来就行这个是一定要声明出来的


}
//int cuntIndex1=0;
 //左灯事件
void Widget::on_DG1Button_clicked()
{
//      cuntIndex1++;//计数器累加


//     if(cuntIndex1%2==0){
//         this->ui->CJlabel->setStyleSheet(tr("background-image:url(%1)").arg(DGbg[3]));
//          io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_off1));
//     }else{
//         this->ui->CJlabel->setStyleSheet(tr("background-image:url(%1)").arg(DGbg[0]));

//            io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_on1));
//     }
    if(!isrightOn){
        if(!isleftOn){  index=4;
        this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.4.jpg)").arg(pixs_one[currentIndex]));
          io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_on1));
            qDebug()<<"开了左灯";
        }
        else{   index=1;
            this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.1.jpg)").arg(pixs_one[currentIndex]));
            io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_off1));

          qDebug()<<"全关灯了";
        }
    }else{
        if(!isleftOn){  index=2;
            this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.2.jpg)").arg(pixs_one[currentIndex]));
             io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_on1));

           qDebug()<<"全开灯了";
        }
        else {   index=3;
            this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.3.jpg)").arg(pixs_one[currentIndex]));
            io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_off1));
          qDebug()<<"开了右灯";
        }
    }

//    repaint();
   isleftOn=!isleftOn;


}
// int cuntIndex2=0;
//右灯事件
void Widget::on_DG2Button_clicked()
{
//      cuntIndex2++;//计数器累加
//   if(cuntIndex2%2==0){
//       this->ui->CJlabel->setStyleSheet(tr("background-image:url(%1)").arg(DGbg[3]));


//   }else{

//       this->ui->CJlabel->setStyleSheet(tr("background-image:url(%1)").arg(DGbg[1]));
//   }
    if(!isleftOn){
        if(!isrightOn){   index=3;
        this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.3.jpg)").arg(pixs_one[currentIndex]));
       io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_on2));
         qDebug()<<"1开了右灯";
        }
        else{  index=1;
            this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.1.jpg)").arg(pixs_one[currentIndex]));

          io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_off2));
         qDebug()<<"1全关了灯了";
        }
    }else{
        if(!isrightOn){   index=2;
            this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.2.jpg)").arg(pixs_one[currentIndex]));

            io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_on2));
      qDebug()<<"1全开了灯";
        }
        else {    index=4;
           this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.4.jpg)").arg(pixs_one[currentIndex]));
         io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Light_off2));
         qDebug()<<"1开了左灯";
        }
    }
//    repaint();
    //isleftOn=!isleftOn;
    isrightOn=!isrightOn;

}
//左窗帘
void Widget::on_CLButton_clicked()
{
    currentIndex--;
         if(currentIndex<0){
            currentIndex=0;
            //timer->stop();
            return;
        }
            this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.%2.jpg)").arg(pixs_one[currentIndex]).arg(index));
            io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Motor1));//按一次正转90度
//            repaint();

}
  //右窗帘
void Widget::on_CL2Button_clicked()
{
    currentIndex++;
          if(currentIndex>6){
              currentIndex=6;
              //timer->stop();
              return;
          }

           this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.%2.jpg)").arg(pixs_one[currentIndex]).arg(index));
           io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Motor4));//按一次翻转90度
//          repaint();
}

//显示温湿度的UI
//int i=0;
void Widget::on_WSDButton_clicked()
{          //这是第一次new wenshidu
          paneSave::instance()->wenshidu=new Wenshidu(this);
       io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Txs1));
          paneSave::instance()->wenshidu->show();
          //开启时间日期的定时器
          paneSave::instance()->wenshidu->Xtimer->start(1000);
          paneSave::instance()->wenshidu->Wtimer->start(500);

         QString wenduz=FrameParse::instance()->wenduz;//这个要按刷新键
         QString wendux=FrameParse::instance()->wendux;//这个要按刷新键
         QString shidu=FrameParse::instance()->shidu;//这个要按按刷新键
//       wsd=new Wenshidu(this);
//       wsd->show();

       qDebug()<<"在这里"<<wenduz;
       qDebug()<<"在这里"<<wendux;
       qDebug()<<"在这里"<<shidu;
//       wsd->ui->WSDlabel->setText(shidu+"%"+"  "+wendu+"℃");


//       i++;
//           if(i%2==1){
//            this->ui->CJlabel->setStyleSheet("background-image:url(:/tem.png);");}//这就不能要 要改或者舍弃
//           else{
//               this->ui->CJlabel->setStyleSheet(tr("background-image:url(:/source/%1.%2.jpg)").arg(pixs_one[currentIndex]).arg(index));
//           }

}




//void Widget::on_EXIT1Button_clicked()
//{
//    QApplication* app;
//    app->exit(0);

//    //    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
////                animation1->setDuration(1000);
////                animation1->setStartValue(1);
////                animation1->setEndValue(0);
////                animation1->start();
////                connect(animation1, SIGNAL(finished()), this, SLOT(close()));
//}
//退出按钮
void Widget::on_EXITButton_clicked()
{    //退出的特效
//    paneSave::instance()->animation->setDuration(1000);
//    paneSave::instance()->animation->setStartValue(1);
//    paneSave::instance()->animation->setEndValue(0);
//    paneSave::instance()->animation->start();
//    connect(paneSave::instance()->animation, SIGNAL(finished()), this, SLOT(close()));
    QApplication* app;
    app->exit(0);
//             animation1->setDuration(1000);
//                   animation1->setStartValue(1);
//                   animation1->setEndValue(0);
//                   animation1->start();
//                   connect(animation1, SIGNAL(finished()), this, SLOT(close()));

}








