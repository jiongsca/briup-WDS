#ifndef WENSHIDU_H
#define WENSHIDU_H

#include <QWidget>
//#include"widget.h"
#include"ui_widget.h"
#include<QApplication>
#include<QColor>
#include<QPropertyAnimation>
#include<QLCDNumber>
#include<QTimer>
#include<QTime>



namespace Ui {
class Wenshidu;
}

class Wenshidu : public QWidget
{
    Q_OBJECT

public:
    explicit Wenshidu(QWidget *parent = 0);
    ~Wenshidu();
     QTimer *Xtimer;
     QTimer *Wtimer;

//    Ui::Wenshidu *ui;

private slots:
    void on_TCButton_clicked();

    void on_EXITButton_clicked();

    void on_NEWButton_clicked();

    void showtime();





private:
    Ui::Wenshidu *ui;


//   QPropertyAnimation* animation2;


};

#endif // WENSHIDU_H
