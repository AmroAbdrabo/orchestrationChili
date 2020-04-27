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


Item {

     function em(x){ return Math.round(x*TextSingleton.font.pixelSize); }
     property bool mobile: Qt.platform.os === "android"
     property bool winrt: Qt.platform.os === "winrt"
     property real gWidth: mobile ? Screen.width : 800
     property bool activateManual: false
    //window for robot and grid
    Window {
        objectName: "robot display window"
        id: window2
        visible: true

        width: 500
        height: mobile ? Screen.desktopAvailableHeight : 500;
        ToastManager{ id: toast }
        Image{
            id: backgroundImg
            source: 'qrc:/assets/redgrid.svg'
            x:0
            y:0
            sourceSize: Qt.size( window2.width, window2.height )
        }

        CelluloRobot{
            id: robotComm1
            property var init: Qt.vector3d(0,0,0)

            Hexagon{
                id: hex1
                property  real wheelRotation: 0
                property real curRobotRotation: 0 //to avoid binding loop on rotation
                width: 75 * window2.width/paper.width;
                height: 75 * Math.sin(60*Math.PI/180) * window2.height/paper.height;//the height of a perfect hexagon depends on its width
                transformOrigin: Item.Center
                color: "green"
                onColorChanged: console.log("color was changed");
                property bool isSelected: false
                x: isSelected?hex1.x:(robotComm1.x * window2.width / paper.width) - hex1.width/2
                y: isSelected?hex1.y:(robotComm1.y * window2.height / paper.height) - hex1.height/2
                rotation: isSelected? curRobotRotation + wheelRotation : robotComm1.theta ;

                MouseArea {
                    id: themouse1
                    anchors.fill: parent
                    drag.target: parent
                    onClicked: {
                        //reset curRobotRotation and wheelRotation
                        parent.curRobotRotation = robotComm1.theta
                        parent.wheelRotation = 0

                        robotComm1.init=Qt.vector3d(robotComm1.x,robotComm1.y,robotComm1.theta)
                        parent.isSelected=!parent.isSelected
                        console.log(parent.isSelected)
                    }
                    onWheel: {
                        if(parent.isSelected){
                            parent.wheelRotation += wheel.angleDelta.y/16;
                            parent.wheelRotation = parent.wheelRotation > 360 ?
                                        parent.wheelRotation-360: parent.wheelRotation
                        }
                    }
                }

            }
            isSimulation: true

            initPose: hex1.isSelected?Qt.vector3d((hex1.x+hex1.width/2)* paper.width/window2.width,
                                                   (hex1.y+hex1.height/2) * paper.height/window2.height,
                                                    hex1.rotation) : robotComm1.init

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
        CelluloRobot{
            id: robotComm2
            property var init: Qt.vector3d(0,0,0)
            Hexagon{
                id: hex2
                property  real wheelRotation: 0
                property real curRobotRotation: 0 //to avoid binding loop on rotation
                width: 75 * window2.width/paper.width;
                height: 75 * Math.sin(60*Math.PI/180) * window2.height/paper.height;
                transformOrigin: Item.Center
                color: "red"
                onColorChanged: console.log("color was changed");
                property bool isSelected: false
                x: isSelected?hex2.x:(robotComm2.x * window2.width / paper.width) - hex2.width/2
                y: isSelected?hex2.y:(robotComm2.y * window2.height / paper.height) - hex2.height/2
                rotation: isSelected? curRobotRotation + wheelRotation : robotComm2.theta ;

                MouseArea {
                    id: themouse2
                    anchors.fill: parent
                    drag.target: parent
                    onClicked: {
                        //reset curRobotRotation and wheelRotation
                        parent.curRobotRotation = robotComm1.theta
                        parent.wheelRotation = 0

                        robotComm2.init=Qt.vector3d(robotComm2.x,robotComm2.y,robotComm2.theta)
                        parent.isSelected=!parent.isSelected
                        console.log(parent.isSelected)
                    }
                    onWheel: {
                        if(parent.isSelected){
                            parent.wheelRotation += wheel.angleDelta.y/16;
                            parent.wheelRotation = parent.wheelRotation > 360 ?
                                        parent.wheelRotation-360: parent.wheelRotation
                        }
                    }
                }
            }
            isSimulation: true

            initPose: hex2.isSelected?Qt.vector3d((hex2.x+hex2.width/2)* paper.width/window2.width,
                                                   (hex2.y+hex2.height/2) * paper.height/window2.height,
                                                    hex2.rotation) : robotComm2.init
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
    }

    Window {
        objectName: "controls window"
        id: window1
        visible: true

        /*Button {
                anchors.centerIn: parent
                text: qsTr("Click me")

                onClicked: {
                    var component = Qt.createComponent("RobotDisplay.qml")
                    var window2    = component.createObject(window)
                    window2.show()
                }
            }*/

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
                                color: robotComm1.kidnapped ? "red" : "green"
                            }
                            Text{
                                text: "X=" + robotComm1.x.toFixed(2) + "mm Y=" + robotComm1.y.toFixed(2) + "mm Theta=" + robotComm1.theta.toFixed(1) + "deg"+ "Vx=" + robotComm1.vx.toFixed(0) + " mm/s Y=" + robotComm1.vy.toFixed(0)
                            }
                        }
                        Row{
                            spacing: 5

                            Text{
                                text: "Kidnapped?"
                                color: robotComm2.kidnapped ? "red" : "green"
                            }
                            Text{
                                text: "X=" + robotComm2.x.toFixed(2) + "mm Y=" + robotComm2.y.toFixed(2) + "mm Theta=" + robotComm2.theta.toFixed(1) + "deg"+ "Vx=" + robotComm2.vx.toFixed(0) + " mm/s Y=" + robotComm2.vy.toFixed(0)
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
                                //update backgroundsize and windowsize
                                paper.height = 420;
                                paper.width = 980;
                                //be default resize window with paper dimensions
                                //but can give the window any size you want
                                window2.width = paper.width;
                                window2.height = paper.height;
                                backgroundImg.source = 'qrc:/assets/orangemapcorrected.svg'
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
                                    onClicked: robotComm1.setGoalXThetaCoordinate(
                                                   parseFloat(goalPoseX.text),
                                                   parseFloat(goalPoseTheta.text),
                                                   parseFloat(goalPoseMaxV.text),
                                                   parseFloat(goalPoseMaxW.text)
                                                   )
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
                            }

                            Button{
                                text: "Clear tracking goals"
                                onClicked: robotComm1.clearTracking()
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
                zoneEngine.addNewClient(robotComm1)
                var closestT = zoneBorder.calculate(robotComm1.x, robotComm1.y, 0);
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
}
