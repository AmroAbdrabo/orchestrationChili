import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    minimumHeight: height
    minimumWidth: width

    CelluloLocalRelayClient{
        id: client
        autoConnect: true
    }

    Column{
        spacing: 5
        anchors.margins: 10
        anchors.verticalCenter: parent.verticalCenter

        Text{ text: "Cellulo robot pool service for Android" }

        Button{
            text: "Start service"
            onClicked: {
                CelluloCommUtil.startRobotPoolDaemon();
                client.connectToServer();
            }
        }

        Button{
            text: "Stop service"
            onClicked: CelluloCommUtil.stopRobotPoolDaemon()
        }

        Text{
            text: client.connected ? "Service running, you can now close this app." : "Trying to connect to service (may not be running)..."
            color: client.connected ? "green" : "black"
        }
    }
}
