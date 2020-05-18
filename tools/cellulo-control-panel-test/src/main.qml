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
import FileIO.qml 1.0

Item {
    property var fruitzones: null
    property variant distancelinezones: null
    property variant borderlinezones:null
    property var closestzones: null
    property var distancezones: null
    property var innerzones: null
    property var crossedBorder: []
    property var rectzones:null
    property var inLineBorder: [] //had to add this

    function em(x){ return Math.round(x*TextSingleton.font.pixelSize); }

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
            source: "qrc:/assets/redgrid.svg"
            x:0
            y:0
            sourceSize: Qt.size( window2.width, window2.height )
        }

        MyCelluloRobot{
            id: robotComm1
        }

        MyCelluloRobot{
            id: robotComm2
        }

        //read csv file
        /*Text {
            id: myText
            text: "Hello World"
            anchors.centerIn: parent
        }*/

        FileIO {
            id : myFile
            source : ":/assets/rawdataExample.csv" //why this doesnt work?
            //source : "/home/gianni/Desktop/cellulo/cellulo-qml-plugin/tools/cellulo-control-panel-test/assets/rawdataExample.csv"
            onError: console.log(msg)
        }

        Component.onCompleted: {
            //console.log( "WRITE"+ myFile.write("TEST WRITE SOMETHING AMAZING IN THIS FILE WOOOOO"));
            //myText.text =  myFile.read();
            //var data = myFile.read();
            //myFile.parseData();
            //console.log("DATA LOADED" + data)
        }

    }

    ControlsWindow{}


}
