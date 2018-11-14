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
    readonly property real maxPeriod: 5000

    CelluloRobotPoolClient{
        id: poolClient

        autoConnect: poolButton.checked
        onAutoConnectChanged: {
            if(!autoConnect)
                disconnectFromServer();
        }
    }

    CelluloRobotHubClient{
        id: hubClient

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
                    title: "Server"

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
                    title: "Controls"

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
                                    expectedPeriod = parseInt(periodTextField.text);
                                    for(var i=0;i<client.robots.length;i++)
                                        client.robots[i].setPoseBcastPeriod(expectedPeriod);
                                }
                            }
                        }

                        Row{
                            spacing: 5

                            CheckBox{
                                id: go
                                checked: false
                                text: "Go!"
                                anchors.verticalCenter: parent.verticalCenter
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

            }

            GroupBox{
                title: "Individual Robots"

                Column{

                    Repeater{
                        model: client.robots.length

                        Row{
                            spacing: 20

                            CircularBuffer{
                                id: periods
                                size: 100

                                property real sum: 0
                                property real mean: 0
                                property real variance: 0
                                property real stdev: 0
                                property real min: maxPeriod
                                property real max: 0

                                onElementAdded: {
                                    var oldsum = sum;
                                    sum += element;
                                    var oldmean = mean;
                                    var N_plus_1 = elements.length;
                                    mean = sum/N_plus_1;
                                    var oldvariance = variance;
                                    variance = N_plus_1 > 1 ? (element*element + (N_plus_1 - 1)*oldmean*oldmean - N_plus_1*mean*mean + (N_plus_1 - 2)*oldvariance)/(N_plus_1 - 1) : 0;
                                    stdev = Math.sqrt(variance);

                                    if(element > max)
                                        max = element;
                                    if(element < min)
                                        min = element;
                                }
                                onElementRemoved: {
                                    var oldsum = sum;
                                    sum -= element;
                                    var oldmean = mean;
                                    var N_minus_1 = elements.length;
                                    mean = N_minus_1 > 0 ? sum/N_minus_1 : 0;
                                    var oldvariance = variance;
                                    variance = N_minus_1 > 1 ? (-element*element + (N_minus_1 + 1)*oldmean*oldmean - N_minus_1*mean*mean + N_minus_1*oldvariance)/(N_minus_1 - 1) : 0;
                                    stdev = Math.sqrt(variance);

                                    if(element == min)
                                        findMin();
                                    if(element == max)
                                        findMax();
                                }

                                function findMin(){
                                    min = maxPeriod;
                                    for(var i=0;i<elements.length;i++)
                                        if(elements[i] < min)
                                            min = elements[i];
                                }

                                function findMax(){
                                    max = 0;
                                    for(var i=0;i<elements.length;i++)
                                        if(elements[i] > max)
                                            max = elements[i];
                                }
                            }

                            Connections{
                                target: client.robots[index]

                                property real lastTimestamp: 0
                                readonly property real maxPeriod: 2000

                                onPoseChanged: {
                                    if(go.checked){
                                        client.robots[index].setGoalVelocity(0,0,1.0);

                                        var timestamp = Date.now();
                                        var period = timestamp - lastTimestamp;
                                        if(period < maxPeriod){
                                            periods.add(period - expectedPeriod);
                                            periodChart.add(timestamp, period - expectedPeriod);
                                        }
                                        lastTimestamp = timestamp;
                                    }
                                    else
                                        client.robots[index].setGoalVelocity(0,0,0);
                                }

                                onKidnappedChanged: lastTimestamp = 0

                                onConnectionStatusChanged: {
                                    if(client.robots[index].connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                                        client.robots[index].setPoseBcastPeriod(expectedPeriod);
                                }

                                onBootCompleted: client.robots[index].setPoseBcastPeriod(expectedPeriod);
                            }

                            Text{
                                id: macAddrText
                                text: client.robots[index].macAddr
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            ChartView{
                                id: periodChart

                                anchors.verticalCenter: parent.verticalCenter

                                Component.onCompleted: clear()

                                function clear(){
                                    removeAllSeries();
                                    var dataSeries = createSeries(ChartView.SeriesTypeLine, "", axisX, axisY);
                                }

                                function add(t, period){
                                    var dataSeries = series(0);
                                    dataSeries.append(t, period);
                                    if(dataSeries.count > periods.size)
                                        dataSeries.remove(0);

                                    axisX.min = new Date(dataSeries.at(0).x);
                                    axisX.max = new Date(t);

                                    axisY.min = periods.min;
                                    axisY.max = periods.max;
                                    axisY.applyNiceNumbers();
                                }

                                backgroundRoundness: 0
                                legend.visible: false
                                backgroundColor: "transparent"
                                margins.left: 0; margins.right: 0; margins.top: 0; margins.bottom: 0
                                width: window.width - macAddrText.width - individualResultText.width - 2*parent.spacing - 20
                                height: Math.max(window.height - firstRow.height - qualityGroupBox.height - 20, 150)
                                antialiasing: true

                                ValueAxis {
                                    id: axisY
                                    min: 0
                                    max: 2*expectedPeriod
                                    titleText: "ΔP (ms)"
                                }

                                DateTimeAxis {
                                    id: axisX
                                    format: "mm:ss"
                                    titleText: "Timestamp"
                                }
                            }

                            Text{
                                id: individualResultText
                                text: "ΔP = " + periods.mean.toPrecision(2) + "±" + periods.stdev.toPrecision(2) + " ms = " + (100.0*periods.mean/expectedPeriod).toPrecision(2) + "±" + (100.0*periods.stdev/expectedPeriod).toPrecision(2) + " %P"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                }
            }
        }
    }
}
