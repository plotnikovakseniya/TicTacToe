import QtQuick 2.15
import QtQuick.Controls 2.0
import GameBoard.Base 1.0
import QtQuick.Controls.Universal 2.0

ApplicationWindow {
    id: root
    width: 200
    height: 200
    visible: true

    Universal.theme: Universal.Dark

    Button {
        text: "123"
    }

//    GameBoardBase {
//        id: _gameboard
//        anchors.fill: parent
//        anchors.margins: 5
//    }
}
