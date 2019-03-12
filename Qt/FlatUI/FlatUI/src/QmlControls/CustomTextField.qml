import QtQuick 2.0
import QtQuick.Controls 2.0
import FlatUI 1.0
import FlatUI.Controls 1.0

TextField{
    id:                             root
    focus:                          true
    width:                          ScreenTools.defaultFontPixelWidth * 16
    height:                         ScreenTools.defaultFontPixelHeight * 2.5
    color:                          ScreenTools.palette.text

    property int hintLevel:         FlatUI.MSG_ACCEPTED_LEVEL
    property alias textColor:       root.color

    onHintLevelChanged:     {
        switch(hintLevel){
        case FlatUI.MSG_REFUSED_LEVEL:
            textColor = ScreenTools.palette.errorHint
            break;
        default:
            ScreenTools.palette.text
            break;
        }
    }

    background: Rectangle{
        id:                         backRect
        implicitWidth:              parent.width
        implicitHeight:             parent.height
        color:                      ScreenTools.palette.windowInner
        border.color:               root.enabled ? (root.activeFocus ? ScreenTools.palette.infoHint :
                                        (hintLevel == FlatUI.MSG_ACCEPTED_LEVEL ?  ScreenTools.palette.windowInner
                                        : ScreenTools.palette.errorHint)) : ScreenTools.palette.disableHint
        border.width:               ScreenTools.defaultFontPixelWidth / 4
        radius:                     height / 4
    }
}
