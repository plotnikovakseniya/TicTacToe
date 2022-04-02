import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Universal 2.15

Item {
    id: root

    Rectangle {
        id: _rectangle

        color: Universal.background

        anchors.fill: parent
        anchors.leftMargin: -border.width
        anchors.rightMargin: -border.width
        anchors.topMargin:  -border.width
        anchors.bottomMargin: -border.width

        visible: true

        border.width: 5
        border.color: Universal.foreground

        Label {
            id: _label
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: cagetext
            font.family: "Funhouse"
            font.pointSize: Math.min(root.width / 2, root.height / 2)
        }
    }
}
