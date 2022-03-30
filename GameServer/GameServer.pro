QT += core network
QT -= gui

SOURCES += \
            src/gameserver.cpp \
            src/main.cpp

HEADERS += include/gameserver.h

INCLUDEPATH += include \
               ../shared/include

LIBS += -L$$PWD/../shared/lib -lNetworkLib
