SOURCE_UNDER_TEST = ../SteamGameMover/

QT += testlib
QT -= gui

install_it.path = $${OUT_PWD}
install_it.files += TestData/

INSTALLS += install_it

SOURCES += \
    SteamAppManifestParserTest.cpp \
    main.cpp \
    SteamAppListItemTest.cpp \
    SteamAppListModelTest.cpp

HEADERS += \
    AutoTest.h

SOURCES += \
    $${SOURCE_UNDER_TEST}SteamAppManifestParser.cpp \
    $${SOURCE_UNDER_TEST}SteamAppListItem.cpp \
    $${SOURCE_UNDER_TEST}SteamAppListModel.cpp

HEADERS += \
    $${SOURCE_UNDER_TEST}SteamAppManifestParser.h \
    $${SOURCE_UNDER_TEST}SteamAppListItem.h \
    $${SOURCE_UNDER_TEST}SteamAppListModel.h
