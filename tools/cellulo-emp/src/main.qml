import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.3
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    property bool mobile: Qt.platform.os === "android"
    property real gWidth: mobile ? Screen.width : 640
    width: gWidth
    height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    ToastManager{ id: toast }

    ScrollView{
        anchors.fill: parent
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: mobile ? Qt.ScrollBarAsNeeded : Qt.ScrollBarAlwaysOff

        Column{
            id: itemsCol

            Row{
                spacing: 10

                ExclusiveGroup{ id: actionGroup }

                RadioButton{
                    text: "No Action"
                    checked: true
                    exclusiveGroup: actionGroup
                }
                RadioButton{
                    text: "Reset Blast"
                    exclusiveGroup: actionGroup
                }
                RadioButton{
                    text: "Shutdown Blast"
                    exclusiveGroup: actionGroup
                }
            }

            Row{
                spacing: 5

                GroupBox {
                    title: "Robots Found:"

                    ListView{
                        width: window.width/3
                        height: window.height*2/3

                        model: foundModel
                        delegate: Text { text: macAddr }
                    }
                }

                GroupBox {
                    title: "Robots Blasted:"

                    ListView{
                        width: window.width/3
                        height: window.height*2/3

                        model: doneModel
                        delegate: Text { text: macAddr }
                    }
                }
            }
        }
    }

    ListModel{
        id: foundModel

        function removeMacAddr(macAddrToRemove){
            for(var i=0;i<count;i++)
                if(get(i).macAddr === macAddrToRemove){
                    remove(i);
                    break;
                }
        }
    }
    ListModel{
        id: doneModel

        function removeMacAddr(macAddrToRemove){
            for(var i=0;i<count;i++)
                if(get(i).macAddr === macAddrToRemove){
                    remove(i);
                    break;
                }
        }
    }

    BluetoothDiscoveryModel{
        id: discoverer

        property string macAddrPrefix: "00:06:66:74"

        running: false
        discoveryMode: BluetoothDiscoveryModel.DeviceDiscovery

        onDeviceDiscovered: {
            if(device.indexOf(macAddrPrefix) === 0){
                foundModel.append({macAddr: device});
                console.log("New device: " + device)
            }
        }
    }

    property var celluloBluetoothComponent: null
    property var celluloBluetooths: []

    Component.onCompleted: {
        celluloBluetoothComponent = Qt.createComponent("CelluloBluetooth.qml");
        discoverer.running = true;
    }

    CelluloBluetooth{
        id: robotComm


        onBootCompleted: toast.show("Boot completed.")
        onShuttingDown: toast.show("Shutting down.")

    }
}
