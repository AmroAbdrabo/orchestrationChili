import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    property bool mobile: Qt.platform.os === "android"
    minimumWidth: width
    minimumHeight: height
    //height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    function createRobot(macAddr){
        var newRobot = Qt.createQmlObject("import Cellulo 1.0; CelluloBluetooth{}", window);
        newRobot.autoConnect = false;
        newRobot.macAddr = macAddr;
        return newRobot;
    }

    CelluloLocalRelayClient{
        id: client

        Component.onCompleted: connectToServer()

        onConnected: {
            serverConnectedText.color = "green";
            serverConnectedText.text = "Connected to Server";
            toast.show("Connected to Server.");
        }
        onDisconnected: {
            serverConnectedText.color = "red";
            serverConnectedText.text = "Connecting to Server...";
            toast.show("Disconnected from Server.");
        }

        onUnknownRobotAtServer: {
            var robot = createRobot(macAddr);
            addRobot(robot, true);
        }
    }

    Column{
        spacing: 5

        GroupBox{
            title: "Server controls"

            Row{
                spacing: 5

                Button{
                    text: "Launch Server"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Button{
                    text: "Kill Server"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text{
                    id: serverConnectedText
                    text: "Connecting to Server..."
                    color: "red"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        GroupBox{
            title: "Robot list controls"

            Row{
                spacing: 5

                Text{
                    id: prefix
                    text: "00:06:66:74:"
                    anchors.verticalCenter: parent.verticalCenter
                }

                TextField{
                    id: suffix
                    placeholderText: "XX:XX"
                    anchors.verticalCenter: parent.verticalCenter

                    onAccepted: addButton.clicked()
                }

                Button{
                    id: addButton

                    text: "Add new robot"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        var robot = createRobot(prefix.text + suffix.text);
                        client.addRobot(robot);
                    }
                }
            }
        }

        GroupBox{
            title: "Robots on server"

            Column{
                id: robotList

                Repeater{
                    model: client.robots.length

                    MacAddrSelector{
                        addresses: [client.robots[index].macAddr]
                        connectionStatus: client.robots[index].connectionStatus

                        onConnectRequested: {
                            client.robots[index].localAdapterMacAddr = selectedLocalAdapterAddress;
                            client.robots[index].macAddr = selectedAddress;
                            client.robots[index].connectToServer();
                        }

                        onDisconnectRequested: client.robots[index].disconnectFromServer()
                    }
                }
            }
        }

        GroupBox{
            title: "Robot mass control"

            Row{
                spacing: 5

                Button{
                    text: "Reset all"
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked:{
                        for(var i=0;i<client.robots.length;i++)
                            client.robots[i].reset();
                    }
                }
                Button{
                    text: "Shutdown all"
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked:{
                        for(var i=0;i<client.robots.length;i++)
                            client.robots[i].shutdown();
                    }
                }
            }
        }
    }

    ToastManager{ id: toast }
}
