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


                        }
                    }
                }
            }
        }
    }
}
