#include "frameparse.h"
#include"io.h"
#include"wenshidu.h"
#include"widget.h"
#include"wlecomepane.h"
#include"panesave.h"




FrameParse* FrameParse::frameparese = NULL;
FrameParse::FrameParse()

{

}

FrameParse::~FrameParse()
{


}
/*单例模式*/
FrameParse* FrameParse::instance(){
    if(FrameParse::frameparese==NULL){
        FrameParse::frameparese=new FrameParse;
    }
    return FrameParse::frameparese;

}
/*生成一般发送的帧*/
QByteArray FrameParse::generateFrame(char content[]) {
    QByteArray frame;
    frame.append(content);
    return frame;
}

/*生成一般发送的帧*/
QByteArray FrameParse::generateFrame(QByteArray content) {
    QByteArray frame;
    frame.append(content);
    return frame;
}
/**
 * 判断数据是否为帧
 * @brief FrameParse::isFrame
 * @param data
 * @return
 */
bool FrameParse::isFrame(QByteArray data) {
    return data.at(FHEAD) == FHEAD && data.length() == 32;
}

/**
 * getter
 * @brief FrameParse::lastFrame
 * @return
 */
QByteArray FrameParse::lastFrame() {
    return this->_lastFrame;
}


/**
 * 计算待发送帧的校验位
 * @brief FrameParse::calculateParity
 * @param frame 待计算的帧
 */
char FrameParse::calculateParity(QByteArray frame, bool hasParity) {//在一些你不确定一定是按照你的意愿走的函数你就先埋一个QDebug就行为了检测
    char parity = frame.at(0);
    for(int i=1; i < 30 - int(hasParity); i ++) {//第29是校验位
        parity ^= frame.at(i);


    }
    QString party=QString::number(quint8(parity), 16);
    qDebug()<<"计算出了校验位了"<<party;
    return parity;
}

/**
 * 获得数据
 * @brief FrameParse::calculateParity
 * @param wende shidu
 */
void FrameParse::setWenShiDu(QString wenduz,QString wendux, QString shidu){

    this->wenduz=wenduz;
    this->wendux=wendux;
    this->shidu=shidu;
}

/**
 * setter
 * @brief FrameParse::setLastFrame
 * @param data
 */
void FrameParse::setLastFrame(QByteArray data) {
    this->_lastFrame = data;
}
/**
 * 解析接收到的响应帧
 * @brief FrameParse::parseFrame
 * @param frame 待解析的帧
 */
