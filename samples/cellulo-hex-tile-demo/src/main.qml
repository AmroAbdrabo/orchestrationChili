import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.2
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: height
    minimumWidth: width

    GroupBox {
        id: addressBox
        title: "Robot Address"

        MacAddrSelector{
            addresses: [
                "00:06:66:74:40:DB"
            ]
            onConnectRequested: robotComm.macAddr = selectedAddress
            onDisconnectRequested: robotComm.disconnectFromServer()
            connectionStatus: robotComm.connectionStatus
        }
    }

    HexTileMap{
        id: hexMap

        HexTile{
            standardCoords: HexTileStandardCoords{ i:0; j:0; u:0; v:0 }
            q: 0; r: 0
        }
        HexTile{
            standardCoords: HexTileStandardCoords{ i:0; j:0; u:1; v:0 }
            q: 1; r: 0
        }
        HexTile{
            standardCoords: HexTileStandardCoords{ i:0; j:0; u:0; v:1 }
            q: 1; r: -1
        }
        HexTile{
            id: extile
            standardCoords: HexTileStandardCoords{ id: oldcoords; i:0; j:0; u:1; v:1 }

            q: 1; r: 1
        }

    }

    Text{ anchors.top: page.bottom; text: extile.sourceLeft + " " + extile.sourceRight + " " + extile.sourceTop + " " + extile.sourceBottom + " " + extile.sourceCenterX + " " + extile.sourceCenterY }

    Button{ id: asdasd; text: "asdasd"; onClicked: extile.standardCoords = newcoords }

    Button{ anchors.left: asdasd.right; text: "asdas2"; onClicked: oldcoords.i = 3 }

    HexTileStandardCoords{
        id: newcoords
    }

    Rectangle{
        id: page
        anchors.top: addressBox.bottom
        anchors.left: parent.left
        anchors.margins: 50

        property real scaleCoeff: Math.min((Screen.width*0.8)/300, (Screen.height*0.8 - addressBox.height)/300)

        width: 300*scaleCoeff
        height: 300*scaleCoeff
        color: "#EEEEEE"
        border.color: "black"
        border.width: 2
        radius: 5

        HexTile{
            standardCoords: HexTileStandardCoords{ i:0; j:0; u:0; v:1 }
            q: 1; r: -1
            width: 50
            height: width*2/Math.sqrt(3)
            x: parent.width/2
            y: parent.height/2
            rotation: 40
            visible: true
        }

        Image{
            source: robotComm.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
            rotation: robotComm.theta
            x: robotComm.x*parent.scaleCoeff - width/2 + 150*parent.scaleCoeff
            y: robotComm.y*parent.scaleCoeff - height/2 + 150*parent.scaleCoeff
            sourceSize.width: 75*parent.scaleCoeff
            sourceSize.height: 80*parent.scaleCoeff
            visible: false
        }
    }

    Item{ //Dummy item to provide margin for bottom
        anchors.top: page.bottom
        anchors.margins: 50
    }

    Item{ //Dummy item to provide margin for right
        anchors.left: page.right
        anchors.margins: 50
    }

    CelluloRobot{
        id: robotComm
        onConnectionStatusChanged:{
            if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                setPoseBcastPeriod(0);
        }
        poseRemapper: hexMap

        onPoseChanged: console.info(x+" "+y+" "+theta)
    }
}
