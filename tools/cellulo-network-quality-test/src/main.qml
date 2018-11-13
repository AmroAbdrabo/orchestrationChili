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

    minimumWidth: width
    minimumHeight: height

    width: mobile ? Screen.width : 0.7*Screen.width
    height: mobile ? Screen.desktopAvailableHeight : 0.7*Screen.height

    property var client: poolButton.checked ? poolClient : hubClient

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
                                text: "100"
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            Button{
                                text: "Set"
                                anchors.verticalCenter: parent.verticalCenter

                                onClicked: {
                                    for(var i=0;i<client.robots.length;i++)
                                        client.robots[i].setPoseBcastPeriod();
                                }
                            }
                        }

                        Row{
                            spacing: 5

                            Button{
                                text: "Reset All"

                            }
                        }
                    }
                }

            }

            GroupBox{
                title: "Robots"

                Column{

                    Repeater{
                        model: client.robots.length

                        Row{
                            spacing: 5

                            CircularBuffer{
                                id: periods
                                size: 100

                                property real sum: 0
                                property real mean: 0
                                property real variance: 0
                                property real stdev: 0

                                onElementAdded: {
                                    var oldsum = sum;
                                    sum += element;
                                    var oldmean = mean;
                                    var N_plus_1 = elements.length;
                                    mean = sum/N_plus_1;
                                    var oldvariance = variance;
                                    variance = N_plus_1 > 1 ? (element*element + (N_plus_1 - 1)*oldmean*oldmean - N_plus_1*mean*mean + (N_plus_1 - 2)*oldvariance)/(N_plus_1 - 1) : 0;
                                    stdev = Math.sqrt(variance);
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
                                }
                            }

                            Connections{
                                target: client.robots[index]

                                onPoseChanged: {

                                }

                                onKidnappedChanged: {

                                }
                            }

                            Text{
                                text: client.robots[index].macAddr
                                anchors.verticalCenter: parent.verticalCenter
                            }
/*
                            ChartView{
                                id: periodChart

                                anchors.verticalCenter: parent.verticalCenter

                                property var startT: 0

                                function clear(){
                                    startT = 0;
                                    removeAllSeries();
                                    createSeries(ChartView.SeriesTypeLine, "", axisXAng, axisYAng);
                                    createSeries(ChartView.SeriesTypeLine, "", axisXAng, axisYAng);
                                }

                                function add(t, angle){
                                    while(angle < robot.testAngles[index] - 180)
                                        angle += 360;
                                    while(angle > robot.testAngles[index] + 180)
                                        angle -= 360;

                                    var ideal = series(0);
                                    if(startT == 0){
                                        startT = t;
                                        axisXAng.min = startT;
                                        axisXAng.max = startT + 1;

                                        ideal.append(startT, robot.testAngles[index]);
                                        ideal.append(startT + 1, robot.testAngles[index]);
                                    }
                                    else{
                                        axisXAng.max = t;
                                        ideal.remove(1);
                                        ideal.append(t, robot.testAngles[index]);
                                    }

                                    var measured = series(1);
                                    measured.append(t, angle);
                                }

                                backgroundRoundness: 0
                                legend.visible: false
                                backgroundColor: "transparent"
                                margins.left: 0; margins.right: 0; margins.top: 0; margins.bottom: 0
                                width: resultsBox.width/2 - 30/2 - testAngleText.width/2
                                height: width/2
                                antialiasing: true

                                ValueAxis {
                                    id: axisYAng
                                    min: robot.testAngles[index] - 45
                                    max: robot.testAngles[index] + 45
                                }

                                ValueAxis {
                                    id: axisXAng
                                    min: 0
                                    max: 1
                                }
                            }
                            */
                        }
                    }
                }
            }
        }
    }
}
