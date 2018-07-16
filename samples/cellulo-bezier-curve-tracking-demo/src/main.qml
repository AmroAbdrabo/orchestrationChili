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

        PolyBezierTracker{
            id: tracker

            PolyBezier{
                id: pbcurve
                Component.onCompleted: loadFromFile(":/assets/curve.json")
            }

            goToStartFirst: goToStartFirstCheckbox.checked
            stopWhenGoalReached: stopWhenGoalReachedCheckbox.checked

            onStartReached: console.info("Start of the curve reached.")
            onEndReached: console.info("End of the curve reached.")
        }
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
                    x: tracker.trackedPose.x*parent.scaleCoeff - width/2
                    y: tracker.trackedPose.y*parent.scaleCoeff - height/2
                    height: 10*parent.scaleCoeff
                    width: 10*parent.scaleCoeff
                    transformOrigin: Item.Left
                    color: "#800000FF"
                    radius: 5*parent.scaleCoeff
                    z: 1
                }

                Rectangle{
                    x: tracker.trackedPose.x*parent.scaleCoeff
                    y: tracker.trackedPose.y*parent.scaleCoeff
                    height: 3*parent.scaleCoeff
                    width: 30*parent.scaleCoeff
                    transformOrigin: Item.Left
                    rotation: Math.atan2(tracker.trackedVelocity.y, tracker.trackedVelocity.x)/Math.PI*180
                    color: "#80FF0000"
                    z: 1
                }
            }
        }
    }

    GroupBox{
        id: controlsBox
        title: "Controls"
        anchors.top: playgroundBox.bottom

        Column{
            spacing: 5

            Row{
                spacing: 5

                CheckBox{
                    id: goToStartFirstCheckbox
                    text: "Go to start of the curve first"
                    checked: true
                }

                CheckBox{
                    id: stopWhenGoalReachedCheckbox
                    text: "Stop tracker when end is reached"
                    checked: false
                }
            }

            Row{
                spacing: 5

                Text{
                    text: "(1) Constant velocity tracker:"
                    anchors.verticalCenter: parent.verticalCenter
                }

                TextField{
                    id: velText
                    placeholderText: "Velocity (mm/s)"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Button{
                    text: "Start"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        var vel = parseInt(velText.text);
                        if(!isNaN(vel))
                            tracker.trackConstLinearVel(vel);
                        else
                            console.error("Please enter a valid velocity to the text box.");
                    }
                }

                Button{
                    text: "Stop"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: tracker.enabled = false
                }

                Text{
                    text: tracker.enabled ? "Running" : "Not running"
                    color: tracker.enabled ? "green" : "black"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}
