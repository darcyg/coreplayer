#-------------------------------------------------
#
# Project created by QtCreator 2018-08-18T15:09:36
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = untitled
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

# Enable warnings and threading support
CONFIG += thread silent warn_off build_all

INCLUDEPATH += ../libQtAV
LIBS += -L$$OUT_PWD/../libQtAV

INCLUDEPATH += ../libQtAVWidgets
LIBS += -L$$OUT_PWD/../libQtAVWidgets

LIBS += -lQtAV
LIBS += -lQtAVWidgets


SOURCES += main.cpp player.cpp

HEADERS += player.h

FORMS   += player.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
