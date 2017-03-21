import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import QMLBluetoothExtras 1.0
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    property bool mobile: Qt.platform.os === "android"
    minimumWidth: width
    minimumHeight: height
    //height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    Component.onCompleted: {
        if(CelluloCommUtil.testRobotPoolDaemon()){
            if(CelluloCommUtil.startRobotPoolDaemon())
                toast.show("Robot pool daemon started, connecting...");
            else
                toast.show("Robot pool daemon already running, connecting...");
            client.connectToServer();
        }
        else{
            var err = "/usr/local/bin/cellulorobotpoold not found!!!";
            toast.show(err);
            console.log(err);
        }
    }

    function createRobot(macAddr){
        var newRobot = Qt.createQmlObject("import Cellulo 1.0; CelluloBluetooth{}", window);
        newRobot.autoConnect = false;
        newRobot.macAddr = macAddr;
        return newRobot;
    }

    CelluloLocalRelayClient{
        id: client

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

    Row{
        spacing: 5

        Column{
            spacing: 5

            GroupBox{
                title: "Server controls"

                Row{
                    spacing: 5

                    Button{
                        text: "Start Server"
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            if(CelluloCommUtil.startRobotPoolDaemon())
                                toast.show("Started robot pool daemon.");
                            else
                                toast.show("Cannot start robot pool daemon, possibly already running.");
                        }
                    }
                    Button{
                        text: "Stop Server"
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            if(CelluloCommUtil.stopRobotPoolDaemon())
                                toast.show("Stopped robot pool daemon.");
                            else
                                toast.show("Cannot stop robot pool daemon, possibly not running.");
                        }
                    }
                    Text{
                        text: client.connected ? "Connected to Server." : "Connecting to Server..."
                        color: client.connected ? "green" : "red"
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

                    Repeater{
                        model: client.robots.length

                        MacAddrSelector{
                            property var robot: client.robots[index]
                            property string localAdapterMacAddr: robot.localAdapterMacAddr

                            addresses: [robot.macAddr]
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

                    Button{
                        text: "Equally distribute local adapters"
                        onClicked:{
                            var localAdapters = BluetoothLocalDeviceStatic.allDevices();
                            for(var i=0;i<client.robots.length;i++){
                                console.log(localAdapters[Math.floor(localAdapters.length*i/client.robots.length)]);
                                client.robots[i].localAdapterMacAddr = localAdapters[Math.floor(localAdapters.length*i/client.robots.length)];
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

    ToastManager{ id: toast }
}
