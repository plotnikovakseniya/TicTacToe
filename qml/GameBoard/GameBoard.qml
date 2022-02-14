import QtQuick 2.0
import GameController 1.0
import QtQuick.Controls.Universal 2.15

GridView {
    id: root

    cellHeight: height / root.model.dimension
    cellWidth: width / root.model.dimension

    property GameController gameController

    delegate: Item {
        id: _delegate
        width: root.cellWidth
        height: root.cellHeight
        visible: true
        Text {
            id: _text
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: index
            color: Universal.foreground
        }
    }

    Component.onCompleted: {
        root.model = gameController.gameModel();
    }
}
