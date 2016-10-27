import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0

import Cellulo 1.0

/**
 * @brief MAC address selection GUI
 *
 * TODO: Replace selectedAddress, connectionStatus, connectRequested() and disconnectRequested() with property CelluloBluetooth robot: null
 */
Row{

    /*
     * Public
     */

    property var addresses: []                                                      ///< List of possible MAC addresses, set by the user
    readonly property string selectedAddress: selectionBox.currentText              ///< Currently selected addresses
    property var connectionStatus: CelluloBluetooth.ConnectionStatusDisconnected    ///< Current connection status to display, set by the user

    /**
     * @brief Selects the given address if it exists in the list of addresses
     *
     * @param {string} address Address to look for in the list of addresses
     */
    function selectAddress(address){
        for(var i=0;i<addresses.length;i++)
            if(addresses[i] === address){
                selectionBox.currentIndex = i;
                return;
            }
    }

    signal connectRequested()                                                       ///< Emitted when the connect button is pressed
    signal disconnectRequested()                                                    ///< Emitted when the disconnect button is pressed

    /*
     * Private
     */

    spacing: 5

    function em(x){ return Math.round(x*TextSingleton.font.pixelSize); }

    ComboBox{
        id: selectionBox

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

    Button{
        text: "Connect"
        onClicked: {
            if(selectionBox.acceptableInput)
                connectRequested();
        }
    }

    Button{
        text: "Disconnect"
        onClicked: disconnectRequested();
    }

    Label{
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
}
