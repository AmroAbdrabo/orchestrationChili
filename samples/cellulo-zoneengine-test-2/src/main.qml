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

        /*CelluloZoneCircleInner{
            id: zone1
            name: "MY_ZONE_DUDE"

            x: 630
            y: 140
            r: 50
        }*/
    }

    Row{
        Button{
            text: "listofzones"
            onClicked: console.log(zoneEngine.getAllZoneNames())
        }

        Button{
            text: "addnewzone"
            onClicked: {
                Qt.createQmlObject(
                            '
                                    import Cellulo 1.0
                                    CelluloZoneCircleInner{
                                        name:"DYNAZONE"
                                        x: 630
                                        y: 140
                                        r: 50
                                    }
                               ',
                            zoneEngine, "dynamicallyCreatedZone");


            }
        }

        Button{
            text: "savezones"
            onClicked: CelluloZoneJsonHandler.saveZones(zoneEngine.zones, "/home/equilibrium/zones.json")
        }

        Button{
            text: "savezonesinline"
            onClicked: {
                CelluloZoneJsonHandler.saveZones([zone1], "/home/equilibrium/zones.json")
            }
        }

        Button{
            text: "loadzones"
            onClicked: {
                zoneEngine.addNewZones(CelluloZoneJsonHandler.loadZonesQML("/home/equilibrium/zones.json"))
            }
        }
    }

    CelluloBluetooth{
        id: btClient
        macAddr: "00:06:66:74:41:4C"

        Component.onCompleted: zoneEngine.addNewClient(btClient)

        onZoneValueChanged: console.log(value + " " + zone.name + " " + zone)
    }
}
