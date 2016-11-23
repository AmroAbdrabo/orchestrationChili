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

    ToastManager{ id: toast }

    CelluloBluetoothRelayServer{
        id: server

        listen: true
    }

    ScrollView {
        anchors.fill: parent
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: mobile ? Qt.ScrollBarAsNeeded : Qt.ScrollBarAlwaysOff

        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 5

            Repeater{
                model: 6

                Text{
                    text: "Cellulo Relay Server"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Row{
                    CelluloBluetooth{
                        id: robot
                        macAddr: QMLCache.read("robot" + index + "MacAddr")
                        onMacAddrChanged: QMLCache.write("robot" + index + "MacAddr", macAddr)

                        Component.onCompleted: server.addRobot(robot)
                    }

                    Text{
                        text: "Robot " + (index + 1) + ":"
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    MacAddrSelector{
                        anchors.verticalCenter: parent.verticalCenter

                        addresses: window.robotAddresses
                        onConnectRequested: robot.macAddr = selectedAddress
                        onDisconnectRequested: {
                            robot.disconnectFromServer();
                            QMLCache.write("robot" + index + "MacAddr", "");
                        }
                        connectionStatus: robot.connectionStatus

                        Component.onCompleted: selectAddress(QMLCache.read("robot" + index + "MacAddr"))
                    }
                }
            }
        }
    }
}
