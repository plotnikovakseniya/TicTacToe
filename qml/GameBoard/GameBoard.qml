import QtQuick 2.0
import GameController 1.0

GridView {
    id: root

    cellHeight: height / root.model.dimension
    cellWidth: width / root.model.dimension

    property GameController gameController

    delegate: GameDelegate {
        width: root.cellWidth
        height: root.cellHeight
    }

    Component.onCompleted: {
        root.model = gameController.gameModel()
    }
}
