#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T17:54:03
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Concour
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    playerline.cpp \
    modifyline.cpp \
    windowsaveask.cpp \
    contestgenerate.cpp \
    windowteamconstruct.cpp \
    team.cpp \
    gamesopponnentscontainer.cpp \
    versusteams.cpp \
    pdfdocgeneration.cpp

HEADERS  += mainwindow.h \
    form.h \
    playerline.h \
    modifyline.h \
    windowsaveask.h \
    contestgenerate.h \
    windowteamconstruct.h \
    team.h \
    gamesopponnentscontainer.h \
    versusteams.h \
    pdfdocgeneration.h

FORMS    += mainwindow.ui \
    form.ui \
    modifyline.ui \
    windowsaveask.ui \
    contestgenerate.ui \
    windowteamconstruct.ui
