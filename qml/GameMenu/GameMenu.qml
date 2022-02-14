import QtQuick 2.0
import QtQuick.Controls 2.15
import GameControllerBase 1.0
import ResourceProvider 1.0

MenuBar {
    id: root

    property GameControllerBase gameController

    Menu {
        id: _menu

        title: qsTr("&Settings")

        Action {
            id: _theme
            text: (_gameController.theme ? "Dark" : "Light") + " &theme"
            icon.source: ResourceProvider.icons.themeIcon
            onTriggered: {
                gameController.switchTheme()
            }
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
