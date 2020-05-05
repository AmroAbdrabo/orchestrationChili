import QtQuick 2.0

Item {
    PathView {
        id: leds
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        model: ListModel {
            ListElement { name: "led0" }
            ListElement { name: "led1" }
            ListElement { name: "led2" }
            ListElement { name: "led3" }
            ListElement { name: "led4" }
            ListElement { name: "led5" }
        }
        //use Rectangle to make circles
        delegate: Rectangle {
            id: led
            width: 11
            height: 11
            radius: 5
            //can do color: robotCommLedColors[index] or if(index == 0) robotComm.led1 ect... but that might a be a little
            //so would be good if can figure out way to have an array as qproperty
            //could also just use a javascript function here a
            //leds could repr as array in logic and display 1 b1 1 as qproperties
            color:  if(index == 0)robotComm.led0Color;
                    else if(index == 1) robotComm.led1Color;
                    else if(index == 2) robotComm.led2Color;
                    else if(index == 3) robotComm.led3Color;
                    else if(index == 4) robotComm.led4Color;
                    else if(index == 5) robotComm.led5Color;
        }
        path: Path {
            startX: hex.width/2
            startY: hex.height/2 - hex.height/4
            PathArc { x: hex.width/2; y: hex.height/2+hex.height/4;
                      radiusX: hex.width/4; radiusY: hex.height/4; useLargeArc: true }
            PathArc { x: hex.width/2; y: hex.height/2-hex.height/4;
                      radiusX: hex.width/4; radiusY: hex.height/4; useLargeArc: true }
        }
    }
}

