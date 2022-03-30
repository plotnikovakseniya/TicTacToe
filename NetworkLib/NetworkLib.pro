QT += core network

CONFIG += c++11

SOURCES += src/package.cpp \
           src/servermanager.cpp

HEADERS += include/package.h \
           include/networktypes.h \
           include/servermanager.h

INCLUDEPATH += include

TEMPLATE = lib

DESTDIR = ../shared/lib

headers.path = ../shared/include
headers.files = include/package.h \
                include/networktypes.h \
                include/servermanager.h

INSTALLS += headers

