import QtQuick 2.9
import QtQuick.Controls 2.2
import FlatUI 1.0
import FlatUI.Controls 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")
    color: ScreenTools.palette.window
    ScrollView {
        anchors.fill: parent
        ListView {
            width: parent.width
            model: 20
            delegate: ItemDelegate {
                text: "Item " + (index + 1)
                width: parent.width
            }
        }
    }

    Row{
        anchors.centerIn:   parent
        spacing:                20
        CustomTextField{
        }
        CustomTextField{
            onEditingFinished:  hintLevel = FlatUI.MSG_REFUSED_LEVEL
        }
    }
}
