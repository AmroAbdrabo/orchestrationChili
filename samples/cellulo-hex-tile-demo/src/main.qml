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
    minimumHeight: height
    minimumWidth: width

    GroupBox {
        id: addressBox
        title: "Robot Address"

        MacAddrSelector{
            addresses: [
                "00:06:66:74:41:1e"
            ]
            onConnectRequested: robotComm.macAddr = selectedAddress
            onDisconnectRequested: robotComm.disconnectFromServer()
            connectionStatus: robotComm.connectionStatus
        }
    }



    Rectangle{
        id: page
        anchors.top: addressBox.bottom
        anchors.left: parent.left
        anchors.margins: robotHalf

        property real scaleCoeff: Math.min((Screen.width*0.8)/210, (Screen.height*0.8 - addressBox.height)/297)
        property real robotHalf: 60*scaleCoeff/2

        width: 210*scaleCoeff
        height: 297*scaleCoeff
        color: "#EEEEEE"
        border.color: "black"
        border.width: 2
        radius: 5

        Image{
            source: robotComm.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
            rotation: robotComm.theta
            x: robotComm.x*parent.scaleCoeff - width/2
            y: robotComm.y*parent.scaleCoeff - height/2
            sourceSize.width: 75*parent.scaleCoeff
            sourceSize.height: 80*parent.scaleCoeff
        }
    }

    Item{ //Dummy item to provide margin for bottom
        anchors.top: page.bottom
        anchors.margins: page.robotHalf
    }

    Item{ //Dummy item to provide margin for right
        anchors.left: page.right
        anchors.margins: page.robotHalf
    }

    CelluloRobot{
        id: robotComm
        onConnectionStatusChanged:{
            if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                setPoseBcastPeriod(0);
        }

        onThetaChanged: console.info(theta)
    }

    OffsetRemapper{
        id: offsetTheta
        deltaTheta: 90
    }
    OffsetRemapper{
        id: offsetX
        deltaX: 10
    }
    OffsetRemapper{
        id: offsetY
        deltaY: 10
    }

    Button{
        id: thetaButton
        text: "Theta"
        anchors.top: addressBox.bottom

        onClicked: robotComm.poseRemapper = offsetTheta
    }

    Button{
        id: xButton
        text: "X"
        anchors.left: thetaButton.right

        onClicked: robotComm.poseRemapper = offsetX
    }

    Button{
        id: yButton
        text: "Y"
        anchors.left: xButton.right

        onClicked: robotComm.poseRemapper = offsetY
    }
    Button{
        id: noneButton
        text: "None"
        anchors.left: yButton.right

        onClicked: robotComm.poseRemapper = null
    }
}
