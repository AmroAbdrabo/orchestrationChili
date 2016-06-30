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

    property color colorRect:   "#80FFFF00"
    property color colorCirc:   "#800000FF"
    property color colorRpoly:  "#80FF00FF"
    property color colorIrpoly: "#8000FF00"
    property color colorPoint:  "#80FF0000"
    property color colorLine:   "#8000FFFF"

    function respondToZoneChange(robot, zone, value){
        console.log(zone.name);

        switch(zone.name){

            //Statically added rectangle
        case "ZONE_RECTANGLE_INNER_STATIC":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, colorRect, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;

            //Circle
        case "ZONE_CIRCLE_INNER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, colorCirc, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_CIRCLE_BORDER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectBlink, colorCirc, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_CIRCLE_DISTANCE":
            var distances = robot.zoneDistances;
            distances[zone.name] = value;
            robot.zoneDistances = distances;
            break;

            //Rectangle
        case "ZONE_RECTANGLE_INNER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, colorRect, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_RECTANGLE_BORDER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectBlink, colorRect, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_RECTANGLE_DISTANCE":
            var distances = robot.zoneDistances;
            distances[zone.name] = value;
            robot.zoneDistances = distances;
            break;

            //Line
        case "ZONE_LINE_DISTANCE":
            var distances = robot.zoneDistances;
            distances[zone.name] = value;
            robot.zoneDistances = distances;
            break;

            //Point
        case "ZONE_POINT_DISTANCE":
            var distances = robot.zoneDistances;
            distances[zone.name] = value;
            robot.zoneDistances = distances;
            break;

            //Regular polygon
        case "ZONE_REGULAR_POLYGON_INNER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, colorRpoly, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_REGULAR_POLYGON_BORDER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectBlink, colorRpoly, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_REGULAR_POLYGON_DISTANCE":
            var distances = robot.zoneDistances;
            distances[zone.name] = value;
            robot.zoneDistances = distances;
            break;

            //Irregular polygon
        case "ZONE_IRREGULAR_POLYGON_INNER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, colorIrpoly, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_IRREGULAR_POLYGON_BORDER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectBlink, colorIrpoly, 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_IRREGULAR_POLYGON_DISTANCE":
            var distances = robot.zoneDistances;
            distances[zone.name] = value;
            robot.zoneDistances = distances;
            break;

        default:
            console.log("Unknown zone change");
            break;
        }
    }

    CelluloBluetooth{
        id: robotComm1

        property string robotName: "robot1"
        property variant zoneDistances: []

        Component.onCompleted: zoneEngine.addNewClient(robotComm1)

        onZoneValueChanged: respondToZoneChange(robotComm1, zone, value)
    }

    CelluloBluetooth{
        id: robotComm2

        property string robotName: "robot2"
        property variant zoneDistances: []

        Component.onCompleted: zoneEngine.addNewClient(robotComm2)

        onZoneValueChanged: respondToZoneChange(robotComm2, zone, value)
    }

    CelluloZoneEngine{
        id: zoneEngine

        CelluloZoneRectangleInner{
            id: staticZone

            height: 30
            width: 50
            x: 150
            y: 30
            name: "ZONE_RECTANGLE_INNER_STATIC"
        }

        CelluloZoneRectangleInner{
            id: staticZone2

            height: 30
            width: 50
            x: 80
            y: 30
            name: "ZONE_RECTANGLE_INNER_STATIC2"
        }
    }

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
                onConnectRequested: robotComm1.macAddr = selectedAddress
                onDisconnectRequested: robotComm1.disconnectFromServer()
                connectionStatus: robotComm1.connectionStatus
            }

            MacAddrSelector{
                addresses: parent.addresses
                onConnectRequested: robotComm2.macAddr = selectedAddress
                onDisconnectRequested: robotComm2.disconnectFromServer()
                connectionStatus: robotComm2.connectionStatus
            }
        }
    }

    GroupBox {
        id: zoneCreationBox
        title: "Zone creation"
        anchors.top: addressBox.bottom

        Row{
            Button{
                text: "Clear all zones"
                onClicked: zoneEngine.clearZones()
            }

            Button{
                text: "Load from zones.json"

                function getColorFromZoneType(zoneType){
                    switch(zoneType){
                    case CelluloZoneTypes.CIRCLEBORDER:
                    case CelluloZoneTypes.CIRCLEDISTANCE:
                    case CelluloZoneTypes.CIRCLEINNER:
                        return colorCirc;
                    case CelluloZoneTypes.RECTANGLEBORDER:
                    case CelluloZoneTypes.RECTANGLEDISTANCE:
                    case CelluloZoneTypes.RECTANGLEINNER:
                        return colorRect;
                    case CelluloZoneTypes.RPOLYGONBORDER:
                    case CelluloZoneTypes.RPOLYGONDISTANCE:
                    case CelluloZoneTypes.RPOLYGONINNER:
                        return colorRpoly;
                    case CelluloZoneTypes.IRPOLYGONBORDER:
                    case CelluloZoneTypes.IRPOLYGONDISTANCE:
                    case CelluloZoneTypes.IRPOLYGONINNER:
                        return colorIrpoly;
                    case CelluloZoneTypes.POINTDISTANCE:
                        return colorPoint;
                    case CelluloZoneTypes.LINEDISTANCE:
                        return colorLine;
                    }
                }

                onClicked: {
                    var zones = CelluloZoneJsonHandler.loadZonesQML(":/zones.json");
                    for(var i=0;i<zones.length;i++)
                        zones[i].createPaintedItem(page, getColorFromZoneType(zones[i].type), page.physicalWidth, page.physicalHeight);
                    zoneEngine.addNewZones(zones);
                }
            }
        }
    }

    GroupBox{
        id: playgroundBox
        title: "Playground"
        anchors.top: zoneCreationBox.bottom

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
                property real gridSpacing: 0.508

                color: "#EEEEEE"
                border.color: "black"
                border.width: 2
                radius: 5

                CelluloZonePaintedItem{
                    color: colorRect
                    physicalPlaygroundWidth: parent.physicalWidth
                    physicalPlaygroundHeight: parent.physicalHeight
                    associatedZone: staticZone
                }

                CelluloZonePaintedItem{
                    color: colorRect
                    physicalPlaygroundWidth: parent.physicalWidth
                    physicalPlaygroundHeight: parent.physicalHeight
                    associatedZone: staticZone2
                }

                Image{
                    source: robotComm1.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
                    rotation: -robotComm1.theta //QML wants clockwise angle for some reason
                    x: robotComm1.x*parent.gridSpacing*parent.scaleCoeff - width/2
                    y: robotComm1.y*parent.gridSpacing*parent.scaleCoeff - height/2
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

                Image{
                    source: robotComm2.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
                    rotation: -robotComm2.theta //QML wants clockwise angle for some reason
                    x: robotComm2.x*parent.gridSpacing*parent.scaleCoeff - width/2
                    y: robotComm2.y*parent.gridSpacing*parent.scaleCoeff - height/2
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

    GroupBox{
        id: distanceInfoBox
        title: "Robot distances to zones"
        anchors.top: playgroundBox.top
        anchors.left: playgroundBox.right

        Column{
            Text{ text: "Robot1 distance to ZONE_CIRCLE_DISTANCE is " +             robotComm1.zoneDistances["ZONE_CIRCLE_DISTANCE"] }
            Text{ text: "Robot1 distance to ZONE_RECTANGLE_DISTANCE is " +          robotComm1.zoneDistances["ZONE_RECTANGLE_DISTANCE"] }
            Text{ text: "Robot1 distance to ZONE_LINE_DISTANCE is " +               robotComm1.zoneDistances["ZONE_LINE_DISTANCE"] }
            Text{ text: "Robot1 distance to ZONE_POINT_DISTANCE is " +              robotComm1.zoneDistances["ZONE_POINT_DISTANCE"] }
            Text{ text: "Robot1 distance to ZONE_REGULAR_POLYGON_DISTANCE is " +    robotComm1.zoneDistances["ZONE_REGULAR_POLYGON_DISTANCE"] }
            Text{ text: "Robot1 distance to ZONE_IRREGULAR_POLYGON_DISTANCE is " +  robotComm1.zoneDistances["ZONE_IRREGULAR_POLYGON_DISTANCE"] }

            Item{ height: 25; width: 1}

            Text{ text: "Robot2 distance to ZONE_CIRCLE_DISTANCE is " +             robotComm2.zoneDistances["ZONE_CIRCLE_DISTANCE"] }
            Text{ text: "Robot2 distance to ZONE_RECTANGLE_DISTANCE is " +          robotComm2.zoneDistances["ZONE_RECTANGLE_DISTANCE"] }
            Text{ text: "Robot2 distance to ZONE_LINE_DISTANCE is " +               robotComm2.zoneDistances["ZONE_LINE_DISTANCE"] }
            Text{ text: "Robot2 distance to ZONE_POINT_DISTANCE is " +              robotComm2.zoneDistances["ZONE_POINT_DISTANCE"] }
            Text{ text: "Robot2 distance to ZONE_REGULAR_POLYGON_DISTANCE is " +    robotComm2.zoneDistances["ZONE_REGULAR_POLYGON_DISTANCE"] }
            Text{ text: "Robot2 distance to ZONE_IRREGULAR_POLYGON_DISTANCE is " +  robotComm2.zoneDistances["ZONE_IRREGULAR_POLYGON_DISTANCE"] }
        }
    }
}
