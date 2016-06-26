import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.2
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: 100
    minimumWidth: 200

    CelluloZoneEngine{
        id: zoneEngine
    }

    CelluloBluetooth{
        id: btClient
        macAddr: "00:06:66:74:41:4C"

        Component.onCompleted: zoneEngine.addNewClient(btClient)

        onZoneValueChanged: console.log(value + " " + zone.name)
    }

    CelluloZoneCircleInner{
        id: circleInnerZone

        name: "MY_ZONE_DUDE"

        Component.onCompleted: zoneEngine.addNewZone(circleInnerZone)

        x: 630
        y: 140
        r: 50
    }

}
