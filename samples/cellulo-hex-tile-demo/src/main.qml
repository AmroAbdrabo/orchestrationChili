import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.2
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: height
    minimumWidth: width

    GroupBox {
        id: addressBox
        title: "Robot Address"

        Column{

            MacAddrSelector{
                addresses: [
                    "00:06:66:d2:cf:7a"
                ]
                onConnectRequested: robotComm1.macAddr = selectedAddress
                onDisconnectRequested: robotComm1.disconnectFromServer()
                connectionStatus: robotComm1.connectionStatus
            }

            MacAddrSelector{
                addresses: [
                    "00:06:66:74:40:DB"
                ]
                onConnectRequested: robotComm2.macAddr = selectedAddress
                onDisconnectRequested: robotComm2.disconnectFromServer()
                connectionStatus: robotComm2.connectionStatus
            }

            Slider{
                id: slider
                width: 100
                value: 1.0

                visible: true

                //onValueChanged: hexMap.physicalArea = Qt.rect(-200*slider.value, -200*slider.value, 400*slider.value, 400*slider.value)
            }

            Row{
                Button{
                    text: "Clear"
                    onClicked: hexMap.clearTiles()
                }

                Button{
                    text: "Save Map"
                    onClicked: dumpDialog.open()
                }

                Button{
                    text: "Load Map"
                    onClicked: loadDialog.open()
                }
            }
        }
    }

    Rectangle{
        id: page
        anchors.top: addressBox.bottom
        anchors.left: parent.left
        anchors.margins: 50

        property real rectSize: Math.min((Screen.width*0.8), (Screen.height*0.8 - addressBox.height))

        width: rectSize
        height: rectSize
        color: "#EEEEEE"
        border.color: "black"
        border.width: 2
        radius: 5

        HexTileMap{
            id: hexMap

            property real scale: Math.min(parent.width/physicalSize.x, parent.height/physicalSize.y)

            width:  scale*physicalSize.x
            height: scale*physicalSize.y

            //x: slider.value*100
            //y: slider.value*100
            //physicalSize: Qt.vector2d(400, 400)
            //physicalTopLeft: Qt.vector2d(-200, -200)

            autoResize: true
            autoBuild: true

            onTileAdded: console.info("Tile added at " + newTile.coords.q + " " + newTile.coords.r)
            onTileRemoved: console.info("Tile removed from " + oldTileQ + " " + oldTileR)

            /*HexTileWithCoords{
                id: centerTile
                standardCoords: HexTileStandardCoords{ i:7; j:9; u:0; v:0 }
                coords.q: 0; coords.r: 0
            }*/
/*
            HexTileWithCoords{
                id: leftTile
                standardCoords: HexTileStandardCoords{ i:2; j:3; u:0; v:1 }
                coords.q: -1; coords.r: 0
            }

            HexTileWithCoords{
                id: rightTile
                standardCoords: HexTileStandardCoords{ i:2; j:3; u:1; v:1 }
                coords.q: 1; coords.r: 0
            }

            HexTileWithCoords{
                id: topLeftTile
                standardCoords: HexTileStandardCoords{ i:2; j:3; u:0; v:0 }
                coords.q: 0; coords.r: -1
            }

            HexTileWithCoords{
                id: topRightTile
                standardCoords: HexTileStandardCoords{ i:7; j:9; u:1; v:1 }
                coords.q: 1; coords.r: -1
            }

            HexTileWithCoords{
                id: bottomLeftTile
                standardCoords: HexTileStandardCoords{ i:7; j:9; u:1; v:0 }
                coords.q: -1; coords.r: 1
            }

            HexTileWithCoords{
                id: bottomRightTile
                standardCoords: HexTileStandardCoords{ i:2; j:3; u:1; v:0 }
                coords.q: 0; coords.r: 1
            }
            */

            Image{
                property vector2d screenSize: parent.toScreenSize.convert(Qt.vector2d(75, 75*2/Math.sqrt(3)))
                property vector2d screenCoords: parent.toScreenCoords.convert(Qt.vector2d(robotComm1.x, robotComm1.y))

                source: robotComm1.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
                rotation: robotComm1.theta
                width: screenSize.x
                height: screenSize.y
                sourceSize.width: screenSize.x
                sourceSize.height: screenSize.y
                x: screenCoords.x - width/2
                y: screenCoords.y - height/2
                visible: true
            }

            Image{
                property vector2d screenSize: parent.toScreenSize.convert(Qt.vector2d(75, 75*2/Math.sqrt(3)))
                property vector2d screenCoords: parent.toScreenCoords.convert(Qt.vector2d(robotComm2.x, robotComm2.y))

                source: robotComm2.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
                rotation: robotComm2.theta
                width: screenSize.x
                height: screenSize.y
                sourceSize.width: screenSize.x
                sourceSize.height: screenSize.y
                x: screenCoords.x - width/2
                y: screenCoords.y - height/2
                visible: true
            }

            /*Image{
                property vector2d screenSize: parent.toScreenSize.convert(Qt.vector2d(30, 30*2/Math.sqrt(3)))
                property vector2d screenCoords: parent.toScreenCoords.convert(Qt.vector2d(robotComm.goal.x, robotComm.goal.y))

                source: "../assets/redHexagon.svg"
                width: screenSize.x
                height: screenSize.y
                sourceSize.width: screenSize.x
                sourceSize.height: screenSize.y
                x: screenCoords.x - width/2
                y: screenCoords.y - height/2
                visible: true
            }*/
        }
    }

    Item{ //Dummy item to provide margin for bottom
        anchors.top: page.bottom
        anchors.margins: 50
    }

    Item{ //Dummy item to provide margin for right
        anchors.left: page.right
        anchors.margins: 50
    }

    CelluloBluetooth{
        property int currentGoal: 0

        property var goals: []//centerTile.hexOffset(), topLeftTile.hexOffset(), topRightTile.hexOffset(), rightTile.hexOffset(), bottomRightTile.hexOffset(), bottomLeftTile.hexOffset(), leftTile.hexOffset()]
        property vector2d goal: Qt.vector2d(0,0)

        //poseVelControlEnabled: true

        id: robotComm1
        onConnectionStatusChanged:{
            if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                setPoseBcastPeriod(100);
        }
        poseRemapper: hexMap

        onPoseChanged: {
            return;
            goal = goals[currentGoal];
            var goalVel = goal.minus(Qt.vector2d(x,y)).times(2.0);
            if(goalVel.length() > 100){
                goalVel = goalVel.normalized().times(100);
            }
            var goalW = 30 - theta;
            if(goalW < -180)
                goalW += 360;
            if(goalW > 180)
                goalW -= 360;
            setGoalVelocity(goalVel.x, goalVel.y, 0.1*goalW);
            if(goal.minus(Qt.vector2d(x,y)).length() < 10)
                currentGoal = (currentGoal + 1) % 7;
        }
    }

    CelluloBluetooth{
        id: robotComm2
        onConnectionStatusChanged:{
            if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                setPoseBcastPeriod(100);
        }
        poseRemapper: hexMap
    }

    FileDialog{
        id: dumpDialog
        title: "Choose a new file to save map to"
        folder: shortcuts.desktop
        selectExisting: false
        selectMultiple: false
        nameFilters: ["*.json"]
        onAccepted: {
            var filename = fileUrl.toString();
            if(!filename.endsWith(".json"))
                filename += ".json";
            hexMap.dumpTilesToJSON(filename);
        }
    }

    FileDialog{
        id: loadDialog
        title: "Choose a map description to load"
        folder: shortcuts.desktop
        selectExisting: true
        selectMultiple: false
        nameFilters: ["*.json"]
        onAccepted: hexMap.loadTilesFromJSON(fileUrl)
    }
}
