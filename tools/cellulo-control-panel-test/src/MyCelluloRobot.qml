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

CelluloRobot{
    id:robotComm
    property var init: Qt.vector3d(0,0,0)
    color: "blue" //default color

    Hexagon{
        id: hex
        property  real wheelRotation: 0
        property real curRobotRotation: 0 //to avoid binding loop on rotation
        width: 75 * window2.width/paper.width;
        height: 75 * Math.sin(60*Math.PI/180) * window2.height/paper.height;//the height of a perfect hexagon depends on its width
        transformOrigin: Item.Center
        color: robotComm.color
        property bool isSelected: false
        x: isSelected?hex.x:(robotComm.x * window2.width / paper.width) - hex.width/2
        y: isSelected?hex.y:(robotComm.y * window2.height / paper.height) - hex.height/2
        rotation: isSelected? curRobotRotation + wheelRotation : robotComm.theta ;

        MouseArea {
            id: themouse1
            anchors.fill: parent
            drag.target: parent
            onClicked: {
                //reset curRobotRotation and wheelRotation
                parent.curRobotRotation = robotComm.theta
                parent.wheelRotation = 0
                robotComm.init=Qt.vector3d(robotComm.x,robotComm.y,robotComm.theta)
                parent.isSelected=!parent.isSelected
                console.log(parent.isSelected)
            }
            onWheel: {
                if(parent.isSelected){
                    parent.wheelRotation += wheel.angleDelta.y/16;
                    parent.wheelRotation = parent.wheelRotation > 360 ?
                                parent.wheelRotation-360: parent.wheelRotation
                }
            }
        }

    }
    isSimulation: true

    initPose: hex.isSelected?Qt.vector3d((hex.x+hex.width/2)* paper.width/window2.width,
                                           (hex.y+hex.height/2) * paper.height/window2.height,
                                            hex.rotation) : robotComm.init

    onZoneValueChanged: {
        //index is 0 since it works only for checking the first robot
        //if(index==0){
        switch(zone.name){
            case "fruit1":
                if(value==1){
                    console.log("on fruit 1")
                }
                break;
            case "fruit2":
                if(value==1){
                console.log("on fruit 2")
            }
                break;
            case "fruit3":
                if(value==1){
                 console.log("on fruit 3")
                }
                break;
            case "fruit4":
                if(value==1){
                    console.log("on fruit 4")
                }
                break;
            case "fruit5":
                if(value==1){
                 console.log("on fruit 5")
                }
                break;
            case "fruit6":
                if(value==1){
                 console.log("on fruit 6")
                }
                break;
            default:
                 break;

        }

    }
    onTouchBegan:{
        switch(key){
        case 0: k0.color = "yellow"; break;
        case 1: k1.color = "yellow"; break;
        case 2: k2.color = "yellow"; break;
        case 3: k3.color = "yellow"; break;
        case 4: k4.color = "yellow"; break;
        case 5: k5.color = "yellow"; break;
        }
    }
    onLongTouch:{
        switch(key){
        case 0: k0.color = "green"; break;
        case 1: k1.color = "green"; break;
        case 2: k2.color = "green"; break;
        case 3: k3.color = "green"; break;
        case 4: k4.color = "green"; break;
        case 5: k5.color = "green"; break;
        }
    }
    onTouchReleased:{
        switch(key){
        case 0: k0.color = "black"; break;
        case 1: k1.color = "black"; break;
        case 2: k2.color = "black"; break;
        case 3: k3.color = "black"; break;
        case 4: k4.color = "black"; break;
        case 5: k5.color = "black"; break;
        }
    }
    onFrameReady: cameraImage.reload()

    onTrackingGoalReached: toast.show("Tracking goal reached.")
    onBootCompleted: toast.show("Boot completed.")
    onShuttingDown: toast.show("Shutting down.")
    onLowBattery: toast.show("Low battery.")
}
