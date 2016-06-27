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

        CelluloZoneCircleInner{
            name: "MY_ZONE_DUDE"

            x: 630
            y: 140
            r: 50
        }

        CelluloZoneCircleInner{
            name: "MY_ZONE_DUDE_SMALLER"

            x: 630
            y: 140
            r: 25

            onXChanged: console.log(x)
        }
    }

    Button{
        text: "zonetoright"
        onClicked: zoneEngine.getZoneByName("MY_ZONE_DUDE_SMALLER").x = 680
    }

    CelluloBluetooth{
        id: btClient
        macAddr: "00:06:66:74:41:4C"

        Component.onCompleted: zoneEngine.addNewClient(btClient)

        onZoneValueChanged: console.log(value + " " + zone.name + " " + zone)
    }
}
