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
    width: 640
    height: 480

    Column{
        spacing: 5

        MacAddrSelector{
            addresses: [
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
            onConnectRequested: robot.macAddr = selectedAddress
            onDisconnectRequested: robot.disconnectFromServer()
            connectionStatus: robot.connectionStatus
        }

        Text{ text: "x error = " + (robot.x - goalPose.x).toFixed(2) }
        Text{ text: "y error = " + (robot.y - goalPose.y).toFixed(2) }
        Text{
            text: {
                var err = robot.theta - goalPose.z;
                while(err < -180)
                    err += 360;
                while(err >= 180)
                    err -= 360;
                return "theta error = " + err.toFixed(2);
            }
        }
        Text{ text: "Vx error = " + (robot.vxyw.x - goalVel.x).toFixed(2) }
        Text{ text: "Vy error = " + (robot.vxyw.y - goalVel.y).toFixed(2) }
        Text{ text: "w error = " + (robot.vxyw.z - goalVel.z).toFixed(2) }

        Item{
            width: page.width + page.physicalRobotWidth*page.scaleCoeff
            height: page.height + page.physicalRobotWidth*page.scaleCoeff

            Rectangle{
                id: page

                anchors.centerIn: parent

                property real physicalWidth: 400        ///< Physical paper width in mm
                property real physicalHeight: 400       ///< Physical paper height in mm
                property real physicalRobotWidth: 75    ///< Physical robot width in mm

                width: height*physicalWidth/physicalHeight
                height: Screen.height/3

                property real scaleCoeff: width/physicalWidth

                color: "#EEEEEE"
                border.color: "black"
                border.width: 2
                radius: 5

                Image{
                    visible: robot.connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected
                    source: "../assets/greenHexagon.svg"
                    rotation: robot.theta
                    x: robot.x*parent.scaleCoeff - width/2
                    y: robot.y*parent.scaleCoeff - height/2
                    width: parent.physicalRobotWidth*parent.scaleCoeff
                    fillMode: Image.PreserveAspectFit
                }

                Image{
                    source: "../assets/yellowHexagon.svg"
                    rotation: root.goalPose.z
                    x: root.goalPose.x*parent.scaleCoeff - width/2
                    y: root.goalPose.y*parent.scaleCoeff - height/2
                    width: parent.physicalRobotWidth*parent.scaleCoeff
                    fillMode: Image.PreserveAspectFit
                }

                Image{
                    source: "../assets/arrowRed.svg"
                    rotation: Math.atan2(root.goalVel.y, root.goalVel.x)/Math.PI*180
                    x: (root.goalPose.x)*parent.scaleCoeff - width/2
                    y: (root.goalPose.y)*parent.scaleCoeff - height/2
                    width: parent.linearVel*parent.scaleCoeff
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    property vector3d goalPose: Qt.vector3d(0,0,0)
    property vector3d goalVel: Qt.vector3d(0,0,0)

    CelluloRobot{
        id: robot

        poseVelControlEnabled: true
        poseVelControlPeriod: 50

        onNextGoalPoseVelRequested: {
            calcGoalPoseVel();
            setGoalPoseAndVelocity(root.goalPose.x, root.goalPose.y, root.goalPose.z, root.goalVel.x, root.goalVel.y, root.goalVel.z);
        }
    }

    property real motionPeriod: 10000
    property vector2d motionCenter: Qt.vector2d(200, 200)
    property real motionR: 100
    property real linearVel: motionR*2*Math.PI/motionPeriod*1000
    property real angularVel: 2*Math.PI/(motionPeriod/2)*1000

    function calcGoalPoseVel(){
        var motionTime = Date.now() % motionPeriod;
        var motionT = 2*Math.PI*motionTime/motionPeriod;

        goalPose.x = motionCenter.x + motionR*Math.cos(motionT);
        goalPose.y = motionCenter.y + motionR*Math.sin(motionT);
        if(motionT < Math.PI)
            goalPose.z = motionT*2;
        else
            goalPose.z = 2*Math.PI - (motionT - Math.PI)*2;
        goalPose.z = goalPose.z/Math.PI*180;

        goalVel.x = linearVel*(-Math.sin(motionT));
        goalVel.y = linearVel*(Math.cos(motionT));
        if(motionT < Math.PI)
            goalVel.z = angularVel;
        else
            goalVel.z = -angularVel;
    }
}
