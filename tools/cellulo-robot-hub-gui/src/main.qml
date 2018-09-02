import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import QMLBluetoothExtras 1.0
import QMLExtraDataStructures 1.0
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    property bool mobile: android
    property bool android: Qt.platform.os === "android"
    property bool osx: Qt.platform.os === "osx"

    minimumWidth: width
    minimumHeight: height

    width: mobile ? Screen.width : 0.7*Screen.width
    height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    function createRobot(macAddr){
        var newRobot = Qt.createQmlObject("import Cellulo 1.0; CelluloBluetooth{}", window);
        newRobot.autoConnect = false;
        newRobot.macAddr = macAddr;
        return newRobot;
    }

    CelluloRobotHubClient{
        id: client

        serverAddress: "192.168.2.1"

        onConnected: toast.show("Connected to Server.")
        onDisconnected: toast.show("Disconnected from Server.")

        onUnknownRobotAtServer: {
            var robot = createRobot(macAddr);
            addRobot(robot, true);
        }

        function hasRobot(macAddr){
            for(var i=0;i<robots.length;i++)
                if(robots[i].macAddr.toUpperCase() === macAddr.toUpperCase())
                    return true;
            return false;
        }
    }


    ScrollView {
        anchors.fill: parent
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: mobile ? Qt.ScrollBarAsNeeded : Qt.ScrollBarAlwaysOff

        Row{
            spacing: 5

            Column{
                spacing: 5

                GroupBox{
                    title: "Server status"

                    Column{
                        spacing: 5

                        Text{
                            text: client.connected ? "Connected to Server." : "Connecting to Server... " + (Qt.platform.os === "osx" ? "\n(must launch \"Cellulo Robot Pool Daemon\" manually on macOS)" : "")
                            color: client.connected ? "green" : "red"
                        }

                        Text{
                            text: "Local adapters on server: " + client.localAdapters
                        }
                    }
                }

                GroupBox{
                    title: "Manually add robot"

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

                            text: "+"
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

                    enabled: client.connected

                    Column{
                        id: robotList

                        RepeaterList{
                            id: robotListMacAddrSelectors

                            model: client.robots.length

                            Row{
                                spacing: 5

                                property var selectorAtRow: selector

                                MacAddrSelector{
                                    id: selector
                                    property var robot: client.robots[index]
                                    property string localAdapterMacAddr: robot.localAdapterMacAddr

                                    addresses: [robot.macAddr]
                                    localAdapterAddresses: client.localAdapters
                                    connectionStatus: robot.connectionStatus

                                    onConnectionStatusChanged: {
                                        if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                                            robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectAlertAll,"#800080",3);
                                    }

                                    onLocalAdapterMacAddrChanged: selectLocalAdapterAddress(localAdapterMacAddr.toUpperCase())

                                    onConnectRequested: {
                                        robot.localAdapterMacAddr = selectedLocalAdapterAddress;
                                        robot.macAddr = selectedAddress;
                                        robot.connectToServer();
                                    }

                                    onDisconnectRequested: robot.disconnectFromServer()
                                }
                            }
                        }

                        Row{
                            spacing: 5

                            Button{
                                text: "Equally distribute local adapters"
                                onClicked:{
                                    for(var i=0;i<client.robots.length;i++)
                                        client.robots[i].localAdapterMacAddr = localAdapterMacAddrs[i % localAdapterMacAddrs.length];
                                }
                                enabled: (osx || android) ? false : true
                            }

                            Button{
                                text: "Connect to all, 3s delay between connects"

                                property int currentIndex: 0

                                function autoconnectTo(){
                                    if(currentIndex < client.robots.length){
                                        var robot = client.robots[currentIndex];
                                        var macAddrSelector = robotListMacAddrSelectors.items[currentIndex].selectorAtRow;
                                        robot.localAdapterMacAddr = macAddrSelector.selectedLocalAdapterAddress;
                                        robot.macAddr = macAddrSelector.selectedAddress;
                                        robot.connectToServer();
                                        currentIndex++;
                                    }
                                }

                                Timer{
                                    id: autoconnectTimer
                                    interval: 3000
                                    running: false
                                    repeat: true
                                    onTriggered: {
                                        parent.autoconnectTo();
                                        if(parent.currentIndex >= client.robots.length)
                                            stop();
                                    }
                                }

                                onClicked:{
                                    currentIndex = 0;
                                    autoconnectTo();
                                    autoconnectTimer.start();
                                }
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
                        Button{
                            text: "Disconnect from all"
                            anchors.verticalCenter: parent.verticalCenter

                            onClicked:{
                                for(var i=0;i<client.robots.length;i++)
                                    client.robots[i].disconnectFromServer();
                            }
                        }
                    }
                }
            }

            GroupBox{
                title: "Scan for robots"

                CelluloBluetoothScanner{
                    id: scanner
                    continuous: continuousCheckBox.checked
                }

                Column{
                    id: scanList

                    CheckBox{
                        id: continuousCheckBox

                        text: "Scan continuously"
                    }

                    Row{
                        spacing: 5

                        Button{
                            text: scanner.scanning ? "Scanning..." : "Scan"
                            enabled: !scanner.scanning
                            onClicked: scanner.start()
                        }

                        Button{
                            text: "Stop"
                            enabled: scanner.scanning
                            onClicked: scanner.stop()
                        }
                    }

                    Repeater{
                        model: scanner.foundRobots.length

                        Row{
                            spacing: 5

                            property string currentMacAddr: scanner.foundRobots[index]

                            Text{
                                text: currentMacAddr
                                anchors.verticalCenter: parent.verticalCenter
                                color: client.hasRobot(currentMacAddr) ? "gray" : "black"
                            }

                            Button{
                                text: "+"
                                anchors.verticalCenter: parent.verticalCenter

                                enabled: !client.hasRobot(currentMacAddr)

                                onClicked: client.addRobot(createRobot(currentMacAddr))
                            }
                        }
                    }

                    Button{
                        text: "Add all above"
                        enabled: scanner.foundRobots.length > 0
                        onClicked: {
                            for(var i=0;i<scanner.foundRobots.length;i++)
                                if(!client.hasRobot(scanner.foundRobots[i]))
                                    client.addRobot(createRobot(scanner.foundRobots[i]));
                        }
                    }
                }
            }
        }
    }

    ToastManager{ id: toast }
}
