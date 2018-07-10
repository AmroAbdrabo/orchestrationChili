import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0

import QMLBluetoothExtras 1.0
import Cellulo 1.0

/**
 * @addtogroup util
 * @{
 */

/**
 * @brief MAC address selection GUI
 *
 * TODO: Replace selectedAddress, connectionStatus, connectRequested() and disconnectRequested() with property CelluloBluetooth robot: null
 */
Row{

    /*
     * Public
     */

    /** type:list<string> List of possible MAC addresses, set by the user */
    property var addresses: []

    /** type:string Currently selected address. */
    readonly property string selectedAddress: selectionBox.currentText

    /** type:string Currently selected local adapter address (only available in Linux). */
    readonly property string selectedLocalAdapterAddress: localAdapterSelectionBox.currentText

    /** type:enum Current connection status to display, set by the user, one of CelluloBluetoothEnums.ConnectionStatus */
    property var connectionStatus: CelluloBluetoothEnums.ConnectionStatusDisconnected

    /**
     * @brief Selects the given address if it exists in the list of addresses
     *
     * @param type:string address Address to look for in the list of addresses
     */
    function selectAddress(address){
        for(var i=0;i<addresses.length;i++)
            if(addresses[i] === address){
                selectionBox.currentIndex = i;
                return;
            }
    }

    /**
     * @brief Selects the given local adapter address if it exists in the list of addresses
     *
     * @param type:string address Address to look for in the list of addresses
     */
    function selectLocalAdapterAddress(address){
        for(var i=0;i<localAdapterAddresses.length;i++)
            if(localAdapterAddresses[i] === address){
                localAdapterSelectionBox.currentIndex = i;
                return;
            }
    }

    /** @brief Emitted when the connect button is pressed */
    signal connectRequested()

    /** @brief Emitted when the disconnect button is pressed */
    signal disconnectRequested()

    /*
     * Private
     */

    /** @cond DO_NOT_DOCUMENT */

    spacing: 5

    property bool linux: Qt.platform.os === "linux"
    property var localAdapterAddresses: {
        var arr = [""];
        if(linux){
            var devices = BluetoothLocalDeviceStatic.allDevices();
            for(var i=0;i<devices.length;i++)
                arr.push(devices[i]);
        }
        return arr;
    }

    function em(x){ return Math.round(x*TextSingleton.font.pixelSize); }

    ComboBox{
        id: selectionBox

        anchors.verticalCenter: parent.verticalCenter

        editable: true
        width: em(12)
        model: addresses

        onAccepted: {
            if (currentIndex == -1) {
                var tempModel = [];
                for(var i=0;i<model.length;i++)
                    tempModel.push(model[i]);
                tempModel.push(editText);
                model = tempModel;
                currentIndex = count - 1;
            }
        }
    }

    Text{
        anchors.verticalCenter: parent.verticalCenter
        text: "through"
        visible: linux
    }

    ComboBox{
        id: localAdapterSelectionBox

        anchors.verticalCenter: parent.verticalCenter

        visible: linux
        enabled: linux

        editable: true
        width: em(12)
        model: localAdapterAddresses

        onAccepted: {
            if (currentIndex == -1) {
                var tempModel = [];
                for(var i=0;i<model.length;i++)
                    tempModel.push(model[i]);
                tempModel.push(editText);
                model = tempModel;
                currentIndex = count - 1;
            }
        }
    }

    Button{
        anchors.verticalCenter: parent.verticalCenter
        text: "Connect"
        onClicked: {
            if(selectionBox.acceptableInput)
                connectRequested();
        }
    }

    Button{
        anchors.verticalCenter: parent.verticalCenter
        text: "Disconnect"
        onClicked: disconnectRequested();
    }

    Text{
        anchors.verticalCenter: parent.verticalCenter
        text: CelluloBluetoothEnums.ConnectionStatusString(connectionStatus)
        color: {
            switch(connectionStatus){
            case CelluloBluetoothEnums.ConnectionStatusDisconnected:
                return "red";
            case CelluloBluetoothEnums.ConnectionStatusConnecting:
                return "yellow";
            case CelluloBluetoothEnums.ConnectionStatusConnected:
                return "green";
            }
        }
    }

    /** @endcond */
}

/** @} */
