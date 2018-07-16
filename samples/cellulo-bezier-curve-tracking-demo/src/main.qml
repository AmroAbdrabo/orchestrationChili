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

        property vector2d closest: pbcurve.getPoint(pbcurve.getTByArcLengthRatio(pbcurve.getArcLengthRatioByT(pbcurve.getClosestT(Qt.vector2d(x,y)))))

        PolyBezierTracker{
            id: tracker

            PolyBezier{
                id: pbcurve
                Component.onCompleted: loadFromFile(":/assets/curve.json")
            }

            onEnabledChanged: console.log(enabled)
        }

        //poseVelControlKGoalPoseErr: Qt.vector3d(5,5,0.0)
        //poseVelControlKGoalVel: Qt.vector3d(0,0,0.0)
        //poseVelControlKGoalVelErr: Qt.vector3d(0,0,0)
    }

    //Visible items
    GroupBox {
        id: addressBox
        title: "Robots"

        Column{
            property var addresses: [
                "00:06:66:74:40:D2"
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

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        pbcurve.appendPoint(Qt.vector2d(mouse.x/page.scaleCoeff, mouse.y/page.scaleCoeff), 0.5, 0.5)
                    }
                }

                PolyBezierVisual{
                    anchors.fill: parent
                    scaleCoeff: page.scaleCoeff
                    controlPoints: pbcurve.controlPoints
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
                    x: robotComm.closest.x*parent.scaleCoeff - width/2
                    y: robotComm.closest.y*parent.scaleCoeff - height/2
                    height: 10*parent.scaleCoeff
                    width: 10*parent.scaleCoeff
                    transformOrigin: Item.Left
                    color: "#800000FF"
                    radius: 5*parent.scaleCoeff
                    z: 1
                }

                /*
                Rectangle{
                    x: robotComm.goalPos.x*parent.scaleCoeff
                    y: robotComm.goalPos.y*parent.scaleCoeff
                    height: 3*parent.scaleCoeff
                    width: 30*parent.scaleCoeff
                    transformOrigin: Item.TopLeft
                    rotation: Math.atan2(robotComm.goalVel.y, robotComm.goalVel.x)/Math.PI*180
                    color: "#80FF0000"
                    z: 1
                }*/
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


                //var pt = curve.getPoint(curve.getTByArcLengthRatio(0));



                //robotComm.polyBezierSetFromZone(zoneEngine.zoneClosestT);
                //robotComm.setGoalPolyBezier(parseFloat(vel.text), parseFloat(w.text));

                tracker.trackConstLinearVel(50, false);
            }
        }

        Button{
            text: "Removefirst"
            onClicked: {
                pbcurve.removeFirstSegment();
            }
        }

        Button{
            text: "Reset"
            onClicked: {
                pbcurve.loadFromFile(":/assets/curve.json")
            }
        }
    }
}
