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
    minimumHeight: 100
    minimumWidth: 200

    CelluloZoneEngine{
        id: zoneEngine

        CelluloZonePolyBezierDistance{
            id: staticZone
            name: "ZONE"
            controlPoints: [
                Qt.vector2d(0.28222222153533215923*95.871981,0.28222222153533215923*254.17223),
                Qt.vector2d(0.28222222153533215923*409.27877,0.28222222153533215923*586.84713),
                Qt.vector2d(0.28222222153533215923*240.24193,0.28222222153533215923*23.240894),
                Qt.vector2d(0.28222222153533215923*405.78373,0.28222222153533215923*111.47905),
                Qt.vector2d(0.28222222153533215923*608.61513,0.28222222153533215923*151.29903),
                Qt.vector2d(0.28222222153533215923*454.34191,0.28222222153533215923*467.76628),
                Qt.vector2d(0.28222222153533215923*628.74183,0.28222222153533215923*519.49236),
                Qt.vector2d(0.28222222153533215923*-80.696715,0.28222222153533215923*915.53858),
                Qt.vector2d(0.28222222153533215923*379.76554,0.28222222153533215923*1066.4045),
                Qt.vector2d(0.28222222153533215923*182.82564,0.28222222153533215923*793.73082),
                Qt.vector2d(0.28222222153533215923*177.38786,0.28222222153533215923*533.72232),
                Qt.vector2d(0.28222222153533215923*0.81001263,0.28222222153533215923*736.4936),
                Qt.vector2d(0.28222222153533215923*111.47905,0.28222222153533215923*541.78817)
            ]
        }
    }

    CelluloBluetooth{
        id: robotComm
        macAddr: "00:06:66:74:43:00"

        Component.onCompleted: zoneEngine.addNewClient(robotComm)

        onZoneValueChanged: console.log(zone.name + " " + value)
    }

    //Visible items

    GroupBox {
        id: addressBox
        title: "Robots"

        Column{
            property variant addresses: [
                "00:06:66:74:40:D2",
                "00:06:66:74:40:D4",
                "00:06:66:74:40:D5",
                "00:06:66:74:40:DB",
                "00:06:66:74:40:DC",
                "00:06:66:74:40:E4",
                "00:06:66:74:40:EC",
                "00:06:66:74:40:EE",
                "00:06:66:74:41:03",
                "00:06:66:74:41:04",
                "00:06:66:74:41:14",
                "00:06:66:74:41:4C",
                "00:06:66:74:43:00",
                "00:06:66:74:43:01",
                "00:06:66:74:46:58",
                "00:06:66:74:46:60",
                "00:06:66:74:48:A7"
            ]

            MacAddrSelector{
                addresses: parent.addresses
                onConnectRequested: robotComm.macAddr = selectedAddress
                onDisconnectRequested: robotComm.disconnectFromServer()
                connectionStatus: robotComm.connectionStatus
            }
        }
    }

    GroupBox{
        id: playgroundBox
        title: "Playground"
        anchors.top: addressBox.bottom

        Item{
            width: page.width + page.physicalRobotWidth*page.scaleCoeff
            height: page.height + page.physicalRobotWidth*page.scaleCoeff

            Rectangle{
                id: page

                anchors.centerIn: parent

                property real physicalWidth: 210        ///< Physical paper width in mm
                property real physicalHeight: 297       ///< Physical paper height in mm
                property real physicalRobotWidth: 75    ///< Physical robot width in mm

                width: height*physicalWidth/physicalHeight
                height: Screen.height/2

                property real scaleCoeff: width/physicalWidth

                color: "#EEEEEE"
                border.color: "black"
                border.width: 2
                radius: 5

                CelluloZonePaintedItem{
                    color: "red"
                    physicalPlaygroundWidth: parent.physicalWidth
                    physicalPlaygroundHeight: parent.physicalHeight
                    associatedZone: staticZone
                }

                Image{
                    source: robotComm.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
                    rotation: robotComm.theta
                    x: robotComm.x*parent.scaleCoeff - width/2
                    y: robotComm.y*parent.scaleCoeff - height/2
                    width: parent.physicalRobotWidth*parent.scaleCoeff
                    fillMode: Image.PreserveAspectFit

                    Rectangle{
                        x: parent.width/2 - width/2
                        y: parent.height/2 - height/2
                        height: 5
                        width: 5
                        color: "black"
                        border.color: "black"
                        border.width: 1
                        radius: 2.5
                    }
                }
            }
        }
    }
}
