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

    MessageDialog{
        icon: StandardIcon.Question
        id: askMoveToNext
        visible: false
        text: "The activity has timed out. Move to the next activity?"
        title: "Activity timed out"
        modality: Qt.ApplicationModal
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            activitiesAndOrchestration.sendNextToFrog()
            activitiesAndOrchestration.nextActivity()
        }
        onNo: {
            // do nothing
        }
    }

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
                                onClicked:{
                                    robotPositionFetch.start();
                                    robotAngleFetch.start()
                                }
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
                function resetActivityTimeAndProgress(){
                    robotComm2.setVisualEffect(0, "#FF"+"00"+"00"+"00", 255) // reset the leds also
                    syncTimer.stop()
                    activityTimer.stop()

                    // re-initialize all these fields since a different activity has started
                    ActivityGlobals.elapsedActivityTime = 0
                    ActivityGlobals.totalActivityTime = 1
                    remainingTime.text = "0" // reset displayed time
                    ActivityGlobals.studentIndivProgress = {"" : 0} // empty student name to zero progress by default
                }
                function pause(){
                    activityTimer.stop();
                    syncTimer.stop();
                }
                function unpause(){
                    activityTimer.interval = 1000*parseInt(remainingTime.text)
                    activityTimer.start();
                    syncTimer.start();
                }
                function nextActivity(){
                    resetActivityTimeAndProgress()
                    ActivityGlobals.currentAct = Math.min(ActivityGlobals.cntActivities, ActivityGlobals.currentAct + 1)
                    moveToActivityPosition();
                }
                function prevActivity(){
                    if (ActivityGlobals.currentAct <= 0) return
                    resetActivityTimeAndProgress()
                    ActivityGlobals.currentAct = Math.max(1, ActivityGlobals.currentAct-1)
                    moveToActivityPosition();
                }
                function oscillateForStuckStudent(){
                    // IMPORTANT: only change speed in the non-critical parts of the oscillation
                    // the non-critical part of the oscillation is the midpoint
                    let speed = Math.min(100 + studentListModel.count * 10, 250); // cap speed at 250 to reduce battery wastage

                    if ((cycles%2) === 1) { // if true, this is the midpoint
                       oscillationSpeed = speed;
                    }
                    if ((1 + Math.floor(cycles/2))%2 === 1){ // move up for cycles 0, 1
                         robotComm2.setGoalVelocity(0, oscillationSpeed, 0)
                         oscillationTimer.start()
                     }else{
                        robotComm2.setGoalVelocity(0, -1*oscillationSpeed, 0) // moves down for cycles 2, 3
                        oscillationTimer.start()
                       }
                       cycles = cycles+1
                }
                function updateColor(){
                    let redValue = Math.floor((255.0/ActivityGlobals.totalActivityTime)*ActivityGlobals.elapsedActivityTime)
                    let blueValue = 255 - redValue
                    let redHex = (redValue < 16 ? "0" : "") + redValue.toString(16).toUpperCase()
                    let blueHex = (blueValue < 16 ? "0" : "") + blueValue.toString(16).toUpperCase()
                    ActivityGlobals.colorEncodedTime =  "#FF"+redHex + "00"+blueHex
                }

                function averageProgress(){
                    // get the average progress of the entire class by aggregating over the individual progresses
                    let values = Object.keys(ActivityGlobals.studentIndivProgress).map(function (key) { return ActivityGlobals.studentIndivProgress[key]; });
                    let avgProgress = 0
                    for (let j = 0; j<values.length; j++){  // forEach is not supported so for loop is used for aggregation
                        avgProgress = avgProgress + values[j]
                    }
                    avgProgress = avgProgress/ActivityGlobals.numStudents
                    return avgProgress
                }
                function stddevProgress(){
                    let values = Object.keys(ActivityGlobals.studentIndivProgress).map(function (key) { return ActivityGlobals.studentIndivProgress[key]; });
                    let avgProg = averageProgress()
                    let stddev = 0
                    for (let j = 0; j<values.length; j++){  // forEach is not supported so for loop is used for aggregation
                        stddev = stddev + (avgProg - values[j])*(avgProg - values[j])
                    }
                    stddev = Math.sqrt(stddev)/ActivityGlobals.numStudents
                    return stddev

                }
                function checkStudentPerformanceOk(){
                    // check if student is more than 2 std dev behind students average
                    let avgProg = averageProgress()
                    let avgDev = stddevProgress()

                    for (let j=0; j < ActivityGlobals.studentNames.length; j++){
                        let name = ActivityGlobals.studentNames[j]
                        if (avgProg > (ActivityGlobals.studentIndivProgress[name] + 2*avgDev)){
                            frogConnector.displayStuckStudent(name) // oscillate and display his name on the screen
                        }
                    }


                }
                // the visual effect depends on the type of the activity: for quiz, the number of leds depends on the average student progress. For other activities, every led is on
                function updateLeds(){
                    // Don't update LEDS if session finished
                    if (ActivityGlobals.sessionClosed) return

                    let curActivity = ActivityGlobals.allActivities[ActivityGlobals.currentAct - 1]
                    // get the color based on time
                    updateColor()
                    if (curActivity && curActivity['type'] == "ac-quiz"){ // in this case set leds one by one
                        let avgProg = averageProgress()

                        // adjust number of leds based on progress
                        let nbrLeds = 6 *avgProg
                        for (let ledIdx = 0; ledIdx < nbrLeds; ++ledIdx){
                            robotComm2.setVisualEffect(1,ActivityGlobals.colorEncodedTime, ledIdx)
                        }
                    }
                    else if (curActivity){
                        robotComm2.setVisualEffect(0,ActivityGlobals.colorEncodedTime, 255)
                    }
                    checkStudentPerformanceOk()
                }
                function incrTime(timeIncrease){
                    // stop both timers (to avoid interruptions while executing)
                    activityTimer.stop()
                    syncTimer.stop()

                    // adjust global (current) activity time
                    ActivityGlobals.totalActivityTime = ActivityGlobals.totalActivityTime + timeIncrease

                    // now reset it
                    let countDownInSeconds = Math.max(parseInt(remainingTime.text) + timeIncrease,0)
                    remainingTime.text = countDownInSeconds.toString()
                    activityTimer.interval = 1000*countDownInSeconds
                    activityTimer.start()
                    syncTimer.start()

                }
                function decrTime(timeDecrease){
                    // stop both timers (to avoid interruptions while executing)
                    activityTimer.stop()
                    syncTimer.stop()

                    // adjust global (current) activity time
                    ActivityGlobals.totalActivityTime = ActivityGlobals.totalActivityTime - timeDecrease

                    // now reset it
                    let countDownInSeconds = Math.max(parseInt(remainingTime.text) - timeDecrease,0)
                    activityTimer.interval = countDownInSeconds*1000
                    remainingTime.text = countDownInSeconds.toString()
                    activityTimer.start()
                    syncTimer.start();
                }

                Timer {
                    // interval is twice period of oscillation
                    id: oscillationTimer
                    interval: 500
                    running: false
                    repeat: false
                    onTriggered: activitiesAndOrchestration.oscillateForStuckStudent()
                }
                property int oscillationSpeed: 100
                property int cycles: 1
                property bool stopOscillation: false

                Row{
                    Column{
                        spacing: 20
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
                                        // important: call sendPrev before prevActivity to ensure currentAct is correct inside sendPrev
                                        // same applies to the onclicked of "next activity"
                                        activitiesAndOrchestration.sendPrevToFrog()
                                        activitiesAndOrchestration.prevActivity();
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
                                                activitiesAndOrchestration.pause()
                                                activitiesAndOrchestration.sendPauseToFrog()
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
                                                activitiesAndOrchestration.unpause()
                                                activitiesAndOrchestration.sendContinueToFrog()
                                            }
                                        }
                                        Timer{
                                            id: activityTimer
                                            interval: 0
                                            running: false
                                            repeat: false
                                            onTriggered: {
                                                syncTimer.stop()
                                                activityTimer.stop()
                                                activityTimer.interval = 0
                                                toast.show("Time out")
                                                // if the activities have not yet began or have finished no need to show prompt saying "activity timed out"
                                                if (ActivityGlobals.currentAct <= 0 || ActivityGlobals.currentAct >= ActivityGlobals.cntActivities) return
                                                askMoveToNext.visible = true
                                            }
                                        }
                                        Timer{
                                            id: syncTimer // gets the remaining time (every second to update display)
                                            interval: 1000
                                            running: false
                                            repeat: true
                                            onTriggered: {
                                                ActivityGlobals.elapsedActivityTime = ActivityGlobals.elapsedActivityTime+1
                                                let remTime = parseInt(remainingTime.text) - 1
                                                if (remTime >= 0) { remainingTime.text = remTime.toString() }
                                                else { syncTimer.stop(); }
                                            }
                                        }
                                        Timer{
                                            id: refreshVisualEffect
                                            repeat: true
                                            interval: 1500
                                            running: true
                                            onTriggered: {
                                                activitiesAndOrchestration.updateLeds()
                                            }
                                        }
                                    }
                                }
                                Button{
                                    text: "Next activity"
                                    anchors.verticalCenter: parent.verticalCenter
                                    onClicked: {
                                        // if session began or if the session has not yet began then make the session begin
                                        if (ActivityGlobals.currentAct == 0){
                                            ActivityGlobals.sessionBegan = true
                                            activitiesAndOrchestration.fetchActivitiesFromFrog()
                                        }
                                        activitiesAndOrchestration.sendNextToFrog()
                                        activitiesAndOrchestration.nextActivity(); 
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
                                            activitiesAndOrchestration.incrTime(parseInt(requestedIncrease.text))
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
                                            activitiesAndOrchestration.decrTime(parseInt(requestedDecrease.text))
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
                        anchors.topMargin: 44
                        height: 124
                        title: "Frog Connection"
                        id: frogConnector
                        ColumnLayout{
                            spacing: 9
                            width: 140
                            Button{
                                width: 140
                                text: "Connect to FROG" + " ".repeat(4)
                                onClicked: {
                                    orchSocket.url = "ws://localhost:10000/?"+seshSlug.text
                                    orchSocket.active = true;
                                }
                            }
                            TextField{
                                id: seshSlug
                                width: 140
                                placeholderText: "session slug (e.g. U9XH)"
                            }
                            Label{
                                id: currentActivityName
                                Layout.topMargin: 38
                                text: "Current Activity: "
                            }
                        }
                        function parseFrogActivities(activities){
                            let nbrAct = activities.length

                            // set global variable appropriately to length of activities and update background image
                            ActivityGlobals.cntActivities = nbrAct
                            backgroundImg.source = "qrc:/assets/activities" + nbrAct+ ".svg"

                            // save the activity names and types globally
                            for (let i= 0; i < nbrAct; i++){
                                let actObject = activities[i]
                                let {activityType, title} = actObject
                                ActivityGlobals.allActivities.push({name: title? title:"name", type: activityType?activityType:"type" })
                            }

                            //update text label showing current activity name
                            let curActivityName = ActivityGlobals.allActivities[ActivityGlobals.currentAct - 1]
                            currentActivityName.text = curActivityName? "Current Activity: \n"+curActivityName['name'] : "Current Activity: "
                        }
                        function parseFrogProgress(progressMessage){
                            // message is formatted "progress Amro, 0.2:4" where 0.2 is the progress, and 4 is the last question answered
                            // comma is used to delimit the name of the student from her progress
                            let delimiterIdx = progressMessage.lastIndexOf(",")
                            let secondDelimiterIdx = progressMessage.lastIndexOf(":")
                            let username = progressMessage.substring(("progress ").length, delimiterIdx);
                            let progressIndiv = parseFloat(progressMessage.substring(delimiterIdx+2, secondDelimiterIdx))
                            let questionIndex = parseInt(progressMessage.substring(secondDelimiterIdx+1))
                            ActivityGlobals.studentIndivProgress[username] = progressIndiv
                            return {'progressIndiv' : progressIndiv, 'username':username, 'qIdx': questionIndex}
                        }
                        function displayStuckStudent(username){
                            // add the students name on the list only if it is not there already
                            for(let i = 0; i < studentListModel.count; i++) {
                                if (studentListModel.get(i).name === username) return
                            }
                            studentListModel.append({name: username})

                            // begin oscillating the robot
                            activitiesAndOrchestration.oscillateForStuckStudent()

                            // log it
                            let now = new Date()
                            studentLogger.write("orchestrationHelp"+username+","+ now.toLocaleString())
                        }
                        FileIO{
                            id: studentLogger
                        }
                        WebSocket {
                            id: orchSocket
                            url: "ws://localhost:10000/?websocketId"
                            onTextMessageReceived: {
                                if (message.startsWith("pause")){
                                    if(!checkIfConnectionStarted()) return
                                    activitiesAndOrchestration.pause()
                                 }
                                else if (message.startsWith("continue")){
                                   if(!checkIfConnectionStarted()) return
                                   activitiesAndOrchestration.unpause()
                                }
                                 else if (message.startsWith("closeSession")){
                                    if(!checkIfConnectionStarted()) return
                                    ActivityGlobals.sessionClosed = true
                                    moveToSessionCompletePosition()
                                 }
                                 else if (message.startsWith("begin")){
                                     ActivityGlobals.sessionBegan = true;
                                     let jsonActivites = JSON.parse(message.substring(6))
                                     frogConnector.parseFrogActivities(jsonActivites)
                                     ActivityGlobals.currentAct = 0
                                     activitiesAndOrchestration.nextActivity()
                                 }
                                 else if (message.startsWith("next")){
                                    if(!checkIfConnectionStarted()) return
                                    activitiesAndOrchestration.nextActivity()
                                 }
                                 else if (message.startsWith("prev")){
                                    if(!checkIfConnectionStarted()) return
                                    activitiesAndOrchestration.prevActivity()
                                 }
                                 else if (message.startsWith("stuck")){
                                    // see the student that is stuck and post it on the on-screen list
                                    if(!checkIfConnectionStarted()) return
                                    let username = message.substring(("stuck ".length))
                                    frogConnector.displayStuckStudent(username)
                                 }
                                 else if (message.startsWith("progress")) {
                                    if(!checkIfConnectionStarted()) return
                                    let { progressIndiv, username, qIdx } = frogConnector.parseFrogProgress(message)

                                    // log it
                                    let now = new Date()
                                    studentLogger.write("orchestrationProg"+username+","+ progressIndiv + ","+qIdx +"," +now.toLocaleString())
                                 }
                                else if (message.startsWith("studentCount")){
                                    let skipLength = ("studentCount").length
                                    ActivityGlobals.numStudents = parseInt(message.substring(skipLength))
                                }
                                else if (message.startsWith("activity data")){
                                    let skipLength = ("activity data").length
                                    let jsonActivites = JSON.parse(message.substring(skipLength))
                                    frogConnector.parseFrogActivities(jsonActivites)
                                }else if (message.startsWith("students")){
                                    let skipLength = ("students").length // skip header as usual
                                    let studentMeta = JSON.parse(message.substring(skipLength))

                                    // to keep things simple we use the displayed name as real name (can be easily changed to a real name at the cost of some more code)
                                    for (let j= 0 ; j < studentMeta.length; j++){
                                        let name = studentMeta[j]['displayName']
                                        if (!(ActivityGlobals.studentIndivProgress[name])){
                                            ActivityGlobals.studentIndivProgress[name]= 0
                                        }
                                        ActivityGlobals.studentNames.push(name)
                                    }

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
                        anchors.topMargin: 44
                        anchors.top: parent.top
                        width: 250
                        height: 230
                        title: "Student-Teacher communication"
                        id: studentTeacherGbox
                        Column{
                            anchors.fill: parent
                            spacing: 8
                            Button{
                                text: "Student helped"
                                onClicked: {
                                    // stop the oscillation of the robot if all students are helped
                                    if (studentListModel.count <= 1){
                                        activitiesAndOrchestration.cycles = 1
                                        oscillationTimer.stop()

                                        // send robot back to its normal position
                                        moveToActivityPosition()
                                    }

                                    // and remove student from stuck list
                                    studentListModel.remove(0)
                                }
                            }
                            Label{
                                id: stLabel
                                text:  "<font color=\"#FF0000\">Students needing help</font>"
                            }
                            // the view ...
                            ListView {
                                anchors.top: stLabel.bottom
                                height: 230
                                model: studentListModel
                                delegate: Text {
                                    text: name
                                    color: "#0000ff"
                                }
                            }
                            // .. and the model
                            ListModel{
                                id: studentListModel
                            }
                        }
                    }
                }
                function sendPauseToFrog(){
                    if (ActivityGlobals.sessionBegan && !ActivityGlobals.sessionClosed){
                        orchSocket.sendTextMessage("pause")
                    }
                }
                function sendContinueToFrog(){
                    if (ActivityGlobals.sessionBegan && !ActivityGlobals.sessionClosed){
                        orchSocket.sendTextMessage("continue")
                    }
                }

                // sends a message requesting activities from Frog, so Frog will in turn send a message with the activities (with header "activity data")
                function fetchActivitiesFromFrog(){
                    orchSocket.sendTextMessage("fetch")
                }
                function sendNextToFrog(){
                    // first check if session closed
                    if (ActivityGlobals.sessionClosed) return

                    // If this is not the last activity then do next
                    if (ActivityGlobals.currentAct < ActivityGlobals.cntActivities) {
                        orchSocket.sendTextMessage("next")
                    }else {
                        ActivityGlobals.sessionClosed = true
                        orchSocket.sendTextMessage("stop")
                    }
                }
                function sendPrevToFrog(){
                    if (ActivityGlobals.currentAct > 1 && ActivityGlobals.sessionBegan && !ActivityGlobals.sessionClosed){
                        orchSocket.sendTextMessage("prev")
                    }
                }
            }
        }
    }
    function moveToSessionCompletePosition(){
        // this position (lower right corner) encodes that the session has ended
        toast.show("Session ended")
        activitiesAndOrchestration.resetActivityTimeAndProgress()

        // Turn off leds and go to lower right corner
        ActivityGlobals.colorEncodedTime = "#FF000000"
        robotComm2.setGoalPosition(490, 490, 60);
    }
    function moveToActivityPosition(){
        // bug-fix: disable timers (to avoid interruptions)
        robotAngleFetch.stop()
        robotPositionFetch.stop()

        if (ActivityGlobals.sessionClosed || ActivityGlobals.currentAct > ActivityGlobals.cntActivities) {
            moveToSessionCompletePosition()
            return
        }
        let segmentLength = 500.0/parseFloat(ActivityGlobals.cntActivities)
        let offsetInsideRegion = segmentLength/2

        // border cases
        if (ActivityGlobals.currentAct <= 0){
            console.log("motion of robot 2 canceled "+ActivityGlobals.currentAct)
            return
        }

        // update displayed activity name
        let curActivityName = ActivityGlobals.allActivities[ActivityGlobals.currentAct - 1]
        currentActivityName.text = curActivityName? "Current Activity: \n"+curActivityName['name'] : "Current Activity: "

        //since activities are 1-indexed need to subtract 1 to get position
        robotComm2.setGoalPosition(segmentLength*(ActivityGlobals.currentAct - 1)+offsetInsideRegion, 245, 100);

        // restart the timers
        robotAngleFetch.start()
        robotPositionFetch.start()
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
        interval: 4000
        repeat: true
        running: false
        onTriggered: {

            // If kidnapped, return
            if (!robotComm2.isSimulation){ // bug in simulator? the robot is always kidnapped in the simulator
                if (robotComm2.kidnapped){
                    console.log("Robot 2 position could not be fetched as it is kidnapped")
                    return;
                }
            }

            // check if session ended or if it has not been started
            if (ActivityGlobals.sessionClosed || (!ActivityGlobals.sessionBegan)) return

            // check if robot is in lower right corner (end session)
            if (robotComm2.x> 450 && robotComm2.y > 450){
                // signal session ended in FROG
                ActivityGlobals.sessionClosed = true
                let activityJump = ActivityGlobals.cntActivities - ActivityGlobals.currentAct

                // jump to last activity  in FROG
                orchSocket.sendTextMessage("next:"+activityJump)

                // and then signal stop
                orchSocket.sendTextMessage("stop")

                // move to x, y = (490, 490) which encodes session end
                moveToSessionCompletePosition()
                return
            }

            // end of robot's horizontal position occurs at 500 mm invariant of the screen width (robot does move however on screen re-sizes which is a bit strange)
            let segmentLength = 500.0/parseFloat(ActivityGlobals.cntActivities)

            for (let i=ActivityGlobals.cntActivities - 1; i >= 0 ; i--){
                if (robotComm2.x > i*segmentLength){
                    let currentActivity = i+1
                    if (currentActivity !== ActivityGlobals.currentAct){
                        toast.show("Switched to activity "+ ActivityGlobals.allActivities[i]['name'])
                        activitiesAndOrchestration.resetActivityTimeAndProgress() // reset activity time & progress since moved to a new activity

                        // Go to activity i+1 in Cellulo
                        let activityJump = currentActivity - ActivityGlobals.currentAct
                        ActivityGlobals.currentAct = currentActivity
                        moveToActivityPosition()

                        // and FROG but with a jump (more than a step forward or backward) indicated in the message
                        if (activityJump >0){
                            orchSocket.sendTextMessage("next:"+activityJump)
                        }
                        else {
                            orchSocket.sendTextMessage("prev:"+(-activityJump))
                        }
                    }
                    return
                }
            }

        }
    }
    Timer{
        id: robotAngleFetch
        interval: 2000
        repeat: true
        running: false
        onTriggered: {
            // If kidnapped, return
            if (!robotComm2.isSimulation){
                if (robotComm2.kidnapped){
                    console.log("Robot 2 angular position could not be fetched as it is kidnapped")
                    return;
                }
            }

            // if the session ended return
            if (ActivityGlobals.sessionClosed || (!ActivityGlobals.sessionBegan)) return

            // A rotation of 1 deg  corresponds to 10 more seconds
            let extraTime = Math.floor(10*robotComm2.theta)
            if (extraTime === 0) return

            // BugFix: the robot goes to angle 359 instead of 0 (even when instructed to go to angle zero)
            if (Math.abs(robotComm2.theta - 360) <= 2) return

            // reset angular position
            robotComm2.setGoalOrientation(0, 1)

            // if the angle is greater than 180 degrees, reduce the time
            if (extraTime > 1800) {
                activitiesAndOrchestration.decrTime(extraTime - 1800)
            }
            else{
                activitiesAndOrchestration.incrTime(extraTime)
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

