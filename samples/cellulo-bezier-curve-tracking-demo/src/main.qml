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

        poseVelControlPeriod: 100 //ms
        property real targetVel: 185 //mm/s
        property real rInc: 0

        property real currentR: 0

        property vector2d goalPos: Qt.vector2d(0,0)
        property vector2d goalVel: Qt.vector2d(0,0)

        poseVelControlKGoalPoseErr: Qt.vector3d(5,5,0.0)
        poseVelControlKGoalVel: Qt.vector3d(0,0,0.0)
        poseVelControlKGoalVelErr: Qt.vector3d(0,0,0)

        onNextGoalPoseVelRequested: {
            if(poseVelControlEnabled){
                var goalT = curve.getTByArcLengthRatio(currentR);
                goalPos = curve.getPoint(goalT);
                goalVel = curve.getTangent(goalT).normalized().times(targetVel);

                currentR += rInc;
                if(currentR > 1.0){
                    //setGoalVelocity(0,0,0);
                    currentR = 0.0;
                    //poseVelControlEnabled = false;
                }
                //else{
                    setGoalPoseAndVelocity(goalPos.x, goalPos.y, 0, goalVel.x, goalVel.y, 0, true, true, false);

                //}
            }
            else
                setGoalVelocity(0,0,0);
        }

        function startTracking(){
            currentR = 0;
            robotComm.poseVelControlEnabled = true;
        }
    }

    PolyBezier{
        id: curve

        Component.onCompleted: {
            loadFromFile(":/assets/curve.json");
            curveVisual.start(controlPoints[0]);
            for(var i=1;i<controlPoints.length;i+=3)
                curveVisual.addCubic(controlPoints[i], controlPoints[i + 1], controlPoints[i + 2]);
        }

        onControlPointsChanged: robotComm.rInc = (robotComm.targetVel*robotComm.poseVelControlPeriod/1000)/getArcLength()
    }

    //Visible items

    GroupBox {
        id: addressBox
        title: "Robots"

        Column{
            property var addresses: [
                "00:06:66:D2:CF:96"
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
                    x: robotComm.goalPos.x*parent.scaleCoeff - width/2
                    y: robotComm.goalPos.y*parent.scaleCoeff - height/2
                    height: 10*parent.scaleCoeff
                    width: 10*parent.scaleCoeff
                    transformOrigin: Item.Left
                    color: "#800000FF"
                    radius: 5*parent.scaleCoeff
                    z: 1
                }

                Rectangle{
                    x: robotComm.goalPos.x*parent.scaleCoeff
                    y: robotComm.goalPos.y*parent.scaleCoeff
                    height: 3*parent.scaleCoeff
                    width: 30*parent.scaleCoeff
                    transformOrigin: Item.TopLeft
                    rotation: Math.atan2(robotComm.goalVel.y, robotComm.goalVel.x)/Math.PI*180
                    color: "#80FF0000"
                    z: 1
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


                //var pt = curve.getPoint(curve.getTByArcLengthRatio(0));



                //robotComm.polyBezierSetFromZone(zoneEngine.zoneClosestT);
                //robotComm.setGoalPolyBezier(parseFloat(vel.text), parseFloat(w.text));

                robotComm.startTracking();
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
