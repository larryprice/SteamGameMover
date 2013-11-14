SOURCE_UNDER_TEST = ../SteamGameMover/

QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32 {
    PWD_WIN = $${PWD}
    PWD_WIN ~= s,/,\\,g

    QMAKE_POST_LINK += $$quote(mkdir DestFolder)
    QMAKE_POST_LINK += $$quote(xcopy $${PWD_WIN}\\TestData $${OUT_PWD_WIN}\\TestData /E)

    QMAKE_CLEAN += /s /f /q TestData && rd /s /q TestData
}

unix {
    QMAKE_POST_LINK += $$quote(cp -rf $${PWD}/TestData $${OUT_PWD})

    QMAKE_CLEAN += -r TestData
}

SOURCES += \
    SteamAppManifestParserTest.cpp \
    main.cpp \
    SteamAppListItemTest.cpp \
    SteamAppListModelTest.cpp \
    SteamAppDataTransfererTest.cpp \
    AppTransferErrorTest.cpp

HEADERS += \
    AutoTest.h \
    SteamAppListItemFake.h

SOURCES += \
    $${SOURCE_UNDER_TEST}SteamAppManifestParser.cpp \
    $${SOURCE_UNDER_TEST}SteamAppListItem.cpp \
    $${SOURCE_UNDER_TEST}SteamAppListModel.cpp \
    $${SOURCE_UNDER_TEST}SteamAppDataTransferer.cpp \
    $${SOURCE_UNDER_TEST}AppTransferError.cpp

HEADERS += \
    $${SOURCE_UNDER_TEST}SteamAppManifestParser.h \
    $${SOURCE_UNDER_TEST}SteamAppListItem.h \
    $${SOURCE_UNDER_TEST}SteamAppListModel.h \
    $${SOURCE_UNDER_TEST}SteamAppDataTransferer.h \
    $${SOURCE_UNDER_TEST}AppTransferError.h
