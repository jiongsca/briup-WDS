#ifndef WLECOMEPANE_H
#define WLECOMEPANE_H
#include<QApplication>
#include<QWidget>
#include<QColor>
#include<QPixmap>
#include<QPropertyAnimation>



namespace Ui {
class WlecomePane;
}

class WlecomePane : public QWidget
{
    Q_OBJECT

public:
    explicit WlecomePane(QWidget *parent = 0);
    ~WlecomePane();

signals:

//    void finished();


private slots:
    void on_JRXTButton_clicked();

    void on_TCButton_clicked();

    void on_EXITButton_clicked();

private:
    Ui::WlecomePane *ui;
//      Widget* widget;
     QColor* mainColor;
     QColor* whiteColor;
     QColor* backgroundColor;
//     QPropertyAnimation *animation ;





};

#endif // WLECOMEPANE_H
