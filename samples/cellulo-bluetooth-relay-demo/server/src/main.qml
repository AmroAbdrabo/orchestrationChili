import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import QMLCache 1.0
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    CelluloLocalRelayServer{
        id: server

        onClientConnected: console.log("Server: Client connected.")
        onClientDisconnected: console.log("Server: Client disconnected.")

        onRobotAdded: console.log("Server: Robot added: " + macAddr)
        onRobotRemoved: console.log("Server: Robot removed: " + macAddr)
    }
}
