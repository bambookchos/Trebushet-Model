#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T19:30:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = persistent_paint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintwidget.cpp \
    model.cpp \
    matrix.cpp \
    Objects/ground.cpp \
    Objects/trebushet.cpp \
    Objects/barrel.cpp \
    sprite.cpp \



HEADERS  += mainwindow.h \
    paintwidget.h \
    model.h \
    face.h \
    matrix.h \
    sprite.h \
    Objects/barrel.h \
    Objects/ground.h \
    Objects/trebushet.h \




FORMS    += mainwindow.ui

RESOURCES += sprites/exp08_001.png \
    sprites/exp08_002.png \
    sprites/exp08_003.png \
    sprites/exp08_004.png \
    sprites/exp08_005.png \
    sprites/exp08_006.png \
    sprites/exp08_007.png \
    sprites/exp08_008.png \
    sprites/exp08_009.png \
    sprites/exp08_010.png \
    sprites/exp08_011.png \
    sprites/exp08_012.png \
    sprites/exp08_013.png \
    sprites/exp08_014.png \
    sprites/exp08_015.png \
    sprites/exp08_016.png \
    sprites/exp08_017.png \
    sprites/exp08_018.png \
    sprites/exp08_019.png \
    sprites/exp08_020.png \
    sprites/exp08_021.png \
    sprites/exp08_022.png \
    sprites/exp08_023.png \
    sprites/exp08_024.png \
    sprites/exp08_025.png \
    sprites/exp08_026.png \
    sprites/exp08_027.png \
    sprites/exp08_028.png \
    sprites/exp08_031.png



