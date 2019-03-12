pragma Singleton

import QtQuick 2.0
import FlatUI.Palette 1.0

Item {
    property real defaultFontPointSize:     10
    property real defaultFontPixelHeight:   14
    property real defaultFontPixelWidth:    10

    property alias palette: palette
    Palette{
        id:             palette
    }

    Text {
        id:     _defaultFont
        text:   "X"
    }

    function _setFontSize(size){
        defaultFontPointSize = size
        defaultFontPixelWidth = Math.floor(_defaultFont.contentWidth / 2) * 2
        defaultFontPixelHeight = Math.floor(_defaultFont.contentHeight / 2) * 2
    }

    Text {
        id:     _textMeasure
        text:   "X"
        property real   fontWidth:    contentWidth
        property real   fontHeight:   contentHeight
        Component.onCompleted: {
            var baseSize = _defaultFont.font.pointSize;
            _setFontSize(baseSize)
            console.log(baseSize)
        }
    }
}
