QT += core network
QT -= gui

SOURCES += \
            src/nnserver.cpp \
            src/main.cpp

HEADERS += include/nnserver.h

INCLUDEPATH += include \
               ../shared/include

LIBS += -L$$PWD/../shared/lib -lNetworkLib
