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
    playerline.cpp \
    modifyline.cpp \
    windowsaveask.cpp \
    contestgenerate.cpp \
    windowteamconstruct.cpp \
    team.cpp \
    gamesopponnentscontainer.cpp \
    versusteams.cpp \
    pdfdocgeneration.cpp \
    modechoosewindow.cpp \
    meleemeleeform.cpp \
    presetteamform.cpp \
    teamline.cpp \
    modteam.cpp

HEADERS  += mainwindow.h \
    playerline.h \
    modifyline.h \
    windowsaveask.h \
    contestgenerate.h \
    windowteamconstruct.h \
    team.h \
    gamesopponnentscontainer.h \
    versusteams.h \
    pdfdocgeneration.h \
    modechoosewindow.h \
    meleemeleeform.h \
    presetteamform.h \
    teamline.h \
    modteam.h

FORMS    += mainwindow.ui \
    modifyline.ui \
    windowsaveask.ui \
    contestgenerate.ui \
    windowteamconstruct.ui \
    modechoosewindow.ui \
    presetteamform.ui \
    meleemeleeform.ui \
    modteam.ui
