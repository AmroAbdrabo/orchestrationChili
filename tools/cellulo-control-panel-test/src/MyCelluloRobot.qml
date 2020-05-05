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
    property real  goalVelX: 50
    property real  goalVelY: 50
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
        Leds {
        }
        /*Arrow {
            id:arrow
            PropertyAnimation on rotation {
                from: 0
                to: 360
                duration: 5000
                loops: Animation.Infinite
            }

        }*/
    }

    color: "light grey" //default color

    isSimulation: true

    initPose: hex.isSelected?Qt.vector3d((hex.x+hex.width/2)* paper.width/window2.width,
                                           (hex.y+hex.height/2) * paper.height/window2.height,
                                            hex.rotation) : robotComm.init

    onZoneValueChanged: {
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
            case "INNER_ZONE0":
                if(value==1){
                console.log("in zone 0")
                crossedBorder[0]=true;
                }
                else
                crossedBorder[0]=false;
                break;
            case "INNER_ZONE1":
                if(value==1){
                console.log("in zone 1")
                crossedBorder[1]=true;
                }
                else
                crossedBorder[1]=false;
                break;


            case "INNER_ZONE2":
                if(value==1){
                console.log("in zone 2")
                crossedBorder[2]=true;
                }
                else
                crossedBorder[2]=false;
                break;
            case "INNER_ZONE3":
                if(value==1){
                console.log("in zone 3")
                crossedBorder[3]=true;
                }
                else
                crossedBorder[3]=false;
                break;
            case "INNER_ZONE4":
                if(value==1){
                console.log("in zone 4")
                crossedBorder[4]=true;
                }
                else
                crossedBorder[4]=false;
                break;
            case "INNER_ZONE5":
                if(value==1){
                console.log("in zone 5")
                crossedBorder[5]=true;
                }
                else
                crossedBorder[5]=false;
                break;
            case "INNER_ZONE6":
            if(value==1){
                console.log("in zone 6")
                crossedBorder[6]=true;
                }
                else
                crossedBorder[6]=false;
                break;
            case "INNER_ZONE7":
            if(value==1){
                console.log("in zone 7")
                crossedBorder[7]=true;
                }
                else
                crossedBorder[7]=false;
                break;
            case "INNER_ZONE8":
                if(value==1){
                console.log("in zone 8")
                crossedBorder[8]=true;
                }
                else
                crossedBorder[8]=false;
                break;
            case "INNER_ZONE9":
                if(value==1){
                console.log("in zone 9")
                crossedBorder[9]=true;
                }
                else
                crossedBorder[9]=false;
                break;
            case "INNER_ZONE10":
                if(value==1){
                console.log("in zone 10")
                crossedBorder[10]=true;
                }
                else
                crossedBorder[10]=false;
                break;
            case "INNER_ZONE11":
            if(value==1){
                console.log("in zone 11")
                crossedBorder[11]=true;
                }
                else
                crossedBorder[11]=false;
                break;
            case "INNER_ZONE12":
                if(value==1){
                console.log("in zone 12")
                crossedBorder[12]=true;
                }
                else
                crossedBorder[12]=false;
                break;
            case "INNER_ZONE13":
                if(value==1){
                console.log("in zone13")
                crossedBorder[13]=true;
                }
                else
                crossedBorder[13]=false;
                break;
            case "INNER_ZONE14":
                if(value==1){
                console.log("in zone14")
                crossedBorder[14]=true;
                }
                else
                crossedBorder[14]=false;
                break;
            case "INNER_ZONE15":
                if(value==1){
                console.log("in zone15")
                crossedBorder[15]=true;
                }
                else
                crossedBorder[15]=false;
                break;
            case "INNER_ZONE16":
                if(value==1){
                console.log("in zone 16")
                crossedBorder[16]=true;
                }
                else
                crossedBorder[16]=false;
                break;
            case "INNER_ZONE17":
                if(value==1){
                console.log("in zone 17")
                crossedBorder[17]=true;
                }
                else
                crossedBorder[17]=false;
            break;
            case "INNER_ZONE18":
                if(value==1){
                console.log("in zone 18")
                crossedBorder[18]=true;
                }
                else
                crossedBorder[18]=false;
                break;
            case "INNER_ZONE19":
                if(value==1){
                console.log("in zone 19")
                crossedBorder[19]=true;
                }
                else
                crossedBorder[19]=false;
                break;
            case "INNER_ZONE20":
                if(value==1){
                console.log("in zone 20")
                crossedBorder[20]=true;
                }
                else
                crossedBorder[20]=false;
                break;
            case "INNER_ZONE21":
                if(value==1){
                console.log("in zone 21")
                crossedBorder[21]=true;
                }
                else
                crossedBorder[21]=false;
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
