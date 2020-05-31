import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.3
import Cellulo 1.0
import QMLCache 1.0
import QMLBluetoothExtras 1.0
import hexagon.qml 1.0
import Qt.labs.folderlistmodel 2.1
import QtWebSockets 1.0
import FileIO.qml 1.0
//import ch.epfl.chili.orchestration 1.0
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
                            onClicked: { scanner.start() }
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
                            text: "X=" + robotComm1.x.toFixed(2) + "mm Y=" + robotComm1.y.toFixed(2) + "mm Theta=" + robotComm1.theta.toFixed(1) + "deg"+ "Vx=" + robotComm1.vx.toFixed(2) + " mm/s Vy=" + robotComm1.vy.toFixed(2)
                        }
                    }
                    Row{
                        spacing: 5

                        Text{
                            text: "Kidnapped?"
                            color: robotComm2.kidnapped? "red" : "green"
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
                title: "Map selection"
                width: gWidth
                Column{
                    spacing: 5
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
                        ComboBox {
                            width: 150
                            id: mapSelector
                            currentIndex: -1
                            FolderListModel{
                                id: folderModel1
                                folder: 'qrc:/svgs/'
                            }

                            model:folderModel1
                            textRole: 'fileName'

                        }
                        ComboBox {
                            id: csvSelector
                            currentIndex: -1
                            width: 150
                            FolderListModel{
                                id: folderModel2
                                folder: 'qrc:/csvs/'
                            }
                            model:folderModel2
                            textRole: 'fileName'
                        }
                        TextField{ id: mapDimX; placeholderText: "Map width (mm)"; width: 100 }
                        TextField{ id: mapDimY; placeholderText: "Map height (mm)"; width: 100}
                        Button{
                            text: "Set"
                            onClicked: {
                                //setup map with given dimensions
                                paper.height = parseFloat(mapDimY.text);
                                paper.width = parseFloat(mapDimX.text);
                                window2.width = paper.width;//be default resize window with paper dimensions
                                window2.height = paper.height; //but can give the window any size you want

                                //load background image
                                backgroundImg.source = "qrc:/assets/"+ mapSelector.textAt(mapSelector.currentIndex);

                                //begging simulation with csv file if a file other then "NONE" is selected
                                if(csvSelector.textAt(csvSelector.currentIndex) !== "NONE") {
                                    myFile.parseData(); //parse csv file so that it can be read
                                    myFile.nextLine(); //skip the first line
                                    /*robotComm1.setPose( parseFloat(myFile.getcurLineVal(FileIO.POSEX)), parseFloat(myFile.getcurLineVal(FileIO.POSEY)),
                                                           parseFloat(myFile.getcurLineVal(FileIO.POSETHETA)), goalVel,
                                                           parseFloat(myFile.getcurLineVal(FileIO.ANGULARVEL)));*/
                                    robotComm1.setPose( parseFloat(myFile.getcurLineVal(FileIO.POSEX)), parseFloat(myFile.getcurLineVal(FileIO.POSEY)),
                                                           parseFloat(myFile.getcurLineVal(FileIO.POSETHETA)), parseFloat(myFile.getcurLineVal(FileIO.VELOCITYX)) ,
                                                           parseFloat(myFile.getcurLineVal(FileIO.VELOCITYY)), parseFloat(myFile.getcurLineVal(FileIO.ANGULARVEL)));
                                    //console.log(myFile.getcurLineVal(FileIO.TIMESTAMP));
                                    var date2 = Date.fromLocaleString(locale, myFile.getcurLineVal(FileIO.TIMESTAMP), "yyyy-MM-dd hh:mm:ss.zzz")
                                    var date1 = Date.fromLocaleString(locale, myFile.getValAtLine(FileIO.TIMESTAMP, myFile.getCurrLine()+1), "yyyy-MM-dd hh:mm:ss.zzz")
                                    var deltaT = (date1.getSeconds() - date2.getSeconds())*100 + date1.getMilliseconds()-date2.getMilliseconds();
                                    console.log(deltaT);
                                    timer.interval = deltaT;
                                    timer.start();
                                }

                            }
                        }
                    }
                    Row{
                        spacing: 5
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
                        Button {
                            text: "csv"
                            onClicked: {
                                //SETUP MAP
                                //update backgroundsize and windowsize to desired map dimensions in mm
                                paper.height = 420;
                                paper.width = 890;
                                //be default resize window with paper dimensions
                                window2.width = paper.width; //but can give the window any size you want(aslong you scale both the width and height by the same dimensions)s
                                window2.height = paper.height;

                                backgroundImg.source = 'qrc:/assets/mediummap-blue.svg'  //load background image

                                myFile.parseData(); //parse csv file so that it can be read
                                myFile.nextLine(); //skip the first line
                                /*robotComm1.setPose( parseFloat(myFile.getcurLineVal(FileIO.POSEX)), parseFloat(myFile.getcurLineVal(FileIO.POSEY)),
                                                       parseFloat(myFile.getcurLineVal(FileIO.POSETHETA)), goalVel,
                                                       parseFloat(myFile.getcurLineVal(FileIO.ANGULARVEL)));*/
                                robotComm1.setPose( parseFloat(myFile.getcurLineVal(FileIO.POSEX)), parseFloat(myFile.getcurLineVal(FileIO.POSEY)),
                                                       parseFloat(myFile.getcurLineVal(FileIO.POSETHETA)), parseFloat(myFile.getcurLineVal(FileIO.VELOCITYX)) ,
                                                       parseFloat(myFile.getcurLineVal(FileIO.VELOCITYY)), parseFloat(myFile.getcurLineVal(FileIO.ANGULARVEL)));
                                //console.log(myFile.getcurLineVal(FileIO.TIMESTAMP));
                                var date2 = Date.fromLocaleString(locale, myFile.getcurLineVal(FileIO.TIMESTAMP), "yyyy-MM-dd hh:mm:ss.zzz")
                                var date1 = Date.fromLocaleString(locale, myFile.getValAtLine(FileIO.TIMESTAMP, myFile.getCurrLine()+1), "yyyy-MM-dd hh:mm:ss.zzz")
                                var deltaT = (date1.getSeconds() - date2.getSeconds())*100 + date1.getMilliseconds()-date2.getMilliseconds();
                                console.log(deltaT);
                                timer.interval = deltaT;
                                timer.start();
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
                            onClicked: robotComm2.setHexagonColor("#FF" + redSlider2.hexStr + greenSlider2.hexStr + blueSlider2.hexStr)
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
                            Button{
                                text: "Enable drag and rotation listen"
                                onClicked: robotPositionFetch.start()
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
            GroupBox{
                title: "Activities and orchestration"
                id: activitiesAndOrchestration
                Row{
                    Column{
                        Row{
                            spacing: 5
                            Label{
                                text: "Number of activities: "
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            SpinBox{
                                id: nbrActivities
                                minimumValue:  1
                                maximumValue: 6
                                stepSize: 1
                                onEditingFinished: {
                                    backgroundImg.source = "qrc:/assets/activities" + value+ ".svg"
                                    if(value > 5){
                                        window2.width = 900
                                    }
                                    else {
                                         window2.width = 700
                                    }
                                    ActivityGlobals.cntActivities = value
                                }
                            }
                        }
                        GroupBox{
                            title: "Orchestration"
                            id: gboxOrchestration
                            Row{
                                height: 50
                                spacing: 10
                                anchors.verticalCenter: parent.verticalCenter
                                Button{
                                    text: "Previous activity"
                                    anchors.verticalCenter: parent.verticalCenter
                                    onClicked: {
                                        ActivityGlobals.currentAct = Math.max(1, ActivityGlobals.currentAct-1)
                                        moveToActivityPosition();
                                    }
                                }
                                GroupBox{
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: 90
                                    Column{
                                        width: parent.width
                                        spacing: 5
                                        anchors.verticalCenter: parent.verticalCenter
                                        Button{
                                            text: "Pause"
                                            onClicked:{
                                                activityTimer.stop();
                                                syncTimer.stop();
                                            }
                                        }
                                        Label{
                                            id: remainingTime
                                            width: parent.width
                                            text : "0"
                                        }
                                        Button{
                                            text: "Unpause"
                                            onClicked:{
                                                activityTimer.interval = 1000*parseInt(remainingTime.text)
                                                activityTimer.start();
                                                syncTimer.start();
                                            }
                                        }
                                        Timer{
                                            id: activityTimer
                                            interval: 0
                                            running: false
                                            repeat: false
                                            onTriggered: {
                                                activityTimer.interval = 0
                                                console.log("activity timed out")
                                                toast.show("Activity timed out")
                                                askMoveToNext.visible = true
                                            }
                                        }
                                        Timer{
                                            id: syncTimer // gets the remaining time (every second to update display)
                                            interval: 1000
                                            running: false
                                            repeat: true
                                            onTriggered: {
                                                let remTime = parseInt(remainingTime.text) - 1
                                                if (remTime >= 0) { remainingTime.text = remTime.toString() }
                                                else { syncTimer.stop(); }
                                            }
                                        }
                                    }
                                }
                                Button{
                                    text: "Next activity"
                                    anchors.verticalCenter: parent.verticalCenter
                                    onClicked: {
                                        ActivityGlobals.currentAct = Math.min(ActivityGlobals.cntActivities, ActivityGlobals.currentAct + 1)
                                        moveToActivityPosition();
                                    }
                                }
                            }
                        }
                        GroupBox{
                            title: "Time activity"
                            Column{
                                Row{
                                    spacing: 5
                                    Button{
                                        width: 150
                                        text: "Increase duration by: "
                                        onClicked: {
                                            let countDownInSeconds = parseInt(remainingTime.text) + parseInt(requestedIncrease.text)
                                            let countDown = 1000*countDownInSeconds
                                            remainingTime.text = countDownInSeconds.toString()
                                            activityTimer.interval = countDown
                                            activityTimer.start()
                                            syncTimer.start();
                                        }
                                    }
                                    TextField{
                                        id: requestedIncrease
                                        placeholderText: " seconds"
                                    }
                                }
                                Row{
                                    spacing: 5
                                    Button{
                                        width:150
                                        text: "Decrease duration by: "
                                        onClicked: {
                                            // stop it (to avoid interruptions while executing)
                                            let countDownInSeconds = parseInt(remainingTime.text) - parseInt(requestedDecrease.text)
                                            activityTimer.stop()
                                            syncTimer.stop()

                                            // now reset it
                                            activityTimer.interval = countDownInSeconds*1000
                                            remainingTime.text = countDownInSeconds.toString()
                                            activityTimer.start()
                                            syncTimer.start();
                                        }
                                    }
                                    TextField{
                                        id: requestedDecrease
                                        placeholderText: " seconds"
                                    }
                                }
                            }
                        }
                    }
                    GroupBox{
                        anchors.top: parent.top
                        anchors.topMargin: 25
                        height: 124
                        title: "Frog Connection"
                        id: frogConnector
                        Column{
                            spacing: 9
                            Button{
                                width: 140
                                text: "Connect to FROG"
                                onClicked: {
                                    orchSocket.url = "ws://localhost:10000/?"+seshSlug.text
                                    orchSocket.active = true;
                                }
                            }
                            TextField{
                                id: seshSlug
                                width: 140
                                placeholderText: "session slug"
                            }
                        }
                        function parseFrogActivities(activities){
                            for (let i= 0; i < activities.length; i++){
                                let actObject = activities[i]
                                let {activityType, title} = actObject
                                ActivityGlobals.allActivities.push({name: title, type: activityType})
                            }
                        }
                        WebSocket {
                            id: orchSocket
                            url: "ws://localhost:10000/?websocketId"
                            onTextMessageReceived: {
                                if (message.startsWith("pause")){
                                    if(!checkIfConnectionStarted()) return
                                    console.log("pause from frog")
                                 }
                                else if (message.startsWith("continue")){
                                   if(!checkIfConnectionStarted()) return
                                   console.log("continue from frog")
                                }
                                 else if (message.startsWith("stop")){
                                    if(!checkIfConnectionStarted()) return
                                    console.log("stop from frog")
                                 }
                                 else if (message.startsWith("begin")){
                                     ActivityGlobals.sessionBegan = true;
                                     let jsonActivites = JSON.parse(message.substring(6))
                                     frogConnector.parseFrogActivities(jsonActivites)
                                 }
                                 else if (message.startsWith("next")){
                                    if(!checkIfConnectionStarted()) return
                                    console.log("next from frog")
                                 }
                                 else if (message.startsWith("prev")){
                                    if(!checkIfConnectionStarted()) return
                                    console.log("next from frog")
                                 }
                                 else if (message.includes("stuck")){
                                    // see the student that is stuck and post it on the on-screen list
                                    if(!checkIfConnectionStarted()) return
                                    console.log("stuck from frog")
                                 }
                                 else if (message.includes("progress")) {
                                    if(!checkIfConnectionStarted()) return
                                    console.log(message)
                                    // o.w. it is not an orchestration action
                                    // Caveat: in order to receive progress from FROG, the progress graph must be displayed on FROG
                                    let parseData = message.split(":")
                                    let progressGraph = (parseData[0]).split(",")
                                    let nbrStudents = parseFloat(parseData[1])
                                    console.log("progress received")
                                 }
                            }
                            onStatusChanged: {
                                if (status == WebSocket.Error) {
                                    console.log("Error: " + errorString)
                                 } else if (status == WebSocket.Open) {
                                    console.log("open")
                                 } else if (status == WebSocket.Closed) {
                                    console.log("closed")
                                 }
                            }
                            active: false
                            function checkIfConnectionStarted(){
                                if (!ActivityGlobals.sessionBegan){
                                    toast.show("Error: Frog did not start with Cellulo.\n Messages will be ignored to prevent undefined session flow")
                                    return false
                                }
                                return true
                            }
                        }

                    }
                    GroupBox{
                        width: 250
                        title: "<font color=\"#FF0000\">Students needing help</font>"
                        // the view ...
                        ListView {
                            model: studentListModel
                            delegate: rowDelegate
                        }
                        // for row formatting
                        Component {
                            id: rowDelegate
                            Column{
                                spacing: 10
                                Text {
                                    text: name
                                    color: "#0000ff"
                                }
                            }
                        }
                        // .. and the model
                        ListModel{
                            id: studentListModel
                        }
                    }
                }
            }
        }
    }
    function moveToActivityPosition(){
        console.log("move robot 2")
        let segmentLength = 500.0/parseFloat(ActivityGlobals.cntActivities)
        let offsetInsideRegion = segmentLength/2

        // border cases
        if (ActivityGlobals.currentAct <= 0 || ActivityGlobals.currentAct > ActivityGlobals.cntActivities){
            console.log("move robot 2 canceled "+ActivityGlobals.currentAct)
            return
        }

        //since activities are 1-indexed need to subtract 1 to get position
        robotComm2.setGoalPosition(segmentLength*(ActivityGlobals.currentAct - 1)+offsetInsideRegion, 245, 60);
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
    Timer{
        id: robotPositionFetch
        interval: 2000
        repeat: true
        running: false
        onTriggered: {
            // If kidnapped, return
            if ((!robotComm2.isSimulation) || robotComm2.vx >= 1 || robotComm2.vy >= 1){ // bug: the robot is always kidnapped in the simulator
                if (robotComm2.kidnapped){
                    console.log("Robot 2 position could not be fetched as it is being moved or is kidnapped")
                    return;
                }
            }

            // end of robot's horizontal position occurs at 500 mm invariant of the screen width (robot does move however on screen re-sizes which is a bit strange)
            let segmentLength = 500.0/parseFloat(ActivityGlobals.cntActivities)
            for (let i=nbrActivities.value - 1; i >= 0 ; i--){
                if (robotComm2.x > i*segmentLength){
                    let currentActivity = i+1
                    if (currentActivity !== ActivityGlobals.currentAct){
                        toast.show("Switched to activity "+ currentActivity.toString())
                    }

                    // Go to activity i+1
                    ActivityGlobals.currentAct = currentActivity
                    moveToActivityPosition()
                }
            }

        }
    }

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

