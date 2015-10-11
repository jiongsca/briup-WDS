#include "io.h"
#include<QMessageBox>
#include<QSerialPortInfo>
#include<QTime>
io* io::iothing=NULL;//这个就是静态成员变量的调用:: iothing是一个对象

io::io(){

    currentPort=0;
    isOpen=false;
//    isReceivied=false;
    ports=new QVector<QString>;
    port=new QSerialPort;
    Timer=new QTimer(this);

    //扫描所以可用的串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            qDebug() << "扫描到串口：" << info.portName();
            ports->append(info.portName());

            //如果没有扫描到串口
             if(ports->isEmpty()){

                 QMessageBox::information(0,tr("串口初始化失败"),tr("没有串口接入,请接入串口"),QMessageBox::Ok);

             }else{
            connect( this->Timer, SIGNAL(timeout()), this, SLOT(readData()) );

             }



}


}
io::~io(){//当不需要的时候就把这些对象和成员进行垃圾回收
         delete port;
         delete ports;
         delete Timer;
         delete io::iothing;


  }
QSerialPort::BaudRate io::getBaud()
{
    int baud=57600;
    return(QSerialPort::BaudRate)(baud);
}

QSerialPort::DataBits io::getDataBits()
{      int databits=8;
    return(QSerialPort::DataBits)(databits);
}

QSerialPort::Parity io::getParity()
{
    int index = 0;
    if(0==index)
    {

        return QSerialPort::NoParity;
    }else if(1==index){
        return QSerialPort::EvenParity;
    }else if(2==index){
        return QSerialPort::OddParity;
    }else if(3==index){
        return QSerialPort::SpaceParity;
    }else if(4==index){
        return QSerialPort::MarkParity;
    }
    return QSerialPort::UnknownParity;

}

QSerialPort::StopBits io::getStopBit()
{
    int index = 0;
    if (0==index){
        return QSerialPort::OneStop;
    }else if(1==index){
        return QSerialPort::OneAndHalfStop;
    }else if(2==index){
        return QSerialPort::TwoStop;
    }
    return QSerialPort::UnknownStopBits;
}
/**
 * 单例模式创建
 *
 */

io* io::instance(){//没有加同步锁还是会有问题出现
 if(io::iothing==NULL){
  io::iothing=new io;
 }
 return io::iothing;

}

/**
 * 打开串口函数
 *
 */
void io::Open(){

if(isOpen){
    qDebug()<<"执行了！isOpen";
    return;
}
if(ports->isEmpty()){//这是为了在没查串口也可以打开程序
    qDebug()<<"执行了ports->isEmpty()";
    return;
}
port->setPortName(ports->at(currentPort));
while(!isOpen){
     qDebug()<<"执行了while(!isOpen)";

        if(!port->open(QIODevice::ReadWrite)){
            qDebug() <<"串口打开失败";
            exit(0);


        }
      //成功打开了串口，设置参数
        port->setBaudRate(QSerialPort::Baud57600);
        isOpen=true;

        qDebug() << "串口 " << port->portName() << " 打开成功";
                    qDebug() << "开始接收数据....";//qDebug这个就类似于输出诊断信息就类似输出语句一样咯
                    Timer->start(INTERVAL);

}

}
/**
 * 串口关闭
 *
 */

 void io::close(){
  if(!isOpen){

      return;

  }
  Timer->stop();
  port->close();
  isOpen=false;
  qDebug()<<"串口关闭";


}
 /**
  * 读取数据的槽函数 还要重新修改一下
  *
  */
 void io::readData(){

     if(!isOpen){
         qDebug()<<"串口未打开，无法读取数据";
         return;

     }
     QByteArray data=port->readAll();//读取串口传输过来的数据 并且存在直接数组对象中

     if(data.isEmpty()){
         return;
     }
     //要是有数据来了
     qDebug()<<"来了来了";
    qDebug()<<"接收数据："<<data.toHex();//转成十六进制
    //QQueue是一个容器类作用类似java 的Arrylist<> 队列或者是集合
  QQueue<QByteArray> *parseQueue = new QQueue<QByteArray>();//解析队列，存放本次读到的所有帧

  for(int i=0;i<data.length();i++){
      //开始从帧头解析这个队列里面存放的帧了
             if(data.at(i)==char(FHEAD)){//帧头解析 at()是QByteArray提供的一个只读的操作
             QByteArray  buffer;//队列的缓冲区
             //读到帧头就开始往后读七位了
             int j;
           if(data.length()-i<32){
             io::instance()->sendData(FrameParse::instance()->lastFrame());//调用帧工具的单例模式返回的对象去调用去写入数据
             break;
          }
          for(j=i;j<i+32;j++){
              if(j>=data.length()){
                  break;
              }
                  buffer.append(data.at(j));

          }
            i+=31;
            qDebug()<<"读取到帧："<<buffer.toHex();
           if(!buffer.isEmpty()){
               parseQueue->enqueue(buffer);//把buffer加入队列

           }

      }
  }
//  qDebug()<<"无法接收"<<isReceivied;
//  if(isReceivied){//这里做的是要是不想接收的话,那么就不做解析的工作了
    //只要有数据来就去解析帧
     while(!parseQueue->isEmpty()){
         //解读本次读到的所有帧
         FrameParse::instance()->parseFrame(parseQueue->dequeue());//把队列里面的每一个对象拿出来去每一个帧

     }

//  }



  }

 /**
  * 发送数据的槽函数
  *
  */

 void io::sendData(QByteArray data){
     if(!isOpen){

         qDebug("未打开串口，无法发送数据");
         return;


     }
     if(data.isEmpty()){
          qDebug()<<"是空的么？";
         return;
     }
      qDebug()<<"QByteArray::fromHex(data)"<<QByteArray::fromHex(data);
     port->write(QByteArray::fromHex(data));
     qDebug()<<"发送数据+++++:"<<data;//打印出来我们发了什么数据啊
     //记录上一帧
     FrameParse::instance()->setLastFrame(data);
}

 void io::closeParse(){
     isReceivied=false;//不接收那么就可以关闭解析了啊
 }
void io::openParse(){
    isReceivied=true;
}



