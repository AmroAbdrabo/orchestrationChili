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

    CelluloLocalRelayClient{
        id: client

        port: 1234

        Component.onCompleted: connectToServer()

        onConnected: console.log("Client: Connected to server.")
        onDisconnected: console.log("Client: Disconnected from server.")

        onUnknownRobotAtServer: {
            console.log("Client: Unknown robot at server: " + macAddr + ", creating...");

            var newRobot = Qt.createQmlObject("import Cellulo 1.0; CelluloBluetooth{}", window);
            newRobot.autoConnect = false;
            newRobot.macAddr = macAddr;
            var reportPose = function(x,y,theta){ console.log("Client: " + newRobot.macAddr + " pose changed: " + x + " " + y + " " + theta); };
            newRobot.onPoseChanged.connect(reportPose);

            addRobot(newRobot, true);


            var newSelector = Qt.createQmlObject("import Cellulo 1.0; MacAddrSelector{}", macAddressSelectors);
            newSelector.connectionStatus = Qt.binding(function(){ return newRobot.connectionStatus; })
            newSelector.addresses = [macAddr];
            newSelector.selectAddress(macAddr);
            newSelector.onConnectRequested.connect(
                function(){
                    newRobot.localAdapterMacAddr = newSelector.selectedLocalAdapterAddress;
                    newRobot.macAddr = newSelector.selectedAddress;
                    newRobot.connectToServer();
                }
            );
            newSelector.onDisconnectRequested.connect(
                function(){
                    newRobot.disconnectFromServer();
                }
            );
        }

    }

    Column{
        id: macAddressSelectors
    }
}
