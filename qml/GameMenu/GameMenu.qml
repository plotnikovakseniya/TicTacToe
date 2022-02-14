import QtQuick 2.0
import QtQuick.Controls 2.15

MenuBar {
    id: root

    property alias themeIcon: _theme.icon.source
    property alias themeText: _theme.text

    Menu {
        id: _menu

        title: qsTr("&Settings")

        Action {
            id: _theme
        }

        MenuSeparator {}

        Action {
            id: _quit
            text: qsTr("&Quit")
            onTriggered: {
                Qt.quit()
            }
        }
    }
}
