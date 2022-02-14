import QtQuick 2.15
import QtQuick.Controls 2.15
import GameBoard.Base 1.0
import QtQuick.Controls.Universal 2.15
import GameMenu 1.0
import GameControllerBase 1.0
import ResourceProvider 1.0

ApplicationWindow {
    id: root
    width: 600
    height: 600
    visible: true

    Universal.theme: _gameController.theme ? Universal.Light : Universal.Dark

    menuBar: GameMenu {
        themeText: _gameController.theme ? "Dark" : "Light"
        themeIcon: ResourceProvider.icons.themeIcon
    }

    Button {
        text: "123"
    }

    GameControllerBase {
        id: _gameController
    }

}
