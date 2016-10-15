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
    Point3DT.cpp \
    TrajectoryCalculator.cpp \
    Trajectory.cpp \
    widgets/trajectorywidget.cpp \
    widgets/cutwidget.cpp \
    circuitparameters.cpp \
    calculatedcut.cpp \
    partiallycalculatedcut.cpp

HEADERS  += mainwindow.h \
    qcustomplot/qcustomplot.h \
    Point3DT.h \
    TrajectoryCalculator.h \
    Trajectory.h \
    widgets/trajectorywidget.h \
    widgets/cutwidget.h \
    circuitparameters.h \
    trajectoryresulttype.h \
    calculatedcut.h \
    partiallycalculatedcut.h

FORMS    += mainwindow.ui \
    widgets/cutwidget.ui \
    widgets/trajectorywidget.ui

DISTFILES += \
    parameters.txt

LIBS += -ltbb
