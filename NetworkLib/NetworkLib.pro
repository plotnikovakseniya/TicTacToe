QT += core network

CONFIG += c++11

SOURCES += src/package.cpp \
           src/servermanager.cpp\
           src/clientmanager.cpp \
           src/connectionsettings.cpp

HEADERS += include/package.h \
           include/networktypes.h \
           include/servermanager.h \
           include/clientmanager.h \
           include/connectionsettings.h

INCLUDEPATH += include

TEMPLATE = lib

DESTDIR = $$PWD/../shared/lib

headers.path = ../shared/include
headers.files = include/package.h \
                include/networktypes.h \
                include/servermanager.h \
                include/clientmanager.h \
                include/connectionsettings.h

INSTALLS += headers

