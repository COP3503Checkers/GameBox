#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T15:30:51
#
#-------------------------------------------------

QT       += core gui \
         multimedia

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
    health.cpp \
    enemy2.cpp \
    bullet2.cpp \
    level.cpp

HEADERS  += mainwindow.h \
    player.h \
    bullet.h \
    enemy.h \
    galaga.h \
    score.h \
    health.h \
    enemy2.h \
    bullet2.h \
    level.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
