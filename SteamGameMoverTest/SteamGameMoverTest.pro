QT += testlib
QT -= gui

install_it.path = $${OUT_PWD}
install_it.files += TestData/

INSTALLS += install_it

SOURCES += \
    SteamAppManifestParserTest.cpp \
    SteamAppDirectorySelectorTest.cpp \
    main.cpp \
    SteamAppListItemTest.cpp

HEADERS += \
    AutoTest.h
