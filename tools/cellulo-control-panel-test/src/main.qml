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

import "Utils.js" as MyFuncs

Item {
    property var fruitzones: null
    property variant distancelinezones: null
    property variant borderlinezones:null
    property var closestzones: null
    property var distancezones: null
    property var innerzones: null
    property var crossedBorder: []
    property var rectzones:null
    property var locale: Qt.locale()
    property var inLineBorder: [] //had to add this

    function em(x){ return Math.round(x*TextSingleton.font.pixelSize); }
    //move robot based on csv data of the next line
    function updateRobotsWithCSV() {
        if(parseFloat(myFile.getcurLineVal(FileIO.INDEX)) === 0.) {
            //using set goalPose we get a smoother moving robot but often the time intervals are too small for the robot to reach the goalPosition
            //however by increasing the "MAXVINCREMENT" of the robot we can make the robot move faster for the sake of the replay
            /*robotComm1.setPose( parseFloat(myFile.getcurLineVal(FileIO.POSEX)), parseFloat(myFile.getcurLineVal(FileIO.POSEY)),
                                   parseFloat(myFile.getcurLineVal(FileIO.POSETHETA)), 100000,
                                   parseFloat(myFile.getcurLineVal(FileIO.ANGULARVEL)));*/
            //force robot at position in csv file, dont set its velocity because it often makes the robot move in directions that often changed
            //by the player since the player is unpredictable
            //could add a velocity between the current positions and the next position to avoid the strobe effect we sometimes get
            robotComm1.setPose( parseFloat(myFile.getcurLineVal(FileIO.POSEX)), parseFloat(myFile.getcurLineVal(FileIO.POSEY)),
                                   parseFloat(myFile.getcurLineVal(FileIO.POSETHETA)), 0/*parseFloat(myFile.getcurLineVal(FileIO.VELOCITYX))*/ ,
                                   /*parseFloat(myFile.getcurLineVal(FileIO.VELOCITYY))*/0, 0/*parseFloat(myFile.getcurLineVal(FileIO.ANGULARVEL))*/);
        }
        //could add a velocity between the current positions and the next position to avoid the strobe effect we sometimes get
        if(parseFloat(myFile.getcurLineVal(FileIO.INDEX)) === 1) {
            robotComm2.setPose( parseFloat(myFile.getcurLineVal(FileIO.POSEX)), parseFloat(myFile.getcurLineVal(FileIO.POSEY)),
                                   parseFloat(myFile.getcurLineVal(FileIO.POSETHETA)), 0 , 0,0);

        }


        //get timeLaspse between this line and the next line and set the timer to that time interval
        var date2 = Date.fromLocaleString(locale, myFile.getcurLineVal(FileIO.TIMESTAMP), "yyyy-MM-dd hh:mm:ss.zzz")
        var date1 = Date.fromLocaleString(locale, myFile.getValAtLine(FileIO.TIMESTAMP, myFile.getCurrLine()+1), "yyyy-MM-dd hh:mm:ss.zzz")
        var deltaT = (date1.getHours() - date2.getHours())*60*60*1000 + (date1.getMinutes() - date2.getMinutes())*60*1000
                    + (date1.getSeconds() - date2.getSeconds())*1000 + date1.getMilliseconds()-date2.getMilliseconds();
        if(deltaT === 0) deltaT = 1; //if deltaT is 0, to avoid timer stopping we set it to 1
        timer.interval = deltaT;
        myFile.nextLine();

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

        width: 600
        height: mobile ? Screen.desktopAvailableHeight : 450;
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

        FileIO {
            id : myFile
            source : ":/assets/rawdataExample.csv"
            onError: console.log(msg)
        }

        Component.onCompleted: {
               //do nothing
        }

        //timer used for to know to updateRobotsWith data in CSV
        Timer {
            id: timer;
            interval: 150; running: true; repeat: true
            onTriggered: updateRobotsWithCSV()
        }
    }

    ControlsWindow{}


}
