import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    Column{
        id: itemsCol

        GroupBox {
            title: "Robot Address"

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
                    "00:06:66:74:41:03",
                    "00:06:66:74:41:04",
                    "00:06:66:74:41:14",
                    "00:06:66:74:41:4C",
                    "00:06:66:74:43:00",
                    "00:06:66:74:43:01",
                    "00:06:66:74:46:58",
                    "00:06:66:74:46:60",
                    "00:06:66:74:48:A7"
                ]
                onConnectRequested: robotComm.macAddr = selectedAddress
                onDisconnectRequested: robotComm.disconnectFromServer()
                connectionStatus: robotComm.connectionStatus
            }
        }

        GroupBox {
            title: "Power"

            Button{
                text: "Reset"
                onClicked: robotComm.reset();
            }
        }

        GroupBox {
            title: "Locomotion"

            Column{
                anchors.fill: parent

                Row{
                    spacing: 15

                    Column{
                        Label{ text: "Goal velocity:" }
                        TextField{ id: goalVelX; placeholderText: "vx (mm/s)" }
                        TextField{ id: goalVelY; placeholderText: "vy (mm/s)" }
                        TextField{ id: goalW; placeholderText: "w (rad/s)" }

                        Button{
                            text: "Set"
                            onClicked: robotComm.setGoalVelocity(parseFloat(goalVelX.text), parseFloat(goalVelY.text), parseFloat(goalW.text))
                        }
                    }

                    Button{
                        text: "Clear tracking goals"
                        onClicked: robotComm.clearTracking()
                    }
                }
            }
        }

        GroupBox {
            title: "Status"
            Row{
                spacing: 5

                Text{
                    text: "Kidnapped?"
                    color: robotComm.kidnapped ? "red" : "green"
                }
                Text{
                    text: "X=" + robotComm.x.toFixed(2) + "mm Y=" + robotComm.y.toFixed(2) + "mm Theta=" + robotComm.theta.toFixed(1) + "deg"
                }
            }
        }

        GroupBox{
            title: "Profiling"

            Column{
                spacing: 5

                Row{
                    CheckBox{
                        id: timestampingCheckbox
                        text: "Get onboard timestamps"
                    }
                    CheckBox{
                        id: printCheckbox
                        text: "Print velocities"
                    }
                }

                Row{
                    Text{
                        text: "Framerate: " + robotComm.framerate.toFixed(2) + " fps"
                    }
                }

                Row{
                    Text{
                        text: "Last timestamp: " + robotComm.lastTimestamp + " ms"
                    }
                }

                Row{
                    Text{
                        text: "Pose broadcast period:"
                    }
                    TextField{
                        id: poseBcastPeriodField
                        placeholderText: "(ms)"
                    }
                    Button{
                        text: "Set"
                        onClicked: robotComm.setPoseBcastPeriod(parseFloat(poseBcastPeriodField.text))
                    }
                }
            }
        }
    }

    CelluloBluetooth{
        id: robotComm
        timestampingEnabled: timestampingCheckbox.checked

        property real lastLastTimestamp: 0
        property real lastX: 0
        property real lastY: 0
        property real lastTheta: 0

        property real vx: 0
        property real vy: 0
        property real w: 0

        onLastTimestampChanged: {
            var deltaT = lastTimestamp - lastLastTimestamp;

            if(lastLastTimestamp != 0 && deltaT > 0 && deltaT < 20){
                if(x != lastX && y != lastY && theta != lastTheta){
                    vx = 0.5*(x - lastX)/deltaT*1000 + 0.5*vx;
                    vy = 0.5*(y - lastY)/deltaT*1000 + 0.5*vy;
                    var anglediff = theta - lastTheta;
                    while(anglediff < -180)
                        anglediff += 360;
                    while(anglediff > 180)
                        anglediff -= 360;
                    w = 0.2*anglediff/deltaT*1000 + 0.8*w;
                    if(printCheckbox.checked)
                        console.log(lastTimestamp + " " + vx + " " + vy + " " + w);
                }
            }

            lastLastTimestamp = lastTimestamp;
            lastX = x;
            lastY = y;
            lastTheta = theta;
        }
    }
}