void FrameParse::parseFrame(QByteArray frame) {//字符是这样的char a='k'; 字符串是这样char* k="kkk";
    //校验校验校验位
    if(char(frame.at(PARITY)) != char(calculateParity(frame, true))) {
        qDebug("校验失败，数据可能丢失，正在重发上一帧请求...");
        io::instance()->sendData(lastFrame());
        return;
    }
    /*else {
        if(frame.at(TYPE) == TEST) {
            qDebug() << "收到测试帧，信道畅通";
            return;
        }*/
//         qDebug()<<"传来的鬼东西："<<frame;
        qDebug() << "校验成功，正在解析帧" << frame.toHex() << "....";
         char light_data=frame.at(3);
         char motor_data=frame.at(4);
         char wsdu1=frame.at(5);
         char wsdu2=frame.at(6);
         char pioints=frame.at(7);
         char sensiv_data=frame.at(8);
         char sound=frame.at(9);//蜂鸣器的判断位置
         char wdx_data=frame.at(26);//温度小数部分
         char sd_data=frame.at(27);
         char wd_data=frame.at(28);//温度整数部分
         char sensi_light=frame.at(26);//光敏的数据部分

         //开灯 其实还是我们去发帧就行了 这里接收下来 我只是看看 我做了这个动作了没有
       if(light_data!=char(0x00)){

           if(light_data==char(0x01)){
                        qDebug()<<"开了第1个灯！！！";
                    }

                     if(light_data==char(0x02)){
                        qDebug()<<"开了第2个灯！！！";
                    }

                    if(light_data==char(0x03)){
                        qDebug()<<"开了第3个灯！！！";
                    }

                    if(light_data==char(0x04)){
                        qDebug()<<"开了第4个灯！！！";
                    }

                    if(light_data==char(0x05)){
                        qDebug()<<"开了第5个灯！！！";
                    }

                    if(light_data==char(0x06)){
                        qDebug()<<"开了第6个灯！！！";
                    }

                    if(light_data==char(0x07)){
                        qDebug()<<"开了第7个灯！！！";
                    }

                    if(light_data==char(0x08)){
                        qDebug()<<"开了第8个灯！！！";
                    }
                    //关灯的返回
                    if(light_data==char(0x09)){
                        qDebug()<<"关了第1个灯！！！";
                    }

                     if(light_data==char(0x0a)){
                        qDebug()<<"关了第2个灯！！！";
                    }

                    if(light_data==char(0x0b)){
                        qDebug()<<"关了第3个灯！！！";
                    }

                    if(light_data==char(0x0c)){
                        qDebug()<<"关了第4个灯！！！";
                    }

                    if(light_data==char(0x0d)){
                        qDebug()<<"关了第5个灯！！！";
                    }

                    if(light_data==char(0x0e)){
                        qDebug()<<"关了第6个灯！！！";
                    }


                    if(light_data==char(0x0f)){
                        qDebug()<<"关了第7个灯！！！";
                    }

                    if(light_data==char(0x10)){
                        qDebug()<<"关了第8个灯！！！";
                    }

       }

         //温湿度1
       else if(wsdu1==char(0x01)){
//             quint8 a=quint8(frame.at(27));
//             quint8 b=quint8(frame.at(28));
//             QString sd_str=QString(a);
//             QString wd_str=QString(b);
              QString shidu=QString::number(int(frame.at(27)));
              QString wenduz=QString::number(int(frame.at(28)));
              QString wendux=QString::number(int(frame.at(26)));
//             qDebug()<<"接收了湿度！！！"<<int(frame.at(27));
//             qDebug()<<"接收了温度！！！"<<int(frame.at(28));
             qDebug()<<"湿度"<<shidu;
             qDebug()<<"温度整数"<<wenduz;
             qDebug()<<"温度小数"<<wendux;
             qDebug()<<"输出"<<shidu+"%"+'/n'+wenduz+"."+wendux+"℃";
             //处理里面的数据在这之后
//             Wenshidu* wsd;
//             wsd=new Wenshidu();
//             wsd->ui->WSDEdit->insertPlainText(shidu);
//             wsd->ui->WSDEdit->setText(shidu);
//             qDebug()<<"做了么！！";
               this->setWenShiDu(wenduz,wendux,shidu);

         }
       //步进马达
      else if(motor_data==char(0x01)||motor_data==char(0x04)){//只用第一个和第四个，所以只判读这两个就行了
           qDebug()<<"接收了马达！！！";


       }
//         //温湿度2
//         else if(wd_data!=char(0x00)){//这里有点问题，因为我默认了这个温度是大于0的，要是小于零的话这个代码就错了
//             qDebug()<<"接收了温湿度！！！";
//             //处理里面的数据在这之后

//         }

         //8*8点阵图
        else if(pioints==char(0x01)){
             qDebug()<<"接收了点阵了！！！";
             //处理里面的数据在这之后
         }
       //光敏的接收
       else if(sensiv_data==char(0x01)){
           qDebug()<<"接收了光敏了！！！";
           //处理里面的数据在这之后
           if(sensi_light==char(0x01)){
               //这里要开灯
                 paneSave::instance()->door->Sensi_Light(true);
                 qDebug()<<"要开灯啦！！！！！";

           }
           else if(sensi_light==char(0x00)){
              //这里要关灯

             paneSave::instance()->door->Sensi_Light(false);
             qDebug()<<"要关灯啦！！！！！";

           }
       }
       //蜂鸣器的接收
       else if(sound==char(0x01)){
            qDebug()<<"接收了蜂鸣器了！！！";
            //处理里面的数据在这之后
        }

       else{
                   qDebug() << "响应错误，数据可能丢失，正在重发上一帧请求...";
                   io::instance()->sendData(lastFrame());
                   return;
        }

}
