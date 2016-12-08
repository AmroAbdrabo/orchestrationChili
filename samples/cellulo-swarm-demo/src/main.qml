import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtBluetooth 5.2

import QMLCache 1.0
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: 100
    minimumWidth: 200

    readonly property int numRobots: 15
    property int currentNumRobots: 0

    function recalcNumRobots(){
        var ret = 0;
        for(var i=0;i<robots.length;i++)
            if(robots[i].connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                ret++;
        currentNumRobots = ret;
    }

    property int nearestSquareEdge: Math.ceil(Math.sqrt(currentNumRobots))

    property var robots: []

    property real bcastPeriod: 100
    property real bcastPeriodMin: 50
    property real bcastPeriodMax: 200
    property real vMu: 0

    Repeater{
        model: numRobots

        CelluloBluetooth{
            id: robot

            macAddr: QMLCache.read("robot" + index + "MacAddr")
            localAdapterMacAddr: QMLCache.read("robot" + index + "LocalAdapterMacAddr")

            function init(){
                setPoseBcastPeriod(bcastPeriod);
                setTimestampingEnabled(true);
                setCasualBackdriveAssistEnabled(false);
                clearHapticFeedback();
                clearTracking();
                setExposureTime(0);
                setGestureEnabled(false);
                setLocomotionInteractivityMode(CelluloBluetoothEnums.LocomotionInteractivityModeNormal);
                setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll,"#202020",0);
                setLEDResponseMode(CelluloBluetoothEnums.LEDResponseModeResponsiveIndividual);
                keys = [false, false, false, false, false, false];
            }

            onBootCompleted: init()

            onConnectionStatusChanged: {
                if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected)
                    init();

                recalcNumRobots();
            }

            onTouchBegan: {
                keys[key] = true;
                recalcTouchedRobots();
            }

            onTouchReleased: {
                keys[key] = false;
                recalcTouchedRobots();
            }

            property var keys: [false, false, false, false, false, false]

            function anyKey(){
                for(var i=0;i<6;i++)
                    if(keys[i])
                        return true;
                return false;
            }

            property vector3d vxyw: Qt.vector3d(0,0,0)

            readonly property real maxXYVel: 1000//500
            readonly property real maxW: 50//25

            property bool needsReset: true
            property vector3d lastXYTheta: Qt.vector3d(0,0,0)
            property real lastTime: 0

            onKidnappedChanged: needsReset = true

            function calcVel(){
                var newTime = lastTimestamp;
                var deltaTime = newTime - lastTime;
                var newXYTheta = Qt.vector3d(x,y,theta);

                var newVxyw = newXYTheta.minus(lastXYTheta);
                while(newVxyw.z <= -180)
                    newVxyw.z += 360;
                while(newVxyw.z > 180)
                    newVxyw.z -= 360;
                newVxyw.z = newVxyw.z*Math.PI/180;

                newVxyw = newVxyw.times(1000/deltaTime);
                if(bcastPeriodMin < deltaTime && deltaTime < bcastPeriodMax){
                    if(needsReset){
                        vxyw = newVxyw;
                        needsReset = false;
                    }
                    else{
                        vxyw = vxyw.times(vMu).plus(newVxyw.times(1 - vMu));
                    }
                }
                else if(bcastPeriodMax <= deltaTime){
                    needsReset = true;
                    vxyw = newVxyw;
                }
                else
                    needsReset = true;

                if(vxyw.x > maxXYVel)
                    vxyw.x = maxXYVel;
                else if(vxyw.x < -maxXYVel)
                    vxyw.x = -maxXYVel;
                if(vxyw.y > maxXYVel)
                    vxyw.y = maxXYVel;
                else if(vxyw.y < -maxXYVel)
                    vxyw.y = -maxXYVel;
                if(vxyw.z > maxW)
                    vxyw.z = maxW;
                else if(vxyw.z < -maxW)
                    vxyw.z = -maxW;

                lastXYTheta = newXYTheta;
                lastTime = newTime;
            }

            property vector3d goalXYTheta: Qt.vector3d(0,0,0);

            /*property vector3d goalVxyw: Qt.vector3d(0,0,0);

            readonly property real trajEdge: 200
            readonly property real trajDuration: 16000
            readonly property real trajEdgeDuration: trajDuration/4
            readonly property real trajLinearVel: trajEdge/trajEdgeDuration*1000
            readonly property vector2d trajCorner: Qt.vector2d(600, 300);

            function calcTrajGoal(){
                var time = (new Date()).getTime() % trajDuration;
                var trajProgress = 0;

                if(time < trajEdgeDuration){
                    trajProgress = time/trajEdgeDuration;
                    goalXYTheta = Qt.vector3d(trajCorner.x + trajEdge*trajProgress, trajCorner.y, 0);
                    goalVxyw = Qt.vector3d(trajLinearVel, 0, 0);
                }
                else if(time < 2*trajEdgeDuration){
                    time -= trajEdgeDuration;
                    trajProgress = time/trajEdgeDuration;
                    goalXYTheta = Qt.vector3d(trajCorner.x + trajEdge, trajCorner.y + trajEdge*trajProgress, 0);
                    goalVxyw = Qt.vector3d(0, trajLinearVel, 0);
                }
                else if(time < 3*trajEdgeDuration){
                    time -= 2*trajEdgeDuration;
                    trajProgress = time/trajEdgeDuration;
                    goalXYTheta = Qt.vector3d(trajCorner.x + trajEdge - trajEdge*trajProgress, trajCorner.y + trajEdge, 0);
                    goalVxyw = Qt.vector3d(-trajLinearVel, 0, 0);
                }
                else{
                    time -= 3*trajEdgeDuration;
                    trajProgress = time/trajEdgeDuration;
                    goalXYTheta = Qt.vector3d(trajCorner.x, trajCorner.y + trajEdge - trajEdge*trajProgress, 0);
                    goalVxyw = Qt.vector3d(0, -trajLinearVel, 0);
                }
            }*/

            function calcLatticeGoal(){
                var myX = index % nearestSquareEdge;
                var myY = (index - myX)/nearestSquareEdge;
                var myVec = Qt.vector2d(myX*latticeDist, myY*latticeDist);

                var rotRad = latticePose.z*Math.PI/180;
                var rotMat = [
                            [Math.cos(rotRad), -Math.sin(rotRad)],
                            [Math.sin(rotRad), Math.cos(rotRad)]
                        ];

                myVec = Qt.vector2d(rotMat[0][0]*myVec.x + rotMat[0][1]*myVec.y, rotMat[1][0]*myVec.x + rotMat[1][1]*myVec.y);

                goalXYTheta = Qt.vector3d(latticePose.x + myVec.x, latticePose.y + myVec.y, latticePose.z);
            }

            /*readonly property vector3d kGoalVelXYW: Qt.vector3d(0.9,0.9,0.9)
            readonly property vector3d kCommandXYTheta: Qt.vector3d(2,2,0.1)
            readonly property vector3d kCommandVxyw: Qt.vector3d(0.2,0.2,0.2)

            function calcCommandWithVel(){
                var xythetaDiff = goalXYTheta.minus(Qt.vector3d(x,y,theta));
                while(xythetaDiff.z > 180)
                    xythetaDiff.z -= 360;
                while(xythetaDiff.z <= -180)
                    xythetaDiff.z += 360;
                var Pxytheta = xythetaDiff.times(kCommandXYTheta);
                var VxywDiff = goalVxyw.minus(vxyw);
                var PVxyw = VxywDiff.times(kCommandVxyw);

                commandVxyw = goalVxyw.times(kGoalVelXYW);
                commandVxyw = commandVxyw.plus(Pxytheta);
                commandVxyw = commandVxyw.plus(PVxyw);

                if(commandVxyw.x > 200)
                    commandVxyw.x = 200;
                else if(commandVxyw.x < -200)
                    commandVxyw.x = -200;
                if(commandVxyw.y > 200)
                    commandVxyw.y = 200;
                else if(commandVxyw.y < -200)
                    commandVxyw.y = -200;
                if(commandVxyw.z > 10)
                    commandVxyw.z = 10;
                else if(commandVxyw.z < -10)
                    commandVxyw.z = -10;
            }*/

            property vector3d commandVxyw: Qt.vector3d(0,0,0)

            readonly property vector3d kPCommandWithoutVelXYTheta: Qt.vector3d(2.5, 2.5, 0.05)
            readonly property vector3d kDCommandWithoutVelXYTheta: Qt.vector3d(0.3, 0.3, 0.2)

            function calcCommandWithoutVel(){
                var xythetaDiff = goalXYTheta.minus(Qt.vector3d(x,y,theta));
                while(xythetaDiff.z > 180)
                    xythetaDiff.z -= 360;
                while(xythetaDiff.z <= -180)
                    xythetaDiff.z += 360;
                var Pxytheta = xythetaDiff.times(kPCommandWithoutVelXYTheta);
                var Dxytheta = vxyw.times(-1).times(kDCommandWithoutVelXYTheta);

                if(go.checked){
                    commandVxyw = Pxytheta.plus(Dxytheta);

                    if(commandVxyw.x > 200)
                        commandVxyw.x = 200;
                    else if(commandVxyw.x < -200)
                        commandVxyw.x = -200;
                    if(commandVxyw.y > 200)
                        commandVxyw.y = 200;
                    else if(commandVxyw.y < -200)
                        commandVxyw.y = -200;
                    if(commandVxyw.z > 10)
                        commandVxyw.z = 10;
                    else if(commandVxyw.z < -10)
                        commandVxyw.z = -10;
                }
                else
                    commandVxyw = Qt.vector3d(0,0,0);
            }

            function calcUserInput(){
                if(touchedRobot1 === robot){

                    //Resize and rotate lattice according to the first and second held robot
                    if(touchedRobot2 !== null)
                        recalcResize();

                    //Rotate according to the first held robot
                    else
                        latticePose.z = theta;

                    //Move lattice according to the first held robot
                    var myX = index % nearestSquareEdge;
                    var myY = (index - myX)/nearestSquareEdge;

                    var latticeCornerPos = Qt.vector2d(-myX*latticeDist, -myY*latticeDist);
                    var rotRad = latticePose.z*Math.PI/180;
                    var rotMat = [
                                [Math.cos(rotRad), -Math.sin(rotRad)],
                                [Math.sin(rotRad), Math.cos(rotRad)]
                            ];
                    latticeCornerPos = Qt.vector2d(
                                rotMat[0][0]*latticeCornerPos.x + rotMat[0][1]*latticeCornerPos.y,
                                rotMat[1][0]*latticeCornerPos.x + rotMat[1][1]*latticeCornerPos.y
                                );

                    latticePose.x = x + latticeCornerPos.x;
                    latticePose.y = y + latticeCornerPos.y;
                }
            }

            onPoseChanged: {
                calcVel();

                calcUserInput();

                //calcTrajGoal();
                calcLatticeGoal();

                //calcCommandWithVel();
                calcCommandWithoutVel();

                setGoalVelocity(commandVxyw.x, commandVxyw.y, commandVxyw.z);
            }
        }

        onItemAdded: {
            var temp = robots;
            temp.push(item);
            robots = temp;
        }
    }

    property vector3d latticePose: Qt.vector3d(200, 500, 0)
    property real latticeDist: 80
    property var touchedRobot1: null
    property var touchedRobot2: null
    property int touchedRobot1Index: -1
    property int touchedRobot2Index: -1

    function initTouched(robot){
        robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#202000", 0);
        robot.setHapticBackdriveAssist(0.7, 0.7, 0.7);
    }

    function initReleased(robot){
        robot.setVisualEffect(CelluloBluetoothEnums.VisualEffectConstAll, "#202020", 0);
        robot.setHapticBackdriveAssist(0,0,0);
    }

    function recalcTouchedRobots(){
        touchedRobot1 = null;
        touchedRobot2 = null;

        for(var i=0;i<robots.length;i++)
            if(robots[i].anyKey()){
                if(touchedRobot1 === null){
                    touchedRobot1 = robots[i];
                    touchedRobot1Index = i;
                    initTouched(touchedRobot1);
                }
                else{
                    touchedRobot2 = robots[i];
                    touchedRobot2Index = i;
                    initTouched(touchedRobot2);
                    break;
                }
            }
            else
                initReleased(robots[i]);
    }

    function recalcResize(){
        var r1X = touchedRobot1Index % nearestSquareEdge;
        var r1Y = (touchedRobot1Index - r1X)/nearestSquareEdge;
        var r2X = touchedRobot2Index % nearestSquareEdge;
        var r2Y = (touchedRobot2Index - r2X)/nearestSquareEdge;
        var unitXDiff = r2X - r1X;
        var unitYDiff = r2Y - r1Y;
        var originalLatticeAngle = Math.atan2(unitYDiff, unitXDiff);
        var unitDistance = Math.sqrt(unitXDiff*unitXDiff + unitYDiff*unitYDiff);

        var yDiff = touchedRobot2.y - touchedRobot1.y;
        var xDiff = touchedRobot2.x - touchedRobot1.x;
        var angle = Math.atan2(yDiff, xDiff) - originalLatticeAngle;
        latticePose.z = angle/Math.PI*180;

        latticeDist = Math.sqrt(xDiff*xDiff + yDiff*yDiff)/unitDistance;
    }

    //Visible items

    GroupBox {
        id: addressBox
        title: "Robots"

        Column{
            property variant addresses: [
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

            Repeater{
                model: numRobots

                MacAddrSelector{
                    addresses: parent.addresses
                    onConnectRequested: {
                        robots[index].localAdapterMacAddr = selectedLocalAdapterAddress;
                        robots[index].macAddr = selectedAddress;
                        QMLCache.write("robot" + index + "LocalAdapterMacAddr", selectedLocalAdapterAddress);
                        QMLCache.write("robot" + index + "MacAddr", selectedAddress);
                    }
                    onDisconnectRequested: {
                        robots[index].disconnectFromServer();
                        QMLCache.write("robot" + index + "MacAddr", "");
                    }
                    connectionStatus: robots[index].connectionStatus

                    Component.onCompleted: {
                        selectAddress(QMLCache.read("robot" + index + "MacAddr"));
                        selectLocalAdapterAddress(QMLCache.read("robot" + index + "LocalAdapterMacAddr"));
                    }
                }
            }

            CheckBox{
                id: go
                text: "Go!"
                checked: false
            }
        }
    }

    GroupBox{
        id: playgroundBox
        title: "Playground"
        anchors.top: addressBox.bottom

        Item{
            width: page.width + page.physicalRobotWidth*page.scaleCoeff
            height: page.height + page.physicalRobotWidth*page.scaleCoeff

            Rectangle{
                id: page

                anchors.centerIn: parent

                property real physicalWidth: 841        ///< Physical paper width in mm
                property real physicalHeight: 841       ///< Physical paper height in mm
                property real physicalRobotWidth: 75    ///< Physical robot width in mm

                width: height*physicalWidth/physicalHeight
                height: Screen.height/3

                property real scaleCoeff: width/physicalWidth

                color: "#EEEEEE"
                border.color: "black"
                border.width: 2
                radius: 5

                Repeater{
                    model: numRobots

                    Image{
                        visible: robots[index].connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected
                        source: robots[index].kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg"
                        rotation: robots[index].theta
                        x: robots[index].x*parent.scaleCoeff - width/2
                        y: robots[index].y*parent.scaleCoeff - height/2
                        width: parent.physicalRobotWidth*parent.scaleCoeff
                        fillMode: Image.PreserveAspectFit
                    }
                }

                Repeater{
                    model: numRobots

                    Image{
                        visible: robots[index].connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected
                        source: "../assets/yellowHexagon.svg"
                        rotation: robots[index].goalXYTheta.z
                        x: robots[index].goalXYTheta.x*parent.scaleCoeff - width/2
                        y: robots[index].goalXYTheta.y*parent.scaleCoeff - height/2
                        width: parent.physicalRobotWidth*parent.scaleCoeff
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
