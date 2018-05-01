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

    HexTileRemapper{
        id: hexMap

        tiles: [tile1, tile2, tile3, tile4, tile5, tile6]

        HexTile{ id: tile1
            sourceLeft: 105.7; sourceRight: 210.0; sourceTop: 0.0; sourceBottom: 130.0; sourceCenterX: 50.0; sourceCenterY: 67.0;
            q: 0; r: 0
        }
        HexTile{ id: tile2
            sourceLeft: 210.0 + 0.0; sourceRight: 210.0 + 105.7; sourceTop: 0.0; sourceBottom: 130.0; sourceCenterX: 50.0; sourceCenterY: 67.0;
            q: 1; r: 0
        }
        HexTile{ id: tile3
            sourceLeft: 0.0; sourceRight: 105.7; sourceTop: 0.0; sourceBottom: 130.0; sourceCenterX: 50.0; sourceCenterY: 67.0;
            q: -1; r: 0
        }
        HexTile{ id: tile4
            sourceLeft: 105.7; sourceRight: 210.0; sourceTop: 130.0; sourceBottom: 260.0; sourceCenterX: 50.0; sourceCenterY: 67.0;
            q: 0; r: 1
        }
        HexTile{ id: tile5
            sourceLeft: 0.0; sourceRight: 105.7; sourceTop: 130.0; sourceBottom: 260.0; sourceCenterX: 50.0; sourceCenterY: 67.0;
            q: 0; r: -1
        }
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

        Image{
            source: robotComm.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
            rotation: robotComm.theta
            x: robotComm.x*parent.scaleCoeff - width/2 + 150*parent.scaleCoeff
            y: robotComm.y*parent.scaleCoeff - height/2 + 150*parent.scaleCoeff
            sourceSize.width: 75*parent.scaleCoeff
            sourceSize.height: 80*parent.scaleCoeff
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
