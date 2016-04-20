#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T15:30:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Galaga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    bullet.cpp \
    enemy.cpp \
    galaga.cpp \
    score.cpp \
    health.cpp

HEADERS  += mainwindow.h \
    player.h \
    bullet.h \
    enemy.h \
    galaga.h \
    score.h \
    health.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
