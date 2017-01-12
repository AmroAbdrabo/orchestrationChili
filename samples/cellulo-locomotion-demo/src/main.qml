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
    minimumHeight: height
    minimumWidth: width

    GroupBox {
        id: addressBox
        title: "Robot"

        Row{
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
                    "00:06:66:74:46:58",
                    "00:06:66:74:46:60",
                    "00:06:66:74:48:A7"
                ]
                onConnectRequested: robotComm.macAddr = selectedAddress
                onDisconnectRequested: robotComm.disconnectFromServer()
                connectionStatus: robotComm.connectionStatus
            }
            Button {
                text: "Reset"
                onClicked: robotComm.reset();
            }
            Button {
                text: "Shutdown"
                onClicked: robotComm.shutdown();
            }
        }
    }

    GroupBox {
        id: locomotionBox
        title: "Locomotion"

        anchors.top:  addressBox.bottom

        Column{
            spacing: 5

            Text{
                text: "X=" + robotComm.x.toFixed(2) + " Y=" + robotComm.y.toFixed(2) + " Theta=" + robotComm.theta.toFixed(1)
            }

            Row{
                Label{
                    text: "X goal (mm):"
                }
                TextField{
                    id: xGoalField
                    text: "105"
                }
            }

            Row{
                Label{
                    text: "Y goal (mm):"
                }
                TextField{
                    id: yGoalField
                    text: "148.5"
                }
            }

            Row{
                Label{
                    text: "Theta goal (deg):"
                }
                TextField{
                    id: thetaGoalField
                    text: "30"
                }
            }

            Row{
                Label{
                    text: "Linear max vel (mm/s):"
                }
                TextField{
                    id: linMaxVelField
                    text: "150"
                }
            }

            Row{
                Label{
                    text: "Angular max vel (rad/s):"
                }
                TextField{
                    id: angMaxVelField
                    text: "5"
                }
            }

            Button{
                text: "Go"
                onClicked: robotComm.setGoalPose(
                               parseFloat(xGoalField.text), parseFloat(yGoalField.text), parseFloat(thetaGoalField.text),
                               parseFloat(linMaxVelField.text), parseFloat(angMaxVelField.text));
            }
        }
    }

    CelluloRobot{
        id: robotComm
        onConnectionStatusChanged: {
            if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#0F0F0F", 0);
        }
        onBootCompleted: setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#0F0F0F", 0)
        onTrackingGoalReached: setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0), 0)
    }
}
