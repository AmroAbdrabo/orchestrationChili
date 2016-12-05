import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.2

import QMLCache 1.0
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: 100
    minimumWidth: 200

    readonly property int numRobots: 15
    property var robots: []

    Repeater{
        model: numRobots

        CelluloBluetooth{
            id: robot

            macAddr: QMLCache.read("robot" + index + "MacAddr")
            localAdapterMacAddr: QMLCache.read("robot" + index + "LocalAdapterMacAddr")

            onConnectionStatusChanged: {
                if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected){
                    robot.setPoseBcastPeriod(100);
                    robot.setCasualBackdriveAssistEnabled(true);
                    robot.clearHapticFeedback();
                    robot.clearTracking();
                }
            }

            onPoseChanged: {
                robot.setGoalVelocity(0,0,0);
            }
        }

        onItemAdded: {
            var temp = robots;
            temp.push(item);
            robots = temp;
        }
    }

    //Visible items

    GroupBox {
        id: addressBox
        title: "Robots"

        Column{
            property variant addresses: [
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

            Repeater{
                model: numRobots

                MacAddrSelector{
                    addresses: parent.addresses
                    onConnectRequested: {
                        robots[index].localAdapterMacAddr = selectedLocalAdapterAddress;
                        robots[index].macAddr = selectedAddress;
                        QMLCache.write("robot" + index + "LocalAdapterMacAddr", selectedLocalAdapterAddress);
                        QMLCache.write("robot" + index + "MacAddr", selectedAddress);
                    }
                    onDisconnectRequested: {
                        robots[index].disconnectFromServer();
                        QMLCache.write("robot" + index + "MacAddr", "");
                    }
                    connectionStatus: robots[index].connectionStatus

                    Component.onCompleted: {
                        selectAddress(QMLCache.read("robot" + index + "MacAddr"));
                        selectLocalAdapterAddress(QMLCache.read("robot" + index + "LocalAdapterMacAddr"));
                    }
                }
            }
        }
    }

    GroupBox{
        id: playgroundBox
        title: "Playground"
        anchors.top: addressBox.bottom

        Item{
            width: page.width + page.physicalRobotWidth*page.scaleCoeff
            height: page.height + page.physicalRobotWidth*page.scaleCoeff

            Rectangle{
                id: page

                anchors.centerIn: parent

                property real physicalWidth: 841        ///< Physical paper width in mm
                property real physicalHeight: 841       ///< Physical paper height in mm
                property real physicalRobotWidth: 75    ///< Physical robot width in mm

                width: height*physicalWidth/physicalHeight
                height: Screen.height/3

                property real scaleCoeff: width/physicalWidth

                color: "#EEEEEE"
                border.color: "black"
                border.width: 2
                radius: 5

                Repeater{
                    model: numRobots

                    Image{
                        visible: robots[index].connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected
                        source: robots[index].kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
                        rotation: robots[index].theta
                        x: robots[index].x*parent.scaleCoeff - width/2
                        y: robots[index].y*parent.scaleCoeff - height/2
                        width: parent.physicalRobotWidth*parent.scaleCoeff
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
