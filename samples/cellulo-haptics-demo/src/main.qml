import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3
import Cellulo 1.0

ApplicationWindow {
    id: root
    visible: true

    width: 640
    height: 480

    property real mapHalfWidth: 210/2
    property real mapHalfHeight: 297/2
    property real mapHalfBorder: 60/2

    property variant currentHaptics: {
        "xyAssist": 0.0,
        "thetaAssist": 0.0,
        "vibrateIntensity": 0.0,
        "logText": ""
    }

    property variant zoneHaptics: {
        "ICE": {
            "xyAssist": 0.9,
            "thetaAssist": 0.9,
            "vibrateIntensity": 0.0
        },
        "MUD": {
            "xyAssist": 0.3,
            "thetaAssist": 0.3,
            "vibrateIntensity": 0.0
        },
        "SANDPAPER": {
            "xyAssist": -0.3,
            "thetaAssist": -0.3,
            "vibrateIntensity": 0.0
        },
        "STONES": {
            "xyAssist": 0.6,
            "thetaAssist": 0.6,
            "vibrateIntensity": 1.0
        }
    }

    property variant zoneDistances: {
        "ICE": -1,
        "MUD": -1,
        "SANDPAPER": -1,
        "STONES": -1
    }

    CelluloBluetooth{
        id: robotComm

        onConnectionStatusChanged: {
            if(connectionStatus == CelluloBluetoothEnums.ConnectionStatusConnected)
                root.setupHaptics();
        }

        Component.onCompleted: zoneEngine.addNewClient(robotComm)

        onZoneValueChanged:{
            var temp = zoneDistances;
            temp[zone.name] = value;
            zoneDistances = temp;
        }
    }

    function setupHaptics(){
        robotComm.setGestureEnabled(false);
        robotComm.setCasualBackdriveAssistEnabled(false);
    }

    function updateHaptics(){
        var xyAssistTotal = 0;
        var thetaAssistTotal = 0;
        var vibrateIntensityTotal = 0;
        var weightSum = 0;
        var logTextTotal = "";
        var temp;
        for(var zoneName in zoneDistances){
            var dist = zoneDistances[zoneName];

            //Completely inside one zone
            if(dist === 0.0){
                xyAssistTotal = zoneHaptics[zoneName].xyAssist;
                thetaAssistTotal = zoneHaptics[zoneName].thetaAssist;
                vibrateIntensityTotal = zoneHaptics[zoneName].vibrateIntensity;
                logTextTotal = zoneName + " only";
                weightSum = 0;
                break;
            }

            //Between zones
            else if(0 < dist && dist < root.mapHalfBorder*2){

                //Add this zone to haptics
                var weight = 1.0/dist;
                xyAssistTotal += weight*zoneHaptics[zoneName].xyAssist;
                thetaAssistTotal += weight*zoneHaptics[zoneName].thetaAssist;
                vibrateIntensityTotal += weight*zoneHaptics[zoneName].vibrateIntensity;
                weightSum += weight;

                //Add this zone to haptics text
                if(logTextTotal)
                    logTextTotal += " + " + zoneName;
                else
                    logTextTotal = zoneName;
            }
        }

        if(weightSum > 0){
            xyAssistTotal /= weightSum;
            thetaAssistTotal /= weightSum;
            vibrateIntensityTotal /= weightSum;
        }

        temp = currentHaptics;
        temp.xyAssist = xyAssistTotal;
        temp.thetaAssist = thetaAssistTotal;
        temp.vibrateIntensity = vibrateIntensityTotal;
        temp.logText = logTextTotal;
        currentHaptics = temp;
    }

    Timer{
        running: robotComm.connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected
        repeat: true
        interval: 100
        onTriggered: {
            updateHaptics();
            log.append(currentHaptics.logText);
            robotComm.setHapticBackdriveAssist(currentHaptics.xyAssist, currentHaptics.xyAssist, currentHaptics.thetaAssist);
            robotComm.vibrateOnMotion(currentHaptics.vibrateIntensity, 40);

            console.log(currentHaptics.xyAssist + " " + currentHaptics.thetaAssist + " " + currentHaptics.vibrateIntensity);
        }
    }

    CelluloZoneEngine{
        id: zoneEngine

        CelluloZoneRectangleDistance{
            name: "ICE"
            x: 0
            y: 0
            width: root.mapHalfWidth - root.mapHalfBorder
            height: root.mapHalfHeight - root.mapHalfBorder
        }
        CelluloZoneRectangleDistance{
            name: "MUD"
            x: root.mapHalfWidth + root.mapHalfBorder
            y: 0
            width: root.mapHalfWidth - root.mapHalfBorder
            height: root.mapHalfHeight - root.mapHalfBorder
        }
        CelluloZoneRectangleDistance{
            name: "SANDPAPER"
            x: 0
            y: root.mapHalfHeight + root.mapHalfBorder
            width: root.mapHalfWidth - root.mapHalfBorder
            height: root.mapHalfHeight - root.mapHalfBorder
        }
        CelluloZoneRectangleDistance{
            name: "STONES"
            x: root.mapHalfWidth + root.mapHalfBorder
            y: root.mapHalfHeight + root.mapHalfBorder
            width: root.mapHalfWidth - root.mapHalfBorder
            height: root.mapHalfHeight - root.mapHalfBorder
        }
    }

    Column{
        spacing: 5

        MacAddrSelector{
            addresses: [
                "00:06:66:74:40:D2",
                "00:06:66:74:40:D4",
                "00:06:66:74:40:D5",
                "00:06:66:74:40:DB",
                "00:06:66:74:40:DC",
                "00:06:66:74:40:E4",
                "00:06:66:74:40:EC",
                "00:06:66:74:40:EE",
                "00:06:66:74:41:04",
                "00:06:66:74:41:14",
                "00:06:66:74:41:4C",
                "00:06:66:74:43:00",
                "00:06:66:74:46:58",
                "00:06:66:74:46:60",
                "00:06:66:74:48:A7"
            ]
            onConnectRequested: robotComm.macAddr = selectedAddress
            onDisconnectRequested: robotComm.disconnectFromServer()
            connectionStatus: robotComm.connectionStatus
        }

        TextArea{
            id: log
            readOnly: true
        }
    }
}
