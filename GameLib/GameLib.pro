QT += core

CONFIG += c++11

SOURCES += src/localgameboard.cpp

HEADERS += include/gameboardinterface.h \
           include/localgameboard.h \
           include/gametypes.h \
           include/gamelib_global.h

INCLUDEPATH += include

TEMPLATE = lib

DEFINES += MAKE_GAME_LIB

DESTDIR = $$PWD/../shared/lib

headers.path = ../shared/include
headers.files = include/gameboardinterface.h \
                include/localgameboard.h \
                include/gametypes.h \
                include/gamelib_global.h

INSTALLS += headers

