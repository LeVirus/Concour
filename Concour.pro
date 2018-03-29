#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T17:54:03
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Concour
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    playerline.cpp \
    modifyline.cpp

HEADERS  += mainwindow.h \
    form.h \
    playerline.h \
    modifyline.h

FORMS    += mainwindow.ui \
    form.ui \
    modifyline.ui

RESOURCES += \
    playerline.qrc
