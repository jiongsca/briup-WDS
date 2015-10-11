#ifndef IO_H
#define IO_H

#include <QObject>
#include <QSerialPort>
#include <QVector>
#include <QQueue>
#include <QTimer>
#include <QDebug>
#include "frameparse.h"
//头文件里面都是宏定义 宏定义里面都是这些还可以加上些库内提供的头文件
const int TIMEOUT = 2000;
const int INTERVAL = 500;

class io : public QObject
{
    Q_OBJECT
public:
    ~io();
    static io* instance();//单例模式 这个函数返回的是io类的指针也就是类似java中的对象 java简化了c++的很多东西
    void Open();//串口打开函数
    void close();//串口关闭函数
    void closeParse();
    void openParse();
    QTimer* Timer;//用*声明为成员的变量的时候 这个是指针是对象 调用其内的方法要用->，如果只是一个变量的话 那就是 .来调用

public slots:

     void readData();//读取帧函数
     void sendData(QByteArray data);//发送数据的函数


private:
   explicit io();
   static io *iothing;//定义一个静态的成员io类的成员 然后后面去实例化是单例模式的 必须之前要是静态的成员
   QQueue<QByteArray> *sendQueue;//发送的队列
   QVector<QString> *ports;//所有识别的串口
   QSerialPort *port;//当前的选择的串口
   int currentPort;//当前打开的串口号
   bool isOpen;//串口是否打开的标志
   bool isReceivied;//接收或者放弃数据
   QSerialPort::BaudRate   getBaud();//获得当前的波特率
   QSerialPort::DataBits   getDataBits();//获得当前的数据位
   QSerialPort::Parity     getParity();//获取当前的校验位
   QSerialPort::StopBits   getStopBit();//获取当前的停止位


};

#endif // IO_H
