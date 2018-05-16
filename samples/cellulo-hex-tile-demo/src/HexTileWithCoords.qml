import QtQuick 2.0

import Cellulo 1.0

HexTile{
    Text{
        text: parent.coords.q + "," + parent.coords.r
        font.pixelSize: parent.height/5
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
