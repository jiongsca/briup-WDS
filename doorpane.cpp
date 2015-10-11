#include "doorpane.h"
#include "ui_doorpane.h"
#include"widget.h"
#include"panesave.h"
#include"frameparse.h"

/*加发送帧以及光敏的帧的东西留到最后来做*/
//char *MKbg[]={":/source/22.1.jpg"};
char *TCbg4[]={":/source/eixt.png"};
//showtime图的大小，这些事那个图的参数，这是不能改动的
const int w_widget = 221;
const int h_widget = 71;
const int space_widget = 90;

Doorpane::Doorpane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doorpane)
{
    ui->setupUi(this);

    paneSave::instance()->m_pBtnAnima = new QToolButton(this);
    //设置提示信息

    //设置ToolButton图像
    //初始化的时候就设置那个按键的图 这个按键要重写啊
   SetBtnImage(paneSave::instance()->m_pBtnAnima,":/source/showtime.png");

   connect(paneSave::instance()->m_pBtnAnima,SIGNAL(clicked()),this,SLOT(SetCloseShow()));

   paneSave::instance()->m_pProAnima= new QPropertyAnimation(paneSave::instance()->m_pBtnAnima,"geometry");

    paneSave::instance()->m_pSignalMapper = new QSignalMapper(this);
    //加一个动态的效果
    paneSave::instance()->animation->setDuration(1000);
    paneSave::instance()->animation->setStartValue(0);
    paneSave::instance()->animation->setEndValue(1);
    paneSave::instance()->animation->start();
    this->ui->TClabel->setStyleSheet(tr("background-image:url(%1)").arg(TCbg4[0]));
    connect(&Dtimer,SIGNAL(timeout()),this,SLOT(open()));//连接动画效果
    connect(&Jtimer,SIGNAL(timeout()),this,SLOT(sensiLight()));//定时器发帧啊
    this->ui->DOORlabel->setStyleSheet("background-image:url(:/source/22.1.jpg);");
}

Doorpane::~Doorpane()
{
    delete ui;
}
//设置按钮图像以及透明
void Doorpane::SetBtnImage(QToolButton *pBtn,const QString &str)
{
    pBtn->setStyleSheet("QToolButton{border:0px;}");
    pBtn->resize(w_widget,h_widget);
    pBtn->setIconSize(QSize(w_widget,h_widget));
    QPixmap objPixmap(str);
    pBtn->setIcon(QIcon(objPixmap));
    pBtn->setMask(objPixmap.mask());
}
//槽函数--动画设置
void Doorpane::SetAnimation()
{
    //如果状态为Running，则停止动画
    if(paneSave::instance()->m_pProAnima->state()==QPropertyAnimation::Running)
    {
        paneSave::instance()->m_pProAnima->stop();
    }
    //设置新的动画
  paneSave::instance()->m_pProAnima->setDuration(3000);
  paneSave::instance()->m_pProAnima->setStartValue(QRect(0, 0, w_widget, h_widget));
  paneSave::instance()->m_pProAnima->setEndValue(QRect(width()-w_widget,height()-h_widget,w_widget,h_widget));
  paneSave::instance()->m_pProAnima->setEasingCurve(QEasingCurve::OutBounce);
  paneSave::instance()->m_pProAnima->start();
}
//窗口大小改变事件
void Doorpane::resizeEvent(QResizeEvent *event)
{

   paneSave::instance()->m_pBtnAnima->move(0,30);
    QWidget::resizeEvent(event);
}

//这是点击进入门口的时候按钮的事件,如果要是RFID模块可以就用那个进入，不用这个按钮了
void Doorpane::on_JRButton_clicked()
{


//    Widget* w=new Widget(this);
//    w->show();

     Dtimer.start(500);
     //因为这里在显示场景的UI面板之后不需要你去回跳了，所以你就只需要就是覆盖掉这个doorUI面板就行了

}
//这里是光敏的效果的灯，但是现在是先点击开光 到时候用帧来改变吧
 int i=0;//点击按钮的变化
void Doorpane::on_DGButton_clicked()//要是用了光敏千万不要去点击那个开灯的按钮 不然就乱了
{      //这里要做成帧的判断
      if(i%2==0){
        this->ui->DOORlabel->setStyleSheet("background-image:url(:/source/11.1.jpg);");
        i++;}
           else{
          this->ui->DOORlabel->setStyleSheet("background-image:url(:/source/22.1.jpg);");
           i++;}
}
   int count=22;//这里是光敏开关的方法，这个和上面哪个只能留一个 因为大部分的场景特效是他写的，必须要和他商讨啊，还要有一个不断发帧的函数
void Doorpane::Sensi_Light(bool on_off){

    bool flag=false;//这个值要根据光敏返回的值去设置是否要关还是要开什么的 如果要是用定时器做的话，一定要注意关闭帧啊
    flag=on_off;
    qDebug()<<"flag========"<<flag;
    if(flag){
     this->ui->DOORlabel->setStyleSheet("background-image:url(:/source/11.1.jpg);");
      qDebug()<<"已经开灯了！！";
       count=11;}
         else{
        this->ui->DOORlabel->setStyleSheet("background-image:url(:/source/22.1.jpg);");
         qDebug()<<"已经关灯了！！";
        count=22;}
}
//这是光敏发帧监听的函数
void Doorpane::sensiLight(){
  //监听的时间之内一直发帧
 io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Sen_Light));
}
//这是动画演示门口打开的模块
int a=1;
void Doorpane::open()
{
     a++;
if(a<=7){//共用一个i这个问题要注意
    this->ui->DOORlabel->setStyleSheet(tr("background-image:url(:/source/%1.%2.jpg)").arg(count).arg(a));
   }

//else if(i%2==1&&a<=7){
//    this->ui->DOORlabel->setStyleSheet(tr("background-image:url(:/source/11.%1.jpg)").arg(a));
//}
else{
    // 不动画的时候就可以跳到一个新的面板测试
    //这是第一次new widget
    //   paneSave::instance()->door->hide();
       Dtimer.stop();//这个定时器一定要关，不然之后的面板会出问题的
       Jtimer.stop();//这个定时器一定要关，不然之后的面板也会有问题的
       paneSave::instance()->widget=new Widget(this);
       paneSave::instance()->widget->show();
             }
}
  //刷卡的内容  RFID发送和接收帧的模块
void Doorpane::on_SKButton_clicked()
{

}

void Doorpane::on_EXITButton_clicked()
{
    QApplication* app;
    app->exit(0);
    //关闭的特效
//    paneSave::instance()->animation->setDuration(1000);
//    paneSave::instance()->animation->setStartValue(1);
//    paneSave::instance()->animation->setEndValue(0);
//    paneSave::instance()->animation->start();
//    connect(paneSave::instance()->animation, SIGNAL(finished()), this, SLOT(close()));
}
//点击门铃的按钮
void Doorpane::on_MLButton_clicked()
{
    //蜂鸣器的帧
  io::instance()->sendData(FrameParse::instance()->generateFrame(FrameParse::instance()->Sound));

}

  //真是那个光敏的效果
// int j=0;
void Doorpane::on_GMZSButton_clicked()
{

   //光敏监听开始
//    j++;
//    if(j%2==1){
      Jtimer.start(500);
      //第一次点的时候就有一个动画，第二次点就不会了
      this->SetAnimation();
//    }else{
//     Jtimer.stop();

//    }

}
void Doorpane::SetCloseShow(){
    //关闭定时器，便可以
    Jtimer.stop();

}
