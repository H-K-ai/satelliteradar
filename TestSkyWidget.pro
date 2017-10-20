#--------------------------------------------------------------------------
#
# Project created by QtCreator 2017-10-08T17:14:13
#/*!
# *@file    TestSkyWidget.pro
# *@brief   模拟卫星/雷达扫描
# *@version 0.1
# *@section LICENSE Copyright (C) 2017-2117 NCHU ImgProcessing Corporation
# *@writer  MHK
# */
#--------------------------------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestSkyWidget
TEMPLATE = app


SOURCES += main.cpp\
        testskywidget.cpp \
    Window.cpp

HEADERS  += testskywidget.h \
    Window.h

FORMS    +=
