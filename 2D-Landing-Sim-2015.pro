#-------------------------------------------------
#
# Project created by QtCreator 2015-07-27T13:12:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2D-Landing-Sim-2015
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    plane.cpp \
    engine.cpp \
    mainmenu.cpp

HEADERS  += \
    game.h \
    plane.h \
    engine.h \
    mainmenu.h

RESOURCES += \
    graphics+sound.qrc
