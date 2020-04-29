import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3

import Cellulo 1.0
import QMLCache 1.0
import QMLBluetoothExtras 1.0
import hexagon.qml 1.0

Item {
     property var fruitzones: null
     function em(x){ return Math.round(x*TextSingleton.font.pixelSize); }
     function createZones(){
                 fruitzones = CelluloZoneJsonHandler.loadZonesQML(":/assets/orangefruits.json");

                 for(var l=0;l<fruitzones.length;l++){
                     fruitzones[l].active = true;
                     zoneEngine.addNewZone(fruitzones[l])
                 }

     }
     property bool mobile: Qt.platform.os === "android"
     property bool winrt: Qt.platform.os === "winrt"
     property real gWidth: mobile ? Screen.width : 800
     property bool activateManual: false

    //window for robot and grid
    Window {
        objectName: "robot display window"
        id: window2
        visible: true


        CelluloZoneEngine{
                id: zoneEngine
                active: true

        }

        width: 500
        height: mobile ? Screen.desktopAvailableHeight : 500;
        ToastManager{ id: toast }
        Image{
            id: backgroundImg
            source: 'qrc:/assets/redgrid.svg'
            x:0
            y:0
            sourceSize: Qt.size( window2.width, window2.height )
        }

        MyCelluloRobot{
            id: robotComm1
            color: "blue"
        }

        MyCelluloRobot{
            id: robotComm2
            color: "red"
        }

    }

    ControlsWindow{}

}
