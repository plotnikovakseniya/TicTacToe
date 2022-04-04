QT += core network

CONFIG += c++11

SOURCES += src/package.cpp \
           src/nextmovemessage.cpp \
           src/servermanager.cpp\
           src/clientmanager.cpp \
           src/connectionsettings.cpp \
           src/gamestartresponse.cpp

HEADERS += include/package.h \
           include/networktypes.h \
           include/nextmovemessage.h \
           include/servermanager.h \
           include/clientmanager.h \
           include/connectionsettings.h \
           include/gamestartresponse.h

INCLUDEPATH += include \
               ../shared/include

TEMPLATE = lib

DESTDIR = $$PWD/../shared/lib

headers.path = ../shared/include
headers.files = include/package.h \
                include/networktypes.h \
                include/servermanager.h \
                include/clientmanager.h \
                include/connectionsettings.h \
                include/nextmovemessage.h \
                include/gamestartresponse.h

INSTALLS += headers

