SOURCE_UNDER_TEST = ../SteamGameMover/

QT += testlib

install_it.path = $${OUT_PWD}
install_it.files += TestData/

INSTALLS += install_it

SOURCES += \
    SteamAppManifestParserTest.cpp \
    main.cpp \
    SteamAppListItemTest.cpp \
    SteamAppListModelTest.cpp \
    SteamAppDataTransfererTest.cpp

HEADERS += \
    AutoTest.h \
    SteamAppListItemFake.h

SOURCES += \
    $${SOURCE_UNDER_TEST}SteamAppManifestParser.cpp \
    $${SOURCE_UNDER_TEST}SteamAppListItem.cpp \
    $${SOURCE_UNDER_TEST}SteamAppListModel.cpp \
    $${SOURCE_UNDER_TEST}SteamAppDataTransferer.cpp

HEADERS += \
    $${SOURCE_UNDER_TEST}SteamAppManifestParser.h \
    $${SOURCE_UNDER_TEST}SteamAppListItem.h \
    $${SOURCE_UNDER_TEST}SteamAppListModel.h \
    $${SOURCE_UNDER_TEST}SteamAppDataTransferer.h

