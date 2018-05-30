import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.2
import Cellulo 1.0
import QMLCache 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: height
    minimumWidth: width

    ToastManager{ id: toast }

    CelluloRobot{
        id: robot
        onConnectionStatusChanged:{
            if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                init();
        }

        function init(){
            setPoseBcastPeriod(0);
        }

        function start(){
            currentGoal = 0;
            next();
        }

        function next(){
            setGoalPose(goals[currentGoal].x, goals[currentGoal].y, goals[currentGoal].z, 185, 7.5);
            currentGoal++;
            //if()
        }

        property vector2d startPos: Qt.vector2d(105, 52.5)
        property vector2d endPos: Qt.vector2d(105, 244.5)

        property var goals: [
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 0)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 0)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 0)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 30)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 30)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 30)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 60)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 60)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 60)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 90)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 90)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 90)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 120)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 120)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 120)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 150)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 150)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 150)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 180)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 180)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 180)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 210)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 210)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 210)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 240)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 240)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 240)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 270)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 270)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 270)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 300)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 300)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 300)),
            startPos.toVector3d().plus(Qt.vector3d(0, 0, 330)),
            endPos.toVector3d().plus(Qt.vector3d(0, 0, 330))
        ]
        property int currentGoal: 0

        onPoseChanged: {
            var linearError = goals[currentGoal].toVector2d().minus(Qt.vector2d(x,y))

        }

        onTrackingGoalReached: {
            if(!trackingGoalDelay.running && currentGoal < goals.length){
                trackingGoalDelay.start();
                next();
            }
        }
    }

    CelluloBluetoothScanner{
        id: scanner
        onRobotDiscovered: {
            var newAddresses = macAddrSelector.addresses;
            if(newAddresses.indexOf(macAddr) < 0){
                toast.show(macAddr + " discovered.");
                newAddresses.push(macAddr);
                newAddresses.sort();
            }
            macAddrSelector.addresses = newAddresses;
            QMLCache.write("addresses", macAddrSelector.addresses.join(','));
        }
    }

    GroupBox {
        id: addressBox
        title: "Robot"

        Row{
            spacing: 5

            Row{
                spacing: 5

                BusyIndicator{
                    running: scanner.scanning
                    height: scanButton.height
                }

                Button{
                    id: scanButton
                    text: "Scan"
                    onClicked: scanner.start()
                }

                Button{
                    text: "Clear List"
                    onClicked: {
                        macAddrSelector.addresses = [];
                        QMLCache.write("addresses","");
                    }
                }
            }

            MacAddrSelector{
                id: macAddrSelector
                addresses: QMLCache.read("addresses").split(",")
                onConnectRequested: {
                    robot.localAdapterMacAddr = selectedLocalAdapterAddress;
                    robot.macAddr = selectedAddress;
                }
                onDisconnectRequested: robot.disconnectFromServer()
                connectionStatus: robot.connectionStatus
            }
        }
    }

    GroupBox {
        id: controlsBox
        title: "Controls"

        anchors.top: addressBox.bottom

        Row{
            spacing: 5
            Button {
                text: "start"
                onClicked: robot.start()
            }
            Button {
                text: "Reset"
                onClicked: robot.reset()
            }
            Button {
                text: "Shutdown"
                onClicked: robot.shutdown()
            }
        }
    }

    Rectangle{
        id: page
        anchors.top: controlsBox.bottom
        anchors.left: parent.left

        property real scaleCoeff: Math.min((Screen.width*0.8)/210, (Screen.height*0.8 - addressBox.height)/297)

        width: 210*scaleCoeff
        height: 297*scaleCoeff
        color: "#EEEEEE"
        border.color: "black"
        border.width: 2
        radius: 5

        Image{
            source: "../assets/paper.svg"
            width: 210*parent.scaleCoeff
            height: 297*parent.scaleCoeff
        }

        Image{
            source: robot.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
            rotation: robot.theta
            visible: robot.connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected
            x: robot.x*parent.scaleCoeff - width/2
            y: robot.y*parent.scaleCoeff - height/2
            sourceSize.width: 75*parent.scaleCoeff
            sourceSize.height: 85*parent.scaleCoeff
        }
    }
}
