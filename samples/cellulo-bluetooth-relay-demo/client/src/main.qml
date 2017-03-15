import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import QMLCache 1.0
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    property bool mobile: Qt.platform.os === "android"
    property real gWidth: mobile ? Screen.width : 640
    width: gWidth
    height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    property variant robotAddresses: [
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

    CelluloTcpRelayClient{
        id: client

        port: 1234

        Component.onCompleted: connectToServer()

        onConnected: console.log("Client: Connected to server.")
        onDisconnected: console.log("Client: Disconnected from server.")
    }

    CelluloBluetooth{
        id: robot1

        macAddr: "00:06:66:74:41:03"
        autoConnect: false

        Component.onCompleted: client.addRobot(robot1)

        onPoseChanged: console.log("Client: " + macAddr + " pose changed: " + x + " " + y + " " + theta)
    }


    CelluloBluetooth{
        id: robot2

        macAddr: "00:06:66:74:46:58"
        autoConnect: false

        Component.onCompleted: client.addRobot(robot2)

        onPoseChanged: console.log("Client: " + macAddr + " pose changed: " + x + " " + y + " " + theta)
    }

    CelluloBluetooth{
        id: robot3

        macAddr: "00:06:66:74:43:00"
        autoConnect: false

        Component.onCompleted: client.addRobot(robot3)

        onPoseChanged: console.log("Client: " + macAddr + " pose changed: " + x + " " + y + " " + theta)
    }

    Column{
        MacAddrSelector{
            addresses: window.robotAddresses
            connectionStatus: robot1.connectionStatus

            onConnectRequested: robot1.connectToServer()
            onDisconnectRequested: robot1.disconnectFromServer()

            Component.onCompleted: selectAddress(robot1.macAddr)
        }

        MacAddrSelector{
            addresses: window.robotAddresses
            connectionStatus: robot2.connectionStatus

            onConnectRequested: robot2.connectToServer()
            onDisconnectRequested: robot2.disconnectFromServer()

            Component.onCompleted: selectAddress(robot2.macAddr)
        }

        MacAddrSelector{
            addresses: window.robotAddresses
            connectionStatus: robot3.connectionStatus

            onConnectRequested: robot3.connectToServer()
            onDisconnectRequested: robot3.disconnectFromServer()

            Component.onCompleted: selectAddress(robot3.macAddr)
        }

        Button{
            text: "reset"

            onClicked: {
                robot1.reset();
                robot2.reset();
                robot3.reset();
            }
        }

        Button{
            text: "shutdown"

            onClicked: {
                robot1.shutdown();
                robot2.shutdown();
                robot3.shutdown();
            }
        }

        Button{
            text: "setperiod"

            onClicked: {
                robot1.setPoseBcastPeriod(0);
                robot2.setPoseBcastPeriod(0);
                robot3.setPoseBcastPeriod(0);
            }
        }

        Button{
            text: "go"

            onClicked: {
                robot1.setGoalPose(105, 186, 30, 150, 5);
                robot2.setGoalPose(105, 110, 30, 150, 5);
            }

        }
    }
}
