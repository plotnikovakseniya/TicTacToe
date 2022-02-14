import QtQuick 2.15
import QtQuick.Controls 2.15
import GameBoard.Base 1.0
import QtQuick.Controls.Universal 2.15
import GameMenu 1.0

ApplicationWindow {
    id: root
    width: 600
    height: 600
    visible: true

    Universal.theme: Universal.Dark

    menuBar: GameMenu {
        themeIcon: "qrc:/stylesettings/icons/theme.svg"
        themeText: "Light &theme"
    }

    Button {
        text: "123"
    }

//    GameControllerBase {
//        id: _gameController
//    }

}
