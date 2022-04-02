QT += core

CONFIG += c++11

SOURCES += src/gameboard.cpp

HEADERS += include/gameboard.h \
           include/gametypes.h

INCLUDEPATH += include

TEMPLATE = lib

DESTDIR = $$PWD/../shared/lib

headers.path = ../shared/include
headers.files = include/gameboard.h \
                include/gametypes.h

INSTALLS += headers

