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

        Slider{
            id: slider
            width: 100
            value: 1.0

            //onValueChanged: hexMap.physicalArea = Qt.rect(-200*slider.value, -200*slider.value, 400*slider.value, 400*slider.value)
        }
    }



    // Text{ anchors.top: page.bottom; text: extile.sourceLeft + " " + extile.sourceRight + " " + extile.sourceTop + " " + extile.sourceBottom + " " + extile.sourceCenterX + " " + extile.sourceCenterY }

    Button{ id: asdasd; text: "asdasd"; onClicked: extile.standardCoords = newcoords }

    Button{ anchors.left: asdasd.right; text: "asdas2"; onClicked: extile.r = -2 }

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

        HexTileMap{
            id: hexMap

            width: parent.width*slider.value
            height: parent.height*slider.value
            //x: slider.value*100
            //y: slider.value*100
            physicalSize: Qt.vector2d(400, 400)
            physicalTopLeft: Qt.vector2d(-200, -200)



            HexTileWithCoords{
                standardCoords: HexTileStandardCoords{ i:7; j:9; u:0; v:0 }
                q: 0; r: 0
            }

            HexTileWithCoords{
                standardCoords: HexTileStandardCoords{ i:2; j:3; u:0; v:1 }
                q: -1; r: 0
            }

            HexTileWithCoords{
                standardCoords: HexTileStandardCoords{ i:2; j:3; u:1; v:1 }
                q: 1; r: 0
            }

            HexTileWithCoords{
                standardCoords: HexTileStandardCoords{ i:2; j:3; u:0; v:0 }
                q: 0; r: -1
            }

            HexTileWithCoords{
                standardCoords: HexTileStandardCoords{ i:7; j:9; u:1; v:1 }
                q: 1; r: -1
            }

            HexTileWithCoords{
                standardCoords: HexTileStandardCoords{ i:7; j:9; u:1; v:0 }
                q: -1; r: 1
            }

            HexTileWithCoords{
                standardCoords: HexTileStandardCoords{ i:2; j:3; u:1; v:0 }
                q: 0; r: 1
            }

            Image{
                property vector2d screenSize: Qt.vector2d(75, 75*2/Math.sqrt(3)).times(parent.toScreen)
                property vector2d screenCoords: Qt.vector2d(robotComm.x, robotComm.y).minus(parent.physicalTopLeft).times(parent.toScreen)

                source: robotComm.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
                rotation: robotComm.theta
                width: screenSize.x
                height: screenSize.y
                sourceSize.width: screenSize.x
                sourceSize.height: screenSize.y
                x: screenCoords.x - width/2
                y: screenCoords.y - height/2
                visible: true
            }
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
    }
}
