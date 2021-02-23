QT += core
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG(release, debug|release){
unix:DESTDIR=./release
}
CONFIG(debug, debug|release){
unix:DESTDIR=./debug
}
unix:OBJECTS_DIR = ../.obj/linux
win32:OBJECTS_DIR = ../.obj/win32
SOURCES += \
        src/assets-addnewspecies.cpp \
        src/assets-printinfo.cpp \
        src/assets.cpp \
        src/character-printinfo.cpp \
        src/character.cpp \
        src/globals.cpp \
        src/inventory.cpp \
        src/iohandling.cpp \
        src/main.cpp \
        src/menu.cpp \
        src/nonplayerchar.cpp \
        src/player-fileio.cpp \
        src/player.cpp \
        src/statemanager.cpp \
        src/terminalmanip.cpp

HEADERS += \
    src/assets.h \
    src/character.h \
    src/globals.h \
    src/inventory.h \
    src/iohandling.h \
    src/menu.h \
    src/nonplayerchar.h \
    src/player.h \
    src/statemanager.h \
    src/terminalmanip.h
