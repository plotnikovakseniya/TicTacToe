import QtQuick 2.0
import QtQuick.Controls 2.15
import GameController 1.0
import ResourceProvider 1.0

MenuBar {
    id: root

    property GameController gameController

    Menu {
        id: _menu

        title: qsTr("&Settings")

        Action {
            id: _theme
            text: (_gameController.clientSettings().theme ? "Dark" : "Light") + " &theme"
            icon.source: ResourceProvider.icons.themeIcon
            onTriggered: {
                gameController.clientSettings().switchTheme()
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
