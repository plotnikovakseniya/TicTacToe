QT += quick
QT += quickcontrols2

SOURCES += \
        src/clientsettings.cpp \
        src/gamecontroller.cpp \
        src/gamemodel.cpp \
        src/client.cpp \
        main.cpp

RESOURCES += \
        qml.qrc

TRANSLATIONS += \
        translations/TicTacToe_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

QT_QUICK_CONTROLS_CONF += stylesettings/stylesettings.conf

QML_IMPORT_PATH += $$PWD/qml
QML2_IMPORT_PATH += $$PWD/qml

INCLUDEPATH += include

QML_DESIGNER_IMPORT_PATH =

DISTFILES += \
    qml/GameBoard/GameBoard.qml \
    main.qml \
    qml/GameBoard/qmldir \
    qml/GameMenu/qmldir \
    qml/GameMenu/qmldir \
    qml/ResourceProvider/qmldir \
    stylesettings/icons/settings.svg

HEADERS += \
    include/clientsettings.h \
    include/gamecontroller.h \
    include/gamemodel.h\
    include/client.h

INCLUDEPATH += include \
               ../shared/include

LIBS += -L$$PWD/../shared/lib -lNetworkLib -lGameLib

DEFINES += \
    NETWORK_SETTINGS_FILE='\\"$$PWD/../shared/networksettings/networksettings.conf\\"'
