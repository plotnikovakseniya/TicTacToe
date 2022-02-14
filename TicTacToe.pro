QT += quick
QT += quickcontrols2

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gamecontroller/base/gamecontrollerbase.cpp \
        main.cpp

RESOURCES += \
        qml.qrc

TRANSLATIONS += \
        translations/TicTacToe_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

QT_QUICK_CONTROLS_CONF += $$PWD/stylesettings/qtquickcontrols2.conf

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml
QML2_IMPORT_PATH += $$PWD/qml
+
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/GameBoard/Base/GameBoardBase.qml \
    main.qml \
    qml/GameBoard/Base/qmldir \
    qml/GameBoard/Impl/qmldir \
    qml/GameBoard/qmldir \
    qml/GameMenu/qmldir \
    qml/GameMenu/qmldir \
    stylesettings/icons/settings.svg

HEADERS += \
    gamecontroller/base/gamecontrollerbase.h
