import QtQuick 2.2
import QtQuick.Shapes 1.0
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

    CelluloRobot{
        id: robotComm

        onConnectionStatusChanged: {
            if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected){
                setCasualBackdriveAssistEnabled(true);
                setPoseBcastPeriod(0);
            }
        }

        onTrackingGoalReached: {
            setCasualBackdriveAssistEnabled(true);
            clearTracking();
        }
    }

    //Visible items

    GroupBox {
        id: addressBox
        title: "Robots"

        Column{
            property var addresses: [
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

                Shape{
                    anchors.fill: parent

                    ShapePath{
                        id: curveVisual
                        strokeWidth: 2
                        strokeColor: "black"
                        fillColor: "transparent"

                        function start(startPoint){
                            startX = Qt.binding(function(){ return startPoint.x*page.scaleCoeff; });
                            startY = Qt.binding(function(){ return startPoint.y*page.scaleCoeff; });
                        }

                        function addCubic(cp1, cp2, end){
                            var newCubic = Qt.createQmlObject('
                                import QtQuick 2.0; \
                                import QtQuick.Shapes 1.0; \
                                \
                                PathCubic{ \
                                    control1X: ' + cp1.x + '*page.scaleCoeff; \
                                    control1Y: ' + cp1.y + '*page.scaleCoeff; \
                                    control2X: ' + cp2.x + '*page.scaleCoeff; \
                                    control2Y: ' + cp2.y + '*page.scaleCoeff; \
                                    x: ' + end.x + '*page.scaleCoeff; \
                                    y: ' + end.y + '*page.scaleCoeff; \
                                }',
                                curveVisual);
                            var pathElements_ = []; //var pathElements_ = pathElements; doesn't work, not a plain Javascript array
                            for(var i=0;i<pathElements.length;i++)
                                pathElements_.push(pathElements[i]);
                            pathElements_.push(newCubic);
                            pathElements = pathElements_;
                        }
                    }
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




                Rectangle{
                    id: marker
                    x: realCoords.x*parent.scaleCoeff - width/2
                    y: realCoords.y*parent.scaleCoeff - height/2
                    height: 10*parent.scaleCoeff
                    width: 10*parent.scaleCoeff
                    transformOrigin: Item.Center
                    color: "#800000FF"
                    radius: 5
                    z: 1

                    property vector2d realCoords: Qt.vector2d(0,0)
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

            PolyBezier{
                id: curve

                Component.onCompleted: {
                    loadFromFile(":/assets/curve.json");

                    curveVisual.start(controlPoints[0]);
                    console.log(controlPoints.length)
                    for(var i=1;i<controlPoints.length;i+=3)
                        curveVisual.addCubic(controlPoints[i], controlPoints[i + 1], controlPoints[i + 2]);
                }
            }

            onClicked: {
                robotComm.setCasualBackdriveAssistEnabled(false);

                tim.restart();

                var pt = curve.getPoint(curve.getTByArcLengthRatio(0));



                //robotComm.polyBezierSetFromZone(zoneEngine.zoneClosestT);
                //robotComm.setGoalPolyBezier(parseFloat(vel.text), parseFloat(w.text));
            }
        }

        Timer{
            id: tim
            repeat: true
            interval: 10
            onTriggered: {
                r += 0.001;
                if(r > 1)
                    r = 0;
                var pt = curve.getPoint(curve.getTByArcLengthRatio(r));
                marker.realCoords = pt;

                console.log(prevpos.minus(pt).length());

                //console.log(curve.getTByArcLengthRatio(r) + " " + r);

                prevpos = pt;
            }

            property real r: 0
            property vector2d prevpos: Qt.vector2d(0,0)
        }

        Button{
            text: "Follow the path (aligned)"
            onClicked: {
                robotComm.setCasualBackdriveAssistEnabled(false);
                robotComm.polyBezierSetFromZone(zoneEngine.zoneClosestT);
                robotComm.setGoalPolyBezierAligned(parseFloat(vel.text), parseFloat(theta.text), parseFloat(w.text));
            }
        }
    }
}
