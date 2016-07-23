import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.2
import Cellulo 1.0

ApplicationWindow {
    id: root
    visible: true
    minimumHeight: 100
    minimumWidth: 200

    property variant polybezierPoints: [
        Qt.vector2d(0.28222222153533215923*95.871981,0.28222222153533215923*254.17223),
        Qt.vector2d(0.28222222153533215923*409.27877,0.28222222153533215923*586.84713),
        Qt.vector2d(0.28222222153533215923*532.31703,0.28222222153533215923*310.85683),
        Qt.vector2d(0.28222222153533215923*405.78373,0.28222222153533215923*111.47905),
        Qt.vector2d(0.28222222153533215923*124.79607,0.28222222153533215923*331.89509),
        Qt.vector2d(0.28222222153533215923*487.78562,0.28222222153533215923*391.96053),
        Qt.vector2d(0.28222222153533215923*662.18554,0.28222222153533215923*443.68661),
        Qt.vector2d(0.28222222153533215923*-243.45612,0.28222222153533215923*873.17654),
        Qt.vector2d(0.28222222153533215923*604.95321,0.28222222153533215923*1099.8482),
        Qt.vector2d(0.28222222153533215923*216.26935,0.28222222153533215923*717.92507),
        Qt.vector2d(0.28222222153533215923*-72.325208,0.28222222153533215923*1075.5105),
        Qt.vector2d(0.28222222153533215923*290.65553,0.28222222153533215923*502.3876),
        Qt.vector2d(0.28222222153533215923*111.47905,0.28222222153533215923*541.78817)
    ]

    CelluloZoneEngine{
        id: zoneEngine

        CelluloZonePolyBezierInner{
            id: zoneInner
            name: "ZONE_INNER"
            controlPoints: root.polybezierPoints
        }

        CelluloZonePolyBezierDistance{
            id: zoneDistance
            name: "ZONE_DISTANCE"
            controlPoints: root.polybezierPoints
            property vector2d closestPoint: Qt.vector2d(0,0)
        }

        CelluloZonePolyBezierBorder{
            id: zoneBorder
            name: "ZONE_BORDER"
            controlPoints: root.polybezierPoints
            borderThickness: 10
        }
    }

    CelluloBluetooth{
        id: robotComm
        macAddr: "00:06:66:74:43:00"

        property bool inInner: false
        property bool inBorder: false

        Component.onCompleted: zoneEngine.addNewClient(robotComm)

        onConnectionStatusChanged: {
            if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected){
                setCasualBackdriveAssistEnabled(true);
                setPoseBcastPeriod(0);
            }
        }

        onPoseChanged: zoneDistance.closestPoint = zoneDistance.getClosestPoint(Qt.vector2d(x,y))

        onZoneValueChanged: {
            switch(zone.name){
            case "ZONE_INNER":
                inInner = value;
                updateColors();
                break;
            case "ZONE_BORDER":
                inBorder = value;
                updateColors();
                break;
            case "ZONE_DISTANCE":
                distText.text = "Distance: " + value.toFixed(6) + "mm"
                break;
            default:
                break;
            }
        }

        function updateColors(){
            if(inInner && inBorder)
                setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#FF00FF", 0);
            else if(inInner)
                setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#FF0000", 0);
            else if(inBorder)
                setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#0000FF", 0);
            else
                setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#FFFFFF", 0);
        }
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
                    color: "#80FF0000"
                    physicalPlaygroundWidth: parent.physicalWidth
                    physicalPlaygroundHeight: parent.physicalHeight
                    associatedZone: zoneInner
                }

                CelluloZonePaintedItem{
                    color: "#800000FF"
                    physicalPlaygroundWidth: parent.physicalWidth
                    physicalPlaygroundHeight: parent.physicalHeight
                    associatedZone: zoneBorder
                }

                CelluloZonePaintedItem{
                    color: "#8000FF00"
                    physicalPlaygroundWidth: parent.physicalWidth
                    physicalPlaygroundHeight: parent.physicalHeight
                    associatedZone: zoneDistance
                }

                Rectangle{
                    x: zoneDistance.closestPoint.x*parent.scaleCoeff - width/2
                    y: zoneDistance.closestPoint.y*parent.scaleCoeff - height/2
                    height: 10
                    width: 10
                    color: "#80FFFFFF"
                    radius: 5
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

    Text{
        id: distText
        anchors.top: playgroundBox.bottom
    }
}
