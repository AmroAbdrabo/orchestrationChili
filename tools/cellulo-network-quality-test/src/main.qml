import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import QMLCache 1.0
import QMLBluetoothExtras 1.0
import QMLExtraDataStructures 1.0
import Cellulo 1.0
import QtCharts 2.2

ApplicationWindow {
    id: window
    visible: true

    property bool mobile: android
    property bool android: Qt.platform.os === "android"
    property bool osx: Qt.platform.os === "osx"
    property bool winrt: Qt.platform.os === "winrt"

    function em(x){ return Math.round(x*TextSingleton.font.pixelSize); }

    Component.onCompleted: {
        width = mobile ? Screen.width : 0.8*Screen.width;
        height = mobile ? Screen.desktopAvailableHeight : 0.8*Screen.height;
    }

    property var client: poolButton.checked ? poolClient : hubClient

    property real expectedPeriod: 100
    readonly property real angularVelAbs: 2.0
    readonly property real angularVelTransitionThreshold: 0.5

    CelluloRobotPoolClient{
        id: poolClient

        robotComponent: Qt.createComponent("MeasurementRobot.qml")

        autoConnect: poolButton.checked
        onAutoConnectChanged: {
            if(!autoConnect)
                disconnectFromServer();
        }
    }

    CelluloRobotHubClient{
        id: hubClient

        robotComponent: Qt.createComponent("MeasurementRobot.qml")

        serverAddress: hubAddress.text
        port: parseInt(hubPort.text)

        autoConnect: hubButton.checked
        onAutoConnectChanged: {
            if(!autoConnect)
                disconnectFromServer();
        }
    }

    ScrollView {
        anchors.fill: parent
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: mobile ? Qt.ScrollBarAsNeeded : Qt.ScrollBarAlwaysOff

        Column{

            Row{
                id: firstRow

                GroupBox{
                    title: "Server Controls"

                    Column{
                        Row{
                            spacing: 5

                            ExclusiveGroup{ id: serverGroup }
                            RadioButton{
                                id: poolButton
                                text: "Pool (Local)"
                                checked: true
                                exclusiveGroup: serverGroup
                            }
                            RadioButton{
                                id: hubButton
                                text: "Hub (Remote, e.g at RPi)"
                                exclusiveGroup: serverGroup
                            }
                        }

                        GroupBox {
                            title: "Hub Address"
                            enabled: hubButton.checked

                            Row{
                                spacing: 5

                                Text{
                                    text: "Address:"
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                TextField{
                                    id: hubAddress
                                    text: "192.168.2.1"
                                }

                                Text{
                                    text: "Port:"
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                TextField{
                                    id: hubPort
                                    text: "2556"
                                }
                            }
                        }

                        Text{
                            text: {
                                switch(client.connectionStatus){
                                case CelluloCommUtil.RelayConnectionStatusDisconnected: return "Disconnected.";
                                case CelluloCommUtil.RelayConnectionStatusConnecting: return "Connecting to Server...";
                                case CelluloCommUtil.RelayConnectionStatusConnected: return "Connected to Server.";
                                }
                            }
                            color: {
                                switch(client.connectionStatus){
                                case CelluloCommUtil.RelayConnectionStatusDisconnected: return "red";
                                case CelluloCommUtil.RelayConnectionStatusConnecting: return "yellow";
                                case CelluloCommUtil.RelayConnectionStatusConnected: return "green";
                                }
                            }
                        }
                    }
                }

                GroupBox{
                    title: "Communication Controls"

                    enabled: client.connectionStatus === CelluloCommUtil.RelayConnectionStatusConnected

                    Column{
                        spacing: 5

                        Row{
                            spacing: 5

                            Text{
                                text: "Control period:"
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            TextField{
                                id: periodTextField
                                text: "100"
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            Button{
                                text: "Set"
                                anchors.verticalCenter: parent.verticalCenter
                                onClicked: {
                                    var p = parseInt(periodTextField.text);
                                    if(p < 10){
                                        p = 10;
                                        periodTextField.text = 10;
                                    }
                                    expectedPeriod = p;
                                    for(var i=0;i<client.robots.length;i++)
                                        client.robots[i].setPoseBcastPeriod(expectedPeriod);
                                }
                            }
                        }

                        CheckBox{
                            id: velocityTraffic
                            checked: true
                            text: "Send velocity at every loop"
                        }

                        CheckBox{
                            id: colorTraffic
                            checked: true
                            text: "Send color at every loop"
                        }

                        Row{
                            spacing: 5

                            CheckBox{
                                id: go
                                checked: false
                                text: "Go!"
                                anchors.verticalCenter: parent.verticalCenter
                                onCheckedChanged: {
                                    if(checked)
                                        for(var i=0;i<client.robots.length;i++)
                                            client.robots[i].setGoalVelocity(0,0,1.0);
                                }
                            }

                            Button{
                                text: "Reset All"
                                anchors.verticalCenter: parent.verticalCenter
                                onClicked: {
                                    for(var i=0;i<client.robots.length;i++)
                                        client.robots[i].reset();
                                }
                            }
                        }
                    }
                }

            }

            GroupBox{
                id: qualityGroupBox
                title: "Overall Quality"

                Row{
                    spacing: 10

                    Column{
                        id: overallQualityTexts

                        anchors.verticalCenter: parent.verticalCenter

                        /*Text{
                            text: "Total outliers (P outside 3 σ) = " + qualityGroupBox.outliers + " = " + (100.0*qualityGroupBox.outliers/qualityGroupBox.numSamples).toPrecision(3) + " %"
                        }

                        Text{
                            text: "Total drops (P more than > " + maxPeriod + " ms) = " + qualityGroupBox.drops + " = " + (100.0*qualityGroupBox.drops/qualityGroupBox.numSamples).toPrecision(3) + " %"
                        }*/
                    }

                   /* ChartView{
                        id: qualityChart

                        property int size: 50

                        anchors.verticalCenter: parent.verticalCenter

                        Component.onCompleted: clear()

                        function clear(){
                            removeAllSeries();
                            var outlierSeries = createSeries(ChartView.SeriesTypeLine, "Outlier Rate", axisXQualityChart, axisYQualityChart);
                            var dropSeries = createSeries(ChartView.SeriesTypeLine, "Drop Rate", axisXQualityChart, axisYQualityChart);
                        }

                        function add(t, outliers, drops){
                            var outlierSeries = series(0);
                            outlierSeries.append(t, outliers);
                            if(outlierSeries.count > qualityChart.size)
                                outlierSeries.remove(0);

                            var dropSeries = series(1);
                            dropSeries.append(t, drops);
                            if(dropSeries.count > qualityChart.size)
                                dropSeries.remove(0);

                            axisXQualityChart.min = new Date(outlierSeries.at(0).x);
                            axisXQualityChart.max = new Date(t);

                            axisYQualityChart.min = 0;
                            axisYQualityChart.max = 100;
                            axisYQualityChart.applyNiceNumbers();
                        }

                        backgroundRoundness: 0
                        backgroundColor: "transparent"
                        margins.left: 0; margins.right: 0; margins.top: 0; margins.bottom: 0
                        width: window.width - overallQualityTexts.width - 2*parent.spacing - 20
                        height: 300
                        antialiasing: true

                        ValueAxis {
                            id: axisYQualityChart
                            min: 0
                            max: 100
                            titleText: "%"
                        }

                        DateTimeAxis {
                            id: axisXQualityChart
                            format: "mm:ss"
                            titleText: "Timestamp"
                        }
                    }*/
                }

                /*StatCircularBuffer{
                    id: overallPeriods
                    size: client.robots.length*Math.max(30*expectedPeriod, 1000)/expectedPeriod
                }*/

                /*Timer{
                    interval: Math.max(30*expectedPeriod, 1000)
                    repeat: true
                    running: go.checked
                    onTriggered: {
                        qualityGroupBox.outliers = qualityGroupBox.newOutliers;
                        qualityGroupBox.drops = qualityGroupBox.newDrops;
                        qualityGroupBox.numSamples = qualityGroupBox.newNumSamples;
                        qualityGroupBox.newOutliers = 0;
                        qualityGroupBox.newDrops = 0;
                        qualityGroupBox.newNumSamples = 0;

                        qualityChart.add(Date.now(), 100.0*qualityGroupBox.outliers/qualityGroupBox.numSamples, 100.0*qualityGroupBox.drops/qualityGroupBox.numSamples);
                    }
                }*/
            }

            GroupBox{
                title: "Individual Connection Quality"

                Column{

                    Repeater{
                        model: client.robots.length

                        Row{
                            id: calculators

                            state: "ClockwiseBegin"
                            states: [
                                State{ name: "ClockwiseBegin" },
                                State{ name: "ClockwiseWait" },
                                State{ name: "CounterClockwiseBegin" },
                                State{ name: "CounterClockwiseWait" }
                            ]

                            spacing: 20

                            StatCircularBuffer{
                                id: delays
                                size: 20
                            }

                            property int resetInitPositionIn: 1
                            property vector2d initPosition: Qt.vector2d(0,0)
                            property real beginTimestamp: 0

                            Connections{
                                target: go
                                onCheckedChanged: {
                                    if(go.checked){
                                        calculators.resetInitPositionIn = 1;
                                        state = "ClockwiseBegin";
                                    }
                                }
                            }

                            Connections{
                                target: client.robots[index]

                                onPoseChanged: {
                                    if(go.checked){
                                        if(velocityTraffic.checked){
                                            if(calculators.resetInitPositionIn >= 2){
                                                client.robots[index].setGoalVelocity(0,0,0);
                                                calculators.resetInitPositionIn--;
                                            }
                                            else if(calculators.resetInitPositionIn == 1){
                                                client.robots[index].setGoalVelocity(0,0,0);
                                                calculators.initPosition = Qt.vector2d(client.robots[index].x, client.robots[index].y);
                                                calculators.resetInitPositionIn--;
                                            }
                                            else{
                                                var linearVel = calculators.initPosition.minus(Qt.vector2d(client.robots[index].x, client.robots[index].y)).times(1.5);
                                                var linearVelLen = linearVel.length();
                                                if(linearVelLen > 50)
                                                    linearVel = linearVel.times(50/linearVelLen);

                                                switch(calculators.state){
                                                case "ClockwiseBegin":
                                                    calculators.beginTimestamp = Date.now();
                                                    calculators.state = "ClockwiseWait";
                                                case "ClockwiseWait":
                                                    client.robots[index].setGoalVelocity(linearVel.x, linearVel.y, angularVelAbs);
                                                    break;
                                                case "CounterClockwiseBegin":
                                                    calculators.beginTimestamp = Date.now();
                                                    calculators.state = "CounterClockwiseWait";
                                                case "CounterClockwiseWait":
                                                    client.robots[index].setGoalVelocity(linearVel.x, linearVel.y, -angularVelAbs);
                                                    break;
                                                }
                                            }
                                        }
                                        if(colorTraffic.checked)
                                            client.robots[index].setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, Qt.hsva(Math.random(), 1.0, 0.5, 1.0), 0.0);
                                    }
                                    else{
                                        client.robots[index].setGoalVelocity(0,0,0);
                                        client.robots[index].setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#808080", 0.0);
                                    }
                                }

                                onWChanged: {
                                    var t, delay;
                                    switch(calculators.state){
                                    case "ClockwiseWait":
                                        if(client.robots[index].w > angularVelTransitionThreshold*angularVelAbs){
                                            t = Date.now();
                                            delay = t - calculators.beginTimestamp;
                                            delays.add(delay);
                                            delayChart.add(t, delay);
                                            calculators.state = "CounterClockwiseBegin";
                                        }
                                        break;
                                    case "CounterClockwiseWait":
                                        if(client.robots[index].w < -angularVelTransitionThreshold*angularVelAbs){
                                            t = Date.now();
                                            delay = t - calculators.beginTimestamp;
                                            delays.add(delay);
                                            delayChart.add(t, delay);
                                            calculators.state = "ClockwiseBegin";
                                        }
                                        break;
                                    default:
                                        break;
                                    }
                                }

                                onKidnappedChanged: {
                                    if(!client.robots[index].kidnapped){
                                        calculators.resetInitPositionIn = 10;
                                        calculators.state = "ClockwiseBegin";
                                    }
                                }

                                onConnectionStatusChanged: {
                                    if(client.robots[index].connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                                        client.robots[index].setPoseBcastPeriod(expectedPeriod);
                                }

                                onBootCompleted: client.robots[index].setPoseBcastPeriod(expectedPeriod)
                            }

                            Text{
                                id: macAddrText
                                text: client.robots[index].macAddr
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            ChartView{
                                id: delayChart

                                anchors.verticalCenter: parent.verticalCenter

                                Component.onCompleted: clear()

                                function clear(){
                                    removeAllSeries();
                                    var dataSeries = createSeries(ChartView.SeriesTypeLine, "", axisXDelayChart, axisYDelayChart);
                                }

                                function add(t, delay){
                                    var dataSeries = series(0);
                                    dataSeries.append(t, delay);
                                    if(dataSeries.count > delays.size)
                                        dataSeries.remove(0);

                                    axisXDelayChart.min = new Date(dataSeries.at(0).x);
                                    axisXDelayChart.max = new Date(t);

                                    axisYDelayChart.min = delays.min;
                                    axisYDelayChart.max = delays.max;
                                    axisYDelayChart.applyNiceNumbers();
                                }

                                backgroundRoundness: 0
                                legend.visible: false
                                backgroundColor: "transparent"
                                margins.left: 0; margins.right: 0; margins.top: 0; margins.bottom: 0
                                width: window.width - macAddrText.width - individualResults.width - 2*parent.spacing - 20
                                height: Math.max((window.height - firstRow.height - qualityGroupBox.height - 20)/client.robots.length, 150)
                                antialiasing: true

                                ValueAxis {
                                    id: axisYDelayChart
                                    min: 0
                                    max: 1000
                                    titleText: "Delay (ms)"
                                }

                                DateTimeAxis {
                                    id: axisXDelayChart
                                    format: "mm:ss"
                                    titleText: "Timestamp"
                                }
                            }

                            Column{
                                id: individualResults

                                anchors.verticalCenter: parent.verticalCenter

                                Text{
                                    text: "Delay = " + delays.mean.toPrecision(5) + "±" + delays.stdev.toPrecision(5) + " ms = " + (100.0*delays.mean/expectedPeriod).toPrecision(5) + "±" + (100.0*delays.stdev/expectedPeriod).toPrecision(5) + " %Period"
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
