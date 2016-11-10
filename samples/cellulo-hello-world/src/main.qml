import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtBluetooth 5.2
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: height
    minimumWidth: width

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
        onConnectRequested: robotComm.macAddr = selectedAddress
        onDisconnectRequested: robotComm.disconnectFromServer()
        connectionStatus: robotComm.connectionStatus
    }

    CelluloBluetooth{
        id: robotComm

        onConnectionStatusChanged: {

            //Say hello by setting all LEDs to green
            if(connectionStatus == CelluloBluetoothEnums.ConnectionStatusConnected)
                setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "green", 0);
        }
    }
}
