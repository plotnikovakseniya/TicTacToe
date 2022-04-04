QT += core

CONFIG += c++11

SOURCES += src/localgameboard.cpp

HEADERS += include/gameboardinterface.h \
           include/localgameboard.h \
           include/gametypes.h

INCLUDEPATH += include

TEMPLATE = lib

DESTDIR = $$PWD/../shared/lib

headers.path = ../shared/include
headers.files = include/gameboardinterface.h \
                include/localgameboard.h \
                include/gametypes.h

INSTALLS += headers

