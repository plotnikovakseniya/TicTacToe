pragma Singleton
import QtQuick 2.0

Item {
    property alias icons: _icons

    QtObject {
        id: _icons
        readonly property string themeIcon: "qrc:/stylesettings/icons/theme.svg"
    }
}
