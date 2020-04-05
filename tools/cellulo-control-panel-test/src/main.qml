import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import Cellulo 1.0
import QMLCache 1.0
import QMLBluetoothExtras 1.0

ApplicationWindow {
    id: window
    visible: true

    function em(x){ return Math.round(x*TextSingleton.font.pixelSize); }

    property bool mobile: Qt.platform.os === "android"
    property bool winrt: Qt.platform.os === "winrt"
    property real gWidth: mobile ? Screen.width : 800
    property bool activateManual: false
    width: gWidth
    height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    ToastManager{ id: toast }

    ScrollView {
        anchors.fill: parent
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: mobile ? Qt.ScrollBarAsNeeded : Qt.ScrollBarAlwaysOff

        Column{
            CelluloRobot{
                id: robotComm
                property var init: Qt.vector3d(0,0,0)
                Image{
                    id:img
                    source: 'qrc:/assets/blue.svg'
                    width: 75
                    height: 75

                    property bool isSelected: false
                    x: isSelected?img.x:robotComm.x-img.width/2
                    y: isSelected?img.y:robotComm.y-img.height/2
                    rotation: robotComm.theta

                    MouseArea {
                        id: themouse
                        anchors.fill: parent
                        drag.target: parent
                        onClicked: {
                            robotComm.init=Qt.vector3d(robotComm.x,robotComm.y,robotComm.theta)
                            parent.isSelected=!parent.isSelected
                            console.log(parent.isSelected)
                        }
                    }
                }
                simulatedCellulo: true

                initPose: img.isSelected?Qt.vector3d(img.x+img.width/2,img.y+img.height/2,img.rotation):robotComm.init

                onTouchBegan:{
                    switch(key){
                    case 0: k0.color = "yellow"; break;
                    case 1: k1.color = "yellow"; break;
                    case 2: k2.color = "yellow"; break;
                    case 3: k3.color = "yellow"; break;
                    case 4: k4.color = "yellow"; break;
                    case 5: k5.color = "yellow"; break;
                    }
                }
                onLongTouch:{
                    switch(key){
                    case 0: k0.color = "green"; break;
                    case 1: k1.color = "green"; break;
                    case 2: k2.color = "green"; break;
                    case 3: k3.color = "green"; break;
                    case 4: k4.color = "green"; break;
                    case 5: k5.color = "green"; break;
                    }
                }
                onTouchReleased:{
                    switch(key){
                    case 0: k0.color = "black"; break;
                    case 1: k1.color = "black"; break;
                    case 2: k2.color = "black"; break;
                    case 3: k3.color = "black"; break;
                    case 4: k4.color = "black"; break;
                    case 5: k5.color = "black"; break;
                    }
                }
                onFrameReady: cameraImage.reload()

                onTrackingGoalReached: toast.show("Tracking goal reached.")
                onBootCompleted: toast.show("Boot completed.")
                onShuttingDown: toast.show("Shutting down.")
                onLowBattery: toast.show("Low battery.")

                onZoneValueChanged: console.log("zone changed")


            }
            id: itemsCol
                Image{
                    source: 'qrc:/assets/redgrid.svg'
                    x:0
                    y:0
                    sourceSize.width: 500
                    sourceSize.height: 500
                }

            GroupBox {
                title: "Robot Address"
                width: gWidth

                Column{
                    spacing: 5

                    MacAddrSelector{
                        id: macAddrSelector
                        //(NOTE:) macAddrSelector.addresses is the list that is displayed in the gui. macAddrSelector.ids are the true mac Addresses to be able to connect
                        // Keeping this notation, to be compatible with older version without cellulo numbers.

                        addresses: QMLCache.read("addresses").split(",")
                        ids: QMLCache.read("ids").split(",")
                        onConnectRequested: {
                            /*robotComm.localAdapterMacAddr = selectedLocalAdapterAddress;
                            robotComm.macAddr = selectedAddress;*/
                            robotComm.localAdapterMacAddr = selectedLocalAdapterAddress;
                            robotComm.macAddr = ids[addresses.indexOf(selectedAddress)]

                        }
                        onDisconnectRequested: robotComm.disconnectFromServer()
                        connectionStatus: robotComm.connectionStatus
                    }

                    Row{
                        spacing: 5

                        BusyIndicator{
                            running: scanner.scanning
                            height: scanButton.height
                        }

                        Button{
                            id: scanButton
                            text: "Scan"
                            onClicked: scanner.start()
                        }

                        Button{
                            text: "Clear List"
                            onClicked: {
                                macAddrSelector.addresses = [];
                                QMLCache.write("addresses","");
                            }
                        }

                        Text{
                            visible: winrt
                            text: "Robots must first be paired from OS Bluetooth settings to appear in scan!"
                        }
                    }
                }
            }

            GroupBox {
                title: "Status"
                width: gWidth

                Column{
                    spacing: 5

                    Row{
                        spacing: 5

                        Text{
                            text: "Battery State: " + CelluloBluetoothEnums.BatteryStateString(robotComm.batteryState)
                        }
                        Text{
                            id: k0
                            text: "K0"
                            color: "black"
                        }
                        Text{
                            id: k1
                            text: "K1"
                            color: "black"
                        }
                        Text{
                            id: k2
                            text: "K2"
                            color: "black"
                        }
                        Text{
                            id: k3
                            text: "K3"
                            color: "black"
                        }
                        Text{
                            id: k4
                            text: "K4"
                            color: "black"
                        }
                        Text{
                            id: k5
                            text: "K5"
                            color: "black"
                        }
                    }
                    Row{
                        spacing: 5

                        Text{
                            text: "Kidnapped?"
                            color: robotComm.kidnapped ? "red" : "green"
                        }
                        Text{
                            text: "X=" + robotComm.x.toFixed(2) + "mm Y=" + robotComm.y.toFixed(2) + "mm Theta=" + robotComm.theta.toFixed(1) + "deg"+ "Vx=" + robotComm.vx.toFixed(0) + " mm/s Y=" + robotComm.vy.toFixed(0)
                        }
                    }
                }
            }

            GroupBox {
                title: "Power"
                width: gWidth

                Row{
                    spacing: 5

                    Button{
                        text: "Reset"
                        onClicked: robotComm.reset();
                    }
                    Button{
                        text: "Shutdown"
                        onClicked: robotComm.shutdown();
                    }
                    Button {
                        text: "Query Battery State"
                        onClicked: robotComm.queryBatteryState();
                    }
                }
            }


            GroupBox {
                title: "Locomotion"
                width: gWidth

                Column{
                    anchors.fill: parent

                    Row{
                        spacing: 15

                        Column{
                            Text{ text: "Goal coordinates:" }

                            TextField{ id: goalPoseX; placeholderText: "x (mm)" }
                            TextField{ id: goalPoseY; placeholderText: "y (mm)" }
                            TextField{ id: goalPoseTheta; placeholderText: "theta (degrees)"; }
                            TextField{ id: goalPoseMaxV; placeholderText: "v (mm/s)" }
                            TextField{ id: goalPoseMaxW; placeholderText: "w (rad/s)" }

                            Button{
                                text: "Track complete pose"
                                onClicked: robotComm.setGoalPose(
                                               parseFloat(goalPoseX.text),
                                               parseFloat(goalPoseY.text),
                                               parseFloat(goalPoseTheta.text),
                                               parseFloat(goalPoseMaxV.text),
                                               parseFloat(goalPoseMaxW.text)
                                               )
                            }
                            Button{
                                text: "Track position"
                                onClicked: robotComm.setGoalPosition(
                                               parseFloat(goalPoseX.text),
                                               parseFloat(goalPoseY.text),
                                               parseFloat(goalPoseMaxV.text)
                                               )
                            }
                            Button{
                                text: "Track orientation"
                                onClicked: robotComm.setGoalOrientation(
                                               parseFloat(goalPoseTheta.text),
                                               parseFloat(goalPoseMaxW.text)
                                               )
                            }
                            Button{
                                text: "Track X"
                                onClicked: robotComm.setGoalXCoordinate(
                                               parseFloat(goalPoseX.text),
                                               parseFloat(goalPoseMaxV.text)
                                               )
                            }
                            Button{
                                text: "Track Y"
                                onClicked: robotComm.setGoalYCoordinate(
                                               parseFloat(goalPoseY.text),
                                               parseFloat(goalPoseMaxV.text)
                                               )
                            }
                            Button{
                                text: "Track X and Theta"
                                onClicked: robotComm.setGoalXThetaCoordinate(
                                               parseFloat(goalPoseX.text),
                                               parseFloat(goalPoseTheta.text),
                                               parseFloat(goalPoseMaxV.text),
                                               parseFloat(goalPoseMaxW.text)
                                               )
                            }
                            Button{
                                text: "Track Y and Theta"
                                onClicked: robotComm.setGoalYThetaCoordinate(
                                               parseFloat(goalPoseY.text),
                                               parseFloat(goalPoseTheta.text),
                                               parseFloat(goalPoseMaxV.text),
                                               parseFloat(goalPoseMaxW.text)
                                               )
                            }
                        }

                        Column{
                            Label{ text: "Goal velocity:" }
                            TextField{ id: goalVelX; placeholderText: "vx (mm/s)" }
                            TextField{ id: goalVelY; placeholderText: "vy (mm/s)" }
                            TextField{ id: goalW; placeholderText: "w (rad/s)" }

                            Button{
                                text: "Set"
                                onClicked: robotComm.setGoalVelocity(parseFloat(goalVelX.text), parseFloat(goalVelY.text), parseFloat(goalW.text))
                            }
                        }

                        Button{
                            text: "Clear tracking goals"
                            onClicked: robotComm.clearTracking()
                        }
                    }
                }
            }
        }
    }

    CelluloBluetoothScanner{
        id: scanner
        property var adList: []
        property var nbList: []
        /*onRobotDiscovered: {
            var newAddresses = macAddrSelector.addresses;
            if(newAddresses.indexOf(macAddr) < 0){
                toast.show(macAddr + " discovered.");
                newAddresses.push(macAddr);
                newAddresses.sort();
            }
            macAddrSelector.addresses = newAddresses;
            QMLCache.write("addresses", macAddrSelector.addresses.join(','));
        }*/

        onRobotDiscovered: {
            var newAddresses = scanner.adList;
            var newNumbers=scanner.nbList;

            if(newAddresses.indexOf(macAddr) < 0){
                console.log(macAddr + " discovered.");
                newAddresses.push(macAddr)
                try{
                    newNumbers.push(robotNb);
                }

                catch(error){
                    console.log("Old version of CelluloBluetooth")
                    newNumbers.push(macAddr);
                }
            }
            //sorting with respect to the nbList
            var mapped = newNumbers.map(function(el, i) {
              return { index: i, value: el.toLowerCase() };
            })

            mapped.sort(function(a, b) {
                  return a.value - b.value
            });

            // container for the resulting order
            scanner.adList = mapped.map(function(el){
              return newAddresses[el.index];
            });
            scanner.nbList = mapped.map(function(el){
              return newNumbers[el.index];
            });
            //(NOTE:) macAddrSelector.addresses is the list that is displayed in the gui. macAddrSelector.ids are the true mac Addresses to be able to connect
            // Keeping this notation, to be compatible with older version without cellulo numbers.
            macAddrSelector.addresses=newNumbers
            macAddrSelector.ids=newAddresses

            QMLCache.write("addresses", newNumbers.join(','));
            QMLCache.write("ids", newAddresses.join(','));
        }


    }

    BluetoothLocalDevice{ Component.onCompleted: powerOn() } //Doesn't work on Linux


    Button{
        id: zonetest
        text: "zone Test"
        onClicked: {
            zoneEngine.addNewClient(robotComm)
            var closestT = zoneBorder.calculate(robotComm.x, robotComm.y, 0);
            var closestPoint = zoneBorder.getPoint(closestT);
            console.log(closestPoint)
        }


    }

    CelluloZoneEngine{
        id: zoneEngine
        active: true

        CelluloZonePolyBezierClosestT {
            id: zoneBorder
            name: "CelluloZone"
            controlPoints: CelluloZoneJsonHandler.loadZonesQML(":/assets/redgrid_.json")[0].controlPoints
        }

    }

}
