import QtQuick 2.0
import QtQuick.Controls 2.0

TextField{
    id:                             root
    focus:                          true

    background: Rectangle{
        id:                         backRect
        implicitWidth:              parent.width
        implicitHeight:             parent.height
        color:                      "red"
        border.color:               "yellow"
        border.width:               4
        radius:                     8
    }
}
