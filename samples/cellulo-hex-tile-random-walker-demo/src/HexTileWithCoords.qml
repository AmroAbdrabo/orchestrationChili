import QtQuick 2.0

import Cellulo 1.0

HexTile{
    id: tile

    Text{
        text: tile.coords.q + "," + tile.coords.r
        anchors.verticalCenter: tile.verticalCenter
        anchors.horizontalCenter: tile.horizontalCenter
        font.pixelSize: tile.height/6
    }
}
