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
    SteamAppListModel.cpp \
    SteamAppListItem.cpp \
    SteamAppDirectorySelector.cpp \
    SteamAppManifestParser.cpp \
    SteamAppDataTransferer.cpp \
    TransferErrorDialog.cpp \
    AppTransferError.cpp \
    TransferProgressDialog.cpp \
    AboutDialog.cpp \
    HelpDialog.cpp

HEADERS  += MainWindow.h \
    SteamAppListModel.h \
    SteamAppListItem.h \
    SteamAppDirectorySelector.h \
    SteamAppManifestParser.h \
    SteamAppDataTransferer.h \
    TransferErrorDialog.h \
    AppTransferError.h \
    TransferProgressDialog.h \
    AboutDialog.h \
    HelpDialog.h

FORMS    += MainWindow.ui \
    TransferErrorDialog.ui \
    TransferProgressDialog.ui \
    AboutDialog.ui \
    HelpDialog.ui

RESOURCES += \
    resources.qrc
