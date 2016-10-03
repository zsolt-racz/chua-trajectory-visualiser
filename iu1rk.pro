#-------------------------------------------------
#
# Project created by QtCreator 2016-05-04T17:55:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = iu1rk
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot/qcustomplot.cpp \
    ChuaCalculator.cpp \
    Point3DT.cpp \
    ChuaResult.cpp

HEADERS  += mainwindow.h \
    qcustomplot/qcustomplot.h \
    ChuaCalculator.h \
    Point3DT.h \
    ChuaResult.h

FORMS    += mainwindow.ui

DISTFILES += \
    parameters.txt
