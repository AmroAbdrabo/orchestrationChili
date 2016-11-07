import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.3

import Cellulo 1.0

import "BlastType.js" as BlastType

ApplicationWindow {
    id: window
    visible: true

    property bool mobile: Qt.platform.os === "android"
    property real gWidth: mobile ? Screen.width : 640
    width: gWidth
    height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    property int blastType: BlastType.None

    Column{
        id: itemsCol

        Row{
            spacing: 10

            ExclusiveGroup{ id: actionGroup }

            RadioButton{
                text: "No Action"
                checked: true
                exclusiveGroup: actionGroup
                onCheckedChanged: {
                    if(checked)
                        blastType = BlastType.None;
                }
            }
            RadioButton{
                text: "Reset Blast"
                exclusiveGroup: actionGroup
                onCheckedChanged: {
                    if(checked)
                        blastType = BlastType.BlastReset;
                }
            }
            RadioButton{
                text: "Shutdown Blast"
                exclusiveGroup: actionGroup
                onCheckedChanged: {
                    if(checked)
                        blastType = BlastType.BlastShutdown;
                }
            }
        }

        CheckBox{
            id: continuousCheckbox
            text: "Blast continuously"
            checked: false
        }

        Row{
            spacing: 5

            GroupBox {
                title: "Robots Found:"

                ListView{
                    width: window.width/3
                    height: window.height*2/3

                    model: emp.macAddrToBlast
                    delegate: Text { text: modelData }
                }
            }

            GroupBox {
                title: "Robots Blasted:"

                ListView{
                    width: window.width/3
                    height: window.height*2/3

                    model: emp.macAddrBlasted
                    delegate: Text { text: modelData }
                }
            }
        }
    }

    onBlastTypeChanged: {
        switch(blastType){
        case BlastType.None:
            discoverer.running = false;
            emp.clear();
            break;
        case BlastType.BlastReset:
        case BlastType.BlastShutdown:
            discoverer.running = true;
            break;
        default:
            break;
        }
    }

    BluetoothLocalDevice{ Component.onCompleted: powerOn() } //Doesn't work on Linux

    CelluloBluetoothEMP{
        id: emp
        continuous: continuousCheckbox.checked
    }

    BluetoothDiscoveryModel{
        id: discoverer

        property string macAddrPrefix: "00:06:66:74"
        running: false
        discoveryMode: BluetoothDiscoveryModel.DeviceDiscovery

        onRunningChanged: {
            if(!running)
                switch(blastType){
                case BlastType.BlastReset:
                case BlastType.BlastShutdown:
                    running = true;
                    break;
                default:
                    break;
                }
        }

        onDeviceDiscovered: {
            if(device.indexOf(macAddrPrefix) === 0){
                switch(blastType){
                case BlastType.BlastReset:
                    emp.resetLater(device);
                    break;
                case BlastType.BlastShutdown:
                    emp.shutdownLater(device);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
