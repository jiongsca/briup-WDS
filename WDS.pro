#-------------------------------------------------
#
# Project created by QtCreator 2015-07-25T14:23:40
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WDS
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    io.cpp \
    frameparse.cpp \
    wlecomepane.cpp \
    wenshidu.cpp \
    doorpane.cpp \
    panesave.cpp

HEADERS  += widget.h \
    io.h \
    frameparse.h \
    wlecomepane.h \
    wenshidu.h \
    doorpane.h \
    panesave.h

FORMS    += widget.ui \
    wlecomepane.ui \
    wenshidu.ui \
    doorpane.ui

DISTFILES += MenuWindowForm.ui.qml

RESOURCES += \
    suicai.qrc

  RC_FILE= homie.rc
