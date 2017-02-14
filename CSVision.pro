#-------------------------------------------------
#
# Project created by QtCreator 2017-02-12T14:20:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CSVision
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cspoint2d.cpp \
    csline2d.cpp \
    csshape2d.cpp \
    cspoint3d.cpp \
    csline3d.cpp \
    csplane3d.cpp \
    cscamera.cpp \
    csscene3d.cpp

HEADERS  += mainwindow.h \
    cspoint2d.h \
    csline2d.h \
    csshape2d.h \
    cspoint3d.h \
    csline3d.h \
    csplane3d.h \
    cscamera.h \
    csscene3d.h

FORMS    += mainwindow.ui
