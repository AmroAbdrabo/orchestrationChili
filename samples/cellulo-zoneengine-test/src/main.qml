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

    function respondToZoneChange(robot, zone, value){
        switch(zone.name){

            //Statically added rectangle
        case "ZONE_RECTANGLE_INNER_STATIC":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "yellow", 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;

            //Circle
        case "ZONE_CIRCLE_INNER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "blue", 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_CIRCLE_BORDER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectBlink, "blue", 0);
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
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "yellow", 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_RECTANGLE_BORDER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectBlink, "yellow", 0);
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
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "purple", 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_REGULAR_POLYGON_BORDER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectBlink, "purple", 0);
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
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "green", 0);
            else
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "white", 0);
            break;
        case "ZONE_IRREGULER_POLYGON_BORDER":
            if(value === 1)
                robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectBlink, "green", 0);
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
            height: 30
            width: 50
            x: 150
            y: 30
            name: "ZONE_RECTANGLE_INNER_STATIC"
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
            Column{
                spacing: 5

                Row{
                    ComboBox {
                        id: combobox
                        currentIndex: 0
                        model: ListModel {
                            id: cbItems
                            ListElement { text: "Select a zone Type"}
                            ListElement { text: "CirlceInner"}
                            ListElement { text: "CircleBorder"}
                            ListElement { text: "RectangleInner" }
                        }
                        width: 200
                        onCurrentIndexChanged: {
                            switch(combobox.currentIndex) {
                            case 1:
                                console.debug("CircleInner selected");
                                circleInner.visible = true
                                circleBorder.visible = false
                                rectangleInner.visible = false
                                break;
                            case 2:
                                console.debug("CircleBorder selected");
                                circleInner.visible = false
                                circleBorder.visible = true
                                rectangleInner.visible = false
                                break;
                            case 3:
                                console.debug("RectangleInner selected");
                                circleInner.visible = false
                                circleBorder.visible = false
                                rectangleInner.visible = true
                                break;
                            default:
                                console.debug("No Action");
                            }
                        }
                    }
                    Button {
                        id: buttonAddChild
                        text: "add new child"
                        property var childTypeToBeAdd: combobox.currentIndex;

                        onClicked: {
                            var properties = {};

                            switch(combobox.currentIndex) {
                            case 1:
                                console.debug("CircleInner creation");
                                var r1 = parseFloat(rCircleInner.text)
                                var x1 = parseFloat(xCircleInner.text)
                                var y1 = parseFloat(yCircleInner.text)
                                if(!isNaN(r1) && !isNaN(x1) && !isNaN(y1)){
                                    properties["name"] = "zone" + zoneE.children.length
                                    properties["r"] = r1;
                                    properties["x"] = x1;
                                    properties["y"] = y1;
                                    zoneE.addNewZoneFromQML(CelluloZoneTypes.CIRCLEINNER, properties)
                                }
                                break;
                            case 2:
                                console.debug("CircleBorder creation");
                                var r2 = parseFloat(rCircleBorder.text)
                                var x2 = parseFloat(xCircleBorder.text)
                                var y2 = parseFloat(yCircleBorder.text)
                                var margin2 = parseFloat(marginCircleBorder.text)
                                if(!isNaN(r2) && !isNaN(x2) && !isNaN(y2) && !isNaN(margin2)){
                                    properties["name"] = "zone" + zoneE.children.length
                                    properties["r"] = r2;
                                    properties["x"] = x2;
                                    properties["y"] = y2;
                                    properties["marginThickeness"] = margin2;
                                    zoneE.addNewZoneFromQML(CelluloZoneTypes.CIRCLEBORDER, properties)
                                }

                                break;
                            case 3:
                                console.debug("RectangleInner creation");
                                var x3 = parseFloat(xRectangleInner.text)
                                var y3 = parseFloat(yRectangleInner.text)
                                var height3 = parseFloat(heightRectangleInner.text)
                                var width3 = parseFloat(widthRectangleInner.text)
                                if(!isNaN(x3) && !isNaN(y3) && !isNaN(height3) && !isNaN(width3)){
                                    properties["name"] = "zone" + zoneE.children.length
                                    properties["x"] = x3;
                                    properties["y"] = y3;
                                    properties["height"] = height3;
                                    properties["width"] = width3;
                                    zoneE.addNewZoneFromQML(CelluloZoneTypes.RECTANGLEINNER, properties)
                                }
                                break;
                            default:
                                console.debug("No Action");
                            }
                        }
                    }
                }


                Row{
                    spacing: 2
                    id: circleInner
                    visible: false
                    Label{
                        text: "r:"
                    }
                    TextField{
                        id: rCircleInner
                        placeholderText: "0.0"
                    }
                    Label{
                        text: "x:"
                    }
                    TextField{
                        id: xCircleInner
                        placeholderText: "0.0"
                    }
                    Label{
                        text: "y:"
                    }
                    TextField{
                        id: yCircleInner
                        placeholderText: "0.0"
                    }
                }
                Row{
                    spacing: 2
                    id: circleBorder
                    visible: false
                    Label{
                        text: "r:"
                    }
                    TextField{
                        id: rCircleBorder
                        placeholderText: "0.0"
                    }
                    Label{
                        text: "x:"
                    }
                    TextField{
                        id: xCircleBorder
                        placeholderText: "0.0"
                    }
                    Label{
                        text: "y:"
                    }
                    TextField{
                        id: yCircleBorder
                        placeholderText: "0.0"
                    }
                    Label{
                        text: "margin:"
                    }
                    TextField{
                        id: marginCircleBorder
                        placeholderText: "0.0"
                    }
                }

                Row{
                    spacing: 2
                    id: rectangleInner
                    visible: false
                    Label{
                        text: "x:"
                    }
                    TextField{
                        id: xRectangleInner
                        placeholderText: "0.0"
                    }
                    Label{
                        text: "y:"
                    }
                    TextField{
                        id: yRectangleInner
                        placeholderText: "0.0"
                    }
                    Label{
                        text: "height:"
                    }
                    TextField{
                        id: heightRectangleInner
                        placeholderText: "0.0"
                    }
                    Label{
                        text: "width:"
                    }
                    TextField{
                        id: widthRectangleInner
                        placeholderText: "0.0"
                    }


                }

                Button {
                    text: "Load from zones.json"
                    onClicked: zoneEngine.addNewZones(CelluloZoneJsonHandler.loadZonesQML(":/zones.json"))
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
