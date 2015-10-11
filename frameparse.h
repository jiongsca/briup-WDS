#ifndef FRAMEPARSE_H
#define FRAMEPARSE_H

#include <QByteArray>
#include<QDebug>

//帧长
#define FLEN 32
//帧头
#define	FHEAD  char(0xAB)  //这里就进行强转是因为0xFF只要是10000000以上就会自动转成补码 那就是负数了 那就错了 强转过来才是11111111才是255

//请求帧的特殊位
#define	HEAD 0//头
#define LIGHT 3//灯光
#define MOTOR 4//马达
#define WSD1 5//温湿度请求数据位
#define WSD2 6 //Lm75a温湿度的请求数据位
#define POINTS 7 //点阵
#define SENSIV 8//光敏
#define SOUND 9//蜂鸣器
#define PARITY 29 //校验
//返回帧的特殊位
#define WD 28 //温度整数位
#define WDL 26//温度小数位
#define SD 27 //湿度



class FrameParse {

public:
    ~FrameParse();
    static FrameParse *instance();
    void parseFrame(QByteArray frame); //解析帧
    //        QByteArray generateFrame(char deviceId, char cmd, char data[]); //根据参数生成帧
    //        QByteArray generateFrame(char content[], int length); //LCD专用内容帧
    //        QByteArray generateFrame(QByteArray content); //LCD专用内容帧
              QByteArray generateFrame(QByteArray content); //现在点灯专用内容帧
              QByteArray  generateFrame(char content[]);//用来生成发送帧
    char calculateParity(QByteArray frame, bool hasParity = 0); //计算校验位
    bool isFrame(QByteArray data);//判断是不是一个完整的帧才选择是不是要接收
    void setLastFrame(QByteArray data);//设置上一帧
    QByteArray lastFrame();//返回上一帧
    void setWenShiDu(QString wenduz,QString wendux,QString shidu);
    //灯开启1-8的请求帧
    const char* Light_on1="ab  1e  0a  01   00 00  0000000000 0000000000  0000000000 0000000000 000000 be 0d 0a";
    const char* Light_on2="AB  1E  0A  02   00 00  0000000000 0000000000  0000000000 0000000000 000000 BD 0d 0a";
    const char* Light_on3="AB  1E  0A  03   00 00  0000000000 0000000000  0000000000 0000000000 000000 BC 0d 0a";
    const char* Light_on4="AB  1E  0A  04   00 00  0000000000 0000000000  0000000000 0000000000 000000 BB 0d 0a";
    const char* Light_on5="AB  1E  0A  05   00 00  0000000000 0000000000  0000000000 0000000000 000000 BA 0d 0a";
    const char* Light_on6="AB  1E  0A  06   00 00  0000000000 0000000000  0000000000 0000000000 000000 B9 0d 0a";
    const char* Light_on7="AB  1E  0A  07   00 00  0000000000 0000000000  0000000000 0000000000 000000 B8 0d 0a";
    const char* Light_on8="AB  1E  0A  08   00 00  0000000000 0000000000  0000000000 0000000000 000000 B7 0d 0a";
    //灯关闭1-8的请求帧
    const char* Light_off1="AB  1E  0A  09   00 00  0000000000 0000000000  0000000000 0000000000 000000 B6 0d 0a";
    const char* Light_off2="AB  1E  0A  0a   00 00  0000000000 0000000000  0000000000 0000000000 000000 B5 0d 0a";
    const char* Light_off3="AB  1E  0A  0b   00 00  0000000000 0000000000  0000000000 0000000000 000000 B4 0d 0a";
    const char* Light_off4="AB  1E  0A  0c   00 00  0000000000 0000000000  0000000000 0000000000 000000 B3 0d 0a";
    const char* Light_off5="AB  1E  0A  0d   00 00  0000000000 0000000000  0000000000 0000000000 000000 B2 0d 0a";
    const char* Light_off6="AB  1E  0A  0e   00 00  0000000000 0000000000  0000000000 0000000000 000000 B1 0d 0a";
    const char* Light_off7="AB  1E  0A  0f   00 00  0000000000 0000000000  0000000000 0000000000 000000 B0 0d 0a";
    const char* Light_off8="AB  1E  0A  10   00 00  0000000000 0000000000  0000000000 0000000000 000000 AF 0d 0a";
    //步进马达的请求帧
     const char* Motor1="AB  1E  0A  00   01 00  0000000000 0000000000  0000000000 0000000000 000000 BE 0d 0a	";  	//正转90度
     const char* Motor2="AB  1E  0A  00   02 00  0000000000 0000000000  0000000000 0000000000 000000 BD 0d 0a" ;            //	正转180度
     const char* Motor3="AB  1E  0A  00   03 00  0000000000 0000000000  0000000000 0000000000 000000 BC 0d 0a";		//正转360度
     const char* Motor4="AB  1E  0A  00   04 00  0000000000 0000000000  0000000000 0000000000 000000 BB 0d 0a	"   ;  	//正转90度
     const char* Motor5="AB  1E  0A  00   05 00  0000000000 0000000000  0000000000 0000000000 000000 BA 0d 0a	"  ;  	//正转180度
     const char* Motor6="AB  1E  0A  00   06 00  0000000000 0000000000  0000000000 0000000000 000000 B9 0d 0a" ; 		//正转360度
    //Lm75a温度+温湿度和时间的请求帧
     const char* Txs1="AB  1E  0A  00   00 01  0000000000 0000000000  0000000000 0000000000 000000   BE  0d 0a";
    // Lm75a温度+时间请求帧
     const char* Txs2="AB  1E  0A  00   00 00  0100000000 0000000000  0000000000 0000000000 00   00  00     BE     0d 0a ";
    //8*8点阵图案请求帧
     const char* Points="AB  1E  0A  00   00 00  0001000000 0000000000  0000000000 0000000000 000000 BE 0d 0a";
     //光敏的请求帧
     const char* Sen_Light="AB  1E  0A  00   00 00  0000010000 0000000000  0000000000 0000000000 00    00   00       BE 0d 0a";
    //蜂鸣器请求帧
     const char* Sound="AB  1E  0A  00  00 00  0000000100 0000000000  0000000000 0000000000 0000   00        BE 0d 0a";
     QString wenduz;//温度整数部分
     QString wendux;//温度小数部分
     QString shidu;//湿度


private:
    explicit FrameParse();
    static FrameParse *frameparese;//这里是头文件宏定义 要是这里就赋值的话到时候调用就会出现再次调用的时候就会这个值的就是空了 最好是在全局变量的情况下去赋NULL值就行
    QByteArray _lastFrame;//上一帧


//    Wenshidu* wsd;



};


#endif // FRAMEPARSE_H
