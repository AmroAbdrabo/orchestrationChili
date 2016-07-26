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

    CelluloZoneEngine{
        id: zoneEngine

        property var zoneDistance: null
        property vector2d closestPoint: Qt.vector2d(0,0)

        Component.onCompleted: {
            var zones = CelluloZoneJsonHandler.loadZonesQML(":/assets/zones.json");
            for(var i=0;i<zones.length;i++){
                var color;
                switch(zones[i].name){
                case "ZONE_INNER":
                    color = "#80FF0000";
                    break;
                case "ZONE_BORDER":
                    color = "#800000FF";
                    break;
                case "ZONE_DISTANCE":
                    color = "#8000FF00";
                    zoneDistance = zones[i];
                    break;
                default:
                    break;
                }
                zones[i].createPaintedItem(page, color, page.physicalWidth, page.physicalHeight);
            }
            addNewZones(zones);
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

        onPoseChanged: zoneEngine.closestPoint = zoneEngine.zoneDistance.getClosestPoint(Qt.vector2d(x,y))

        onTrackingGoalReached: {
            setCasualBackdriveAssistEnabled(true);
            clearTracking();
        }

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

                    Rectangle{
                        x: zoneEngine.closestPoint.x*parent.scaleCoeff - width/2
                        y: zoneEngine.closestPoint.y*parent.scaleCoeff - height/2
                        height: 10
                        width: 10
                        color: "#80FFFFFF"
                        radius: 5
                        z: 1
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

    Row{
        anchors.top: distText.bottom
        spacing: 5

        TextField{
            id: vel
            placeholderText: "Velocity (mm/s)"
        }

        TextField{
            id: w
            placeholderText: "w (rad/s)"
        }

        TextField{
            id: theta
            placeholderText: "Aligned theta (°)"
        }

        Button{
            text: "Follow the path"
            onClicked: {
                robotComm.setCasualBackdriveAssistEnabled(false);
                robotComm.polyBezierSetFromZone(zoneEngine.zoneDistance);
                robotComm.setGoalPolyBezier(parseFloat(vel.text), parseFloat(w.text));
            }
        }

        Button{
            text: "Follow the path (aligned)"
            onClicked: {
                robotComm.setCasualBackdriveAssistEnabled(false);
                robotComm.polyBezierSetFromZone(zoneEngine.zoneDistance);
                robotComm.setGoalPolyBezierAligned(parseFloat(vel.text), parseFloat(theta.text), parseFloat(w.text));
            }
        }
    }
}
