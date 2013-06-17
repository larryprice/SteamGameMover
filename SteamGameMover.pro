#-------------------------------------------------
#
# Project created by QtCreator 2013-06-16T12:28:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SteamGameMover
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    SGMDirectorySelector.cpp \
    SGMListItemModel.cpp

HEADERS  += MainWindow.h \
    SGMDirectorySelector.h \
    SGMListItemModel.h

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
