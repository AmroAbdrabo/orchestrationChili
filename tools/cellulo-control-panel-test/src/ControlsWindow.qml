import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import Cellulo 1.0
import QMLCache 1.0
import QMLBluetoothExtras 1.0
import hexagon.qml 1.0

import "Utils.js" as MyFuncs
//window to display the control panel
Window {
    objectName: "controls window"
    id: window1
    visible: true
    width: gWidth
    height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    ScrollView {
        anchors.fill: parent
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: mobile ? Qt.ScrollBarAsNeeded : Qt.ScrollBarAlwaysOff

        Column{

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
                            robotComm1.localAdapterMacAddr = selectedLocalAdapterAddress;
                            robotComm1.macAddr = ids[addresses.indexOf(selectedAddress)]

                        }
                        onDisconnectRequested: robotComm1.disconnectFromServer()
                        connectionStatus: robotComm1.connectionStatus
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
                            text: "Battery State: " + CelluloBluetoothEnums.BatteryStateString(robotComm1.batteryState)
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
                            color: !robotComm1.isSelected? "red" : "green"
                        }
                        Text{
                            text: "X=" + robotComm1.x.toFixed(2) + "mm Y=" + robotComm1.y.toFixed(2) + "mm Theta=" + robotComm1.theta.toFixed(1) + "deg"+ "Vx=" + robotComm1.vx.toFixed(2) + " mm/s Vy=" + robotComm1.vy.toFixed(2)
                        }
                    }
                    Row{
                        spacing: 5

                        Text{
                            text: "Kidnapped?"
                            color: robotComm2.isSelected ? "red" : "green"
                        }
                        Text{
                            text: "X=" + robotComm2.x.toFixed(2) + "mm Y=" + robotComm2.y.toFixed(2) + "mm Theta=" + robotComm2.theta.toFixed(1) + "deg"+ "Vx=" + robotComm2.vx.toFixed(2) + " mm/s Y=" + robotComm2.vy.toFixed(2)
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
                        onClicked: robotComm1.reset();
                    }
                    Button{
                        text: "Shutdown"
                        onClicked: robotComm1.shutdown();
                    }
                    Button {
                        text: "Query Battery State"
                        onClicked: robotComm1.queryBatteryState();
                    }
                }
            }

            GroupBox {
                title: "Paper size"
                width: gWidth

                Row{
                    spacing: 5

                    Button{
                        text: "Default"
                        onClicked: {
                            //backgroud.sourceSize = Qt.size(500, 500)
                            paper.height = 500
                            paper.width = 500
                            //be default resize window with paper dimensions
                            //but can give the window any size you want
                            window2.width = paper.width
                            window2.height = paper.height
                            backgroundImg.source = 'qrc:/assets/redgrid.svg'
                        }
                    }
                    Button{
                        text: "orangemap"
                        onClicked: {
                            //update backgroundsize and windowsize to desired map dimensions in mm
                            paper.height = 420;
                            paper.width = 980;

                            //be default resize window with paper dimensions
                            //but can give the window any size you want
                            window2.width = paper.width;
                            window2.height = paper.height;
                            //load background image
                            backgroundImg.source = 'qrc:/assets/orangemapcorrected.svg'

                            //create zones and add robots to the zoneEngine
                            MyFuncs.createZones();
                            zoneEngine.addNewClient(robotComm1)
                            zoneEngine.addNewClient(robotComm2)
                        }
                    }
                    Button{
                        text: "A4"
                        onClicked: {
                            paper.height = 210
                            paper.width = 297
                            //be default resize window with paper dimensions
                            //but can give the window any size you want
                            window2.width = paper.width
                            window2.height = paper.height
                        }
                    }
                    Button {
                        text: "A3"
                        onClicked: {
                            paper.height = 297
                            paper.width = 420
                            //be default resize window with paper dimensions
                            //but can give the window any size you want
                            window2.width = paper.width
                            window2.height = paper.height
                        }
                    }
                    Button {
                        text: "A2"
                        onClicked: {
                            paper.height = 420
                            paper.width = 594
                            //be default resize window with paper dimensions
                            //but can give the window any size you want
                            window2.width = paper.width
                            window2.height = paper.height
                        }
                    }
                }
            }


            GroupBox {
                title: "Color Effects Robot1"
                width: gWidth

                RowLayout{
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 5

                    Column{
                        ComboBox {
                            id: effect
                            model: CelluloBluetoothEnums.VisualEffectStrings
                            currentIndex: 0
                        }
                        ComboBox {
                            model: CelluloBluetoothEnums.LEDResponseModeStrings
                            currentIndex: 0
                            onCurrentIndexChanged: {
                                if(robotComm1 != null)
                                    robotComm1.setLEDResponseMode(currentIndex)
                            }
                        }
                    }
                    Column{
                        Layout.fillWidth: true
                        Slider{
                            property string hexStr: (value < 16 ? "0" : "") + value.toString(16).toUpperCase()

                            id: redSlider
                            anchors.left: parent.left
                            anchors.right: parent.right
                            minimumValue: 0
                            maximumValue: 255
                            stepSize: 1
                            value: 128
                            style: SliderStyle {
                                groove: Rectangle {
                                    implicitHeight: 8
                                    color: "red"
                                }
                            }
                        }
                        Slider{
                            property string hexStr: (value < 16 ? "0" : "") + value.toString(16).toUpperCase()

                            id: greenSlider
                            anchors.left: parent.left
                            anchors.right: parent.right
                            minimumValue: 0
                            maximumValue: 255
                            stepSize: 1
                            value: 128
                            style: SliderStyle {
                                groove: Rectangle {
                                    implicitHeight: 8
                                    color: "green"
                                }
                            }
                        }
                        Slider{
                            property string hexStr: (value < 16 ? "0" : "") + value.toString(16).toUpperCase()

                            id: blueSlider
                            anchors.left: parent.left
                            anchors.right: parent.right
                            minimumValue: 0
                            maximumValue: 255
                            stepSize: 1
                            value: 128
                            style: SliderStyle {
                                groove: Rectangle {
                                    implicitHeight: 8
                                    color: "blue"
                                }
                            }
                        }
                    }
                    Label{
                        text: "Value:"
                       // anchors.verticalCenter: effectValue.verticalCenter
                    }
                    SpinBox {
                        id: effectValue
                        minimumValue: 0
                        maximumValue: 255
                        value: 0
                        width: em(3)
                    }
                    Column{
                        spacing: 5
                        Button {
                            text: "Send"
                            onClicked: robotComm1.setVisualEffect(effect.currentIndex, "#FF" + redSlider.hexStr + greenSlider.hexStr + blueSlider.hexStr, effectValue.value);
                        }
                        Button{
                            text: "Set Hex"
                            onClicked: robotComm1.setHexagonColor("#FF" + redSlider.hexStr + greenSlider.hexStr + blueSlider.hexStr)
                        }
                    }

                }

            }

            GroupBox {
                title: "Color Effects Robot2"
                width: gWidth

                RowLayout{
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 5

                    Column{
                        ComboBox {
                            id: effect2
                            model: CelluloBluetoothEnums.VisualEffectStrings
                            currentIndex: 0
                        }
                        ComboBox {
                            model: CelluloBluetoothEnums.LEDResponseModeStrings
                            currentIndex: 0
                            onCurrentIndexChanged: {
                                if(robotComm1 != null)
                                    robotComm1.setLEDResponseMode(currentIndex)
                            }
                        }
                    }
                    Column{
                        Layout.fillWidth: true
                        Slider{
                            property string hexStr: (value < 16 ? "0" : "") + value.toString(16).toUpperCase()

                            id: redSlider2
                            anchors.left: parent.left
                            anchors.right: parent.right
                            minimumValue: 0
                            maximumValue: 255
                            stepSize: 1
                            value: 128
                            style: SliderStyle {
                                groove: Rectangle {
                                    implicitHeight: 8
                                    color: "red"
                                }
                            }
                        }
                        Slider{
                            property string hexStr: (value < 16 ? "0" : "") + value.toString(16).toUpperCase()

                            id: greenSlider2
                            anchors.left: parent.left
                            anchors.right: parent.right
                            minimumValue: 0
                            maximumValue: 255
                            stepSize: 1
                            value: 128
                            style: SliderStyle {
                                groove: Rectangle {
                                    implicitHeight: 8
                                    color: "green"
                                }
                            }
                        }
                        Slider{
                            property string hexStr: (value < 16 ? "0" : "") + value.toString(16).toUpperCase()

                            id: blueSlider2
                            anchors.left: parent.left
                            anchors.right: parent.right
                            minimumValue: 0
                            maximumValue: 255
                            stepSize: 1
                            value: 128
                            style: SliderStyle {
                                groove: Rectangle {
                                    implicitHeight: 8
                                    color: "blue"
                                }
                            }
                        }
                    }
                    Label{
                        text: "Value:"
                       // anchors.verticalCenter: effectValue.verticalCenter
                    }
                    SpinBox {
                        id: effectValue2
                        minimumValue: 0
                        maximumValue: 255
                        value: 0
                        width: em(3)
                    }
                    Column{
                        spacing: 5
                        Button {
                            text: "Send"
                            onClicked: robotComm2.setVisualEffect(effect2.currentIndex, "#FF" + redSlider2.hexStr + greenSlider2.hexStr + blueSlider2.hexStr, effectValue2.value);
                        }
                        Button{
                            text: "Set Hex"
                            onClicked: robotComm2.setHexagonColor("#FF" + redSlider.hexStr + greenSlider.hexStr + blueSlider.hexStr)
                        }
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
                                onClicked: robotComm1.setGoalPose(
                                               parseFloat(goalPoseX.text),
                                               parseFloat(goalPoseY.text),
                                               parseFloat(goalPoseTheta.text),
                                               parseFloat(goalPoseMaxV.text),
                                               parseFloat(goalPoseMaxW.text)
                                               )
                            }
                            Button{
                                text: "Track position"
                                onClicked: robotComm1.setGoalPosition(
                                               parseFloat(goalPoseX.text),
                                               parseFloat(goalPoseY.text),
                                               parseFloat(goalPoseMaxV.text)
                                               )
                            }
                            Button{
                                text: "Track orientation"
                                onClicked: robotComm1.setGoalOrientation(
                                               parseFloat((goalPoseTheta.text)),
                                               parseFloat(goalPoseMaxW.text)
                                               )
                            }
                            Button{
                                text: "Track X"
                                onClicked: robotComm1.setGoalXCoordinate(
                                               parseFloat(goalPoseX.text),
                                               parseFloat(goalPoseMaxV.text)
                                               )
                            }
                            Button{
                                text: "Track Y"
                                onClicked: robotComm1.setGoalYCoordinate(
                                               parseFloat(goalPoseY.text),
                                               parseFloat(goalPoseMaxV.text)
                                               )
                            }
                            Button{
                                text: "Track X and Theta"
                                onClicked: {robotComm1.setGoalXThetaCoordinate(
                                               parseFloat(goalPoseX.text),
                                               parseFloat(goalPoseTheta.text),
                                               parseFloat(goalPoseMaxV.text),
                                               parseFloat(goalPoseMaxW.text)
                                               )
                                            robotComm1.goalVelX = parseFloat(goalPoseMaxV.text);
                                }
                            }
                            Button{
                                text: "Track Y and Theta"
                                onClicked: robotComm1.setGoalYThetaCoordinate(
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
                                onClicked: robotComm1.setGoalVelocity(parseFloat(goalVelX.text), parseFloat(goalVelY.text), parseFloat(goalW.text))
                            }
                            Button{
                                text: "Clear tracking goals"
                                onClicked: robotComm1.clearTracking()
                            }
                        }

                        Column{
                            Text{ text: "Goal coordinates:" }

                            TextField{ id: goalPoseX2; placeholderText: "x (mm)" }
                            TextField{ id: goalPoseY2; placeholderText: "y (mm)" }
                            TextField{ id: goalPoseTheta2; placeholderText: "theta (degrees)"; }
                            TextField{ id: goalPoseMaxV2; placeholderText: "v (mm/s)" }
                            TextField{ id: goalPoseMaxW2; placeholderText: "w (rad/s)" }

                            Button{
                                text: "Track complete pose"
                                onClicked: robotComm2.setGoalPose(
                                               parseFloat(goalPoseX2.text),
                                               parseFloat(goalPoseY2.text),
                                               parseFloat(goalPoseTheta2.text),
                                               parseFloat(goalPoseMaxV2.text),
                                               parseFloat(goalPoseMaxW2.text)
                                               )
                            }
                            Button{
                                text: "Track position"
                                onClicked: robotComm2.setGoalPosition(
                                               parseFloat(goalPoseX2.text),
                                               parseFloat(goalPoseY2.text),
                                               parseFloat(goalPoseMaxV2.text)
                                               )
                            }
                            Button{
                                text: "Track orientation"
                                onClicked: robotComm2.setGoalOrientation(
                                               parseFloat(goalPoseTheta2.text),
                                               parseFloat(goalPoseMaxW2.text)
                                               )
                            }
                            Button{
                                text: "Track X"
                                onClicked: robotComm2.setGoalXCoordinate(
                                               parseFloat(goalPoseX2.text),
                                               parseFloat(goalPoseMaxV2.text)
                                               )
                            }
                            Button{
                                text: "Track Y"
                                onClicked: robotComm2.setGoalYCoordinate(
                                               parseFloat(goalPoseY2.text),
                                               parseFloat(goalPoseMaxV2.text)
                                               )
                            }
                            Button{
                                text: "Track X and Theta"
                                onClicked: robotComm2.setGoalXThetaCoordinate(
                                               parseFloat(goalPoseX2.text),
                                               parseFloat(goalPoseTheta2.text),
                                               parseFloat(goalPoseMaxV2.text),
                                               parseFloat(goalPoseMaxW2.text)
                                               )
                            }
                            Button{
                                text: "Track Y and Theta"
                                onClicked: robotComm2.setGoalYThetaCoordinate(
                                               parseFloat(goalPose2.text),
                                               parseFloat(goalPoseTheta2.text),
                                               parseFloat(goalPoseMaxV2.text),
                                               parseFloat(goalPoseMaxW2.text)
                                               )
                            }
                        }
                        Column{
                            Label{ text: "Goal velocity:" }
                            TextField{ id: goalVelX2; placeholderText: "vx (mm/s)" }
                            TextField{ id: goalVelY2; placeholderText: "vy (mm/s)" }
                            TextField{ id: goalW2; placeholderText: "w (rad/s)" }

                            Button{
                                text: "Set"
                                onClicked: robotComm2.setGoalVelocity(parseFloat(goalVelX2.text), parseFloat(goalVelY2.text), parseFloat(goalW2.text))
                            }
                            Button{
                                text: "Clear tracking goals"
                                onClicked: robotComm2.clearTracking()
                            }
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


    /*Button{
        id: zonetest
        text: "zone Test"
        onClicked: {
            MyFuncs.createZones();
            zoneEngine.addNewClient(robotComm1)
            zoneEngine.addNewClient(robotComm2)
            //var closestT = zoneBorder.calculate(robotComm1.x, robotComm1.y, 0);
            //var closestPoint = zoneBorder.getPoint(closestT);
            //console.log(closestPoint)
        }
    }*/

    /*CelluloZoneEngine{
        id: zoneEngine
        active: true

        CelluloZonePolyBezierClosestT {
            id: zoneBorder
            name: "CelluloZone"
            controlPoints: CelluloZoneJsonHandler.loadZonesQML(":/assets/redgrid_.json")[0].controlPoints
        }

    }*/
}

