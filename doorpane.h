#ifndef DOORPANE_H
#define DOORPANE_H
#include<QDebug>
#include<QApplication>
#include<QPropertyAnimation>
#include<QTimer>
#include<QTime>
#include<QToolButton>
#include<QBitmap>
#include<QPixmap>
#include<QPainter>
#include<QSignalMapper>
#include<QWidget>



namespace Ui {
class Doorpane;
}

class Doorpane : public QWidget
{
    Q_OBJECT

public:
    explicit Doorpane(QWidget *parent = 0);
    ~Doorpane();
    void Sensi_Light(bool on_off);
protected:   //估计会有问题，如果是保护的话

    //窗口大小改变事件
   void resizeEvent(QResizeEvent *event);



private slots:
    void on_JRButton_clicked();

    void on_SKButton_clicked();

    void on_DGButton_clicked();

    void on_EXITButton_clicked();

    void open();//开门函数

    void sensiLight();//光敏发帧的函数

    void on_MLButton_clicked();

    void on_GMZSButton_clicked(); //这个就是那个点击光敏的那个函数 showtime

    void SetAnimation();

    void SetCloseShow();

private:
    Ui::Doorpane *ui;
     QTimer   Dtimer;
     QTimer   Jtimer;
     //设置按钮图像以及透明
     void SetBtnImage(QToolButton *pBtn,const QString &str);
     //建立信号和槽函数的连接
     void SetSignalSlot();



};

#endif // DOORPANE_H
