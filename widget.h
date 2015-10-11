#ifndef WIDGET_H
#define WIDGET_H

#include<QWidget>
#include<QPainter>
#include<QRect>
#include<QColor>
#include<QPixmap>
#include<QApplication>
#include"frameparse.h"
#include"io.h"
#include<QPropertyAnimation>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *);//Qt当中的绘图事件，在父类里面是一个虚函数所以你必须去重写 类似java的抽象函数一样
//    Ui::Widget *ui;

    void setBackground();//一改：头文件 二改：本源文件 三改：引用的源文件

private slots:
    void on_DG1Button_clicked();

    void on_CLButton_clicked();

    void on_WSDButton_clicked();

    void on_DG2Button_clicked();

    void on_EXITButton_clicked();


    void on_CL2Button_clicked();

private:
    Ui::Widget *ui;
    QPixmap pixmap;
    int     currentIndex;
    bool    isleftOn;
    bool    isrightOn;

//    QPropertyAnimation *animation1;



};

#endif // WIDGET_H
