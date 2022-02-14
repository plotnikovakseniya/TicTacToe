import QtQuick 2.15
import QtQuick.Controls 2.15
import GameBoard 1.0
import QtQuick.Controls.Universal 2.15
import GameMenu 1.0
import GameController 1.0
import ResourceProvider 1.0

ApplicationWindow {
    id: root
    width: 600
    height: 600
    visible: true

    Universal.theme: _gameController.theme ? Universal.Light : Universal.Dark

    menuBar: GameMenu {
        id: _gameMenu
        gameController: _gameController
    }

    GameBoard {
        id: _gameBoard

        anchors.fill: parent

        gameController: _gameController
    }

    GameController {
        id: _gameController
    }
}
