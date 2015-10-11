#include "widget.h"
#include <QApplication>
#include"wlecomepane.h"
#include"wenshidu.h"
#include"io.h"
#include"frameparse.h"
#include<QDebug>
#include"panesave.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"1";
    if(char(0xff)==char(char(0xff))){
        qDebug()<<"对的";
    }
    io::instance()->Open();
      qDebug()<<"2";
      //这就是第一次new了 不能new了
//    paneSave::instance()->wlecomepane=new WlecomePane();
//    paneSave::instance()->wlecomepane->show();
      WlecomePane w;//开始这个UI面板没有加进去因为没有必要加进去了呗
      w.show();
      qDebug()<<"3";
    return a.exec();
}
