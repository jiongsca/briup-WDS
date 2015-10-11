#ifndef PANESAVE_H
#define PANESAVE_H
#include"wenshidu.h"
#include"wlecomepane.h"
#include"widget.h"
#include"doorpane.h"

#include <QWidget>
#include<QPropertyAnimation>
#include<QApplication>


class paneSave {

public:
    explicit paneSave();
    ~paneSave();

    static paneSave* instance();
      Widget* widget;
      WlecomePane* wlecomepane;
      Wenshidu* wenshidu;
      Doorpane* door;
      QPropertyAnimation* animation;//第一个
      QToolButton *m_pBtnAnima;
      QPropertyAnimation *m_pProAnima;//第二个
      QSignalMapper *m_pSignalMapper;


//    LedPane *ledPane;
//    VibratePane *vibratePane;
//    MotorPane *motorPane;
//    KbdPane *kbdPane;
//    LcdPane *lcdPane;
//    BuzzerPane *buzzerPane;
//    LightPane *lightPane;
//    InfrarPane *infrarPane;
//    DhtPane *dhtPane;
//    RfidPane *rfidPane;
//    TempPane *tempPane;
//    CpuAPane *cpuAPane;
//    CpuBPane *cpuBPane;

private:
    static paneSave *paneSaver;
};


#endif // PANESAVE_H
