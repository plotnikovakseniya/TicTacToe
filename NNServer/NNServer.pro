QT += core network
QT -= gui

SOURCES += \
            src/nnserver.cpp \
            src/main.cpp

HEADERS += include/nnserver.h

INCLUDEPATH += include \s
               ../shared/include \

LIBS += -L$$PWD/../shared/lib -lNetworkLib

DEFINES += \
    NETWORK_SETTINGS_FILE='\\"$$PWD/../shared/networksettings/networksettings.conf\\"'
