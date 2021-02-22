#-------------------------------------------------
#
# Project created by QtCreator 2017-11-05T15:10:07
#
#-------------------------------------------------

QT       += sql
QT       += gui
QT       += core gui
QT       += widgets
QT       += sql
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = userinfo
TEMPLATE = app


SOURCES += main.cpp\
    dbmanager.cpp

HEADERS  += dbmanager.h \
    userinfo_global.h \
    dbmanager.h

#FORMS    += mainwindow.ui
