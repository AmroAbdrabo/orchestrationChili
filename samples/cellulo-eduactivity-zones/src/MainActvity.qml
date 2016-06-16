import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.1
import Cellulo 1.0
import "cellulo-zonesdrawer-educational-activity.js" as EducationalActivityDrawer

Item {
    id: base
    property var window: ({})
    property var playgroundBorderMargin: 0
    property var gridSpacing: 0.508

    //list of robot used by this activity
    property var robotsList: [robot0, robot1, robot2]
    //heat zones used by this activity
    property var circularHeatZones: []

    //speed information used by this activity
    property real maxSpeed: 90
    property real minSpeed: 30
    property real sigma: 170

    property var isInActivity1: true

    //color code used by this activity
    //taken from http://www.colorhexa.com/0000ff-to-ff0000
    property var gradientBlueToRed: ["#0000ff", "#1500ea", "#2b00d4", "#4000bf", "#5500aa", "#6a0095", "#800080", "#95006a", "#aa0055", "#bf0040", "#d4002b", "#ea0015", "#ff0000"]
    property var diffSpeedInterval: (maxSpeed-minSpeed)/(gradientBlueToRed.length-1)
    property var gradientSpeed: []

    Row{
        id: robotConnect
        anchors.right: page.right
        Column{
            Row{
                spacing: 5

                Label{
                    text: "00:06:66:74:"
                    anchors.verticalCenter: macAddrRight0.verticalCenter
                }
                TextField{
                    id: macAddrRight0
                    text: "40:DC"
                    placeholderText: "XX:XX"
                }
                Button {
                    text: "Connect"
                    onClicked: {
                        robot0.macAddr =  "00:06:66:74:" + macAddrRight0.text;
                        page.focus = true
                    }
                }
                Text{
                    text: "Connected?"
                    color: robot0.connected ? "green" : "red"
                }
            }
            Row{
                spacing: 5

                Label{
                    text: "00:06:66:74:"
                    anchors.verticalCenter: macAddrRight1.verticalCenter
                }
                TextField{
                    id: macAddrRight1
                    text: "40:D4"
                    placeholderText: "XX:XX"
                }
                Button {
                    text: "Connect"
                    onClicked: {
                        robot1.macAddr =  "00:06:66:74:" + macAddrRight1.text;
                        page.focus = true
                    }
                }
                Text{
                    text: "Connected?"
                    color: robot1.connected ? "green" : "red"
                }
            }
            Row{
                spacing: 5

                Label{
                    text: "00:06:66:74:"
                    anchors.verticalCenter: macAddrRight2.verticalCenter
                }
                TextField{
                    id: macAddrRight2
                    text: "48:A7"
                    placeholderText: "XX:XX"
                }
                Button {
                    text: "Connect"
                    onClicked: {
                        robot2.macAddr =  "00:06:66:74:" + macAddrRight2.text;
                        page.focus = true
                    }
                }
                Text{
                    text: "Connected?"
                    color: robot2.connected ? "green" : "red"
                }
            }
        }

        Column{
            Button {
                text: "Show debug"
                property var show: true
                onClicked: {
                    if(show){
                        show = false
                        text = "Show debug"
                        debugView.visible = true
                    } else {
                        show = true
                        text = "Hide debug"
                        debugView.visible = false
                    }
                }
            }
            Button {
                text: "Reset"
                property bool reset: true
                onClicked: {
                    if(reset){
                        text = "Restart"
                        gameLogic.resetAction()
                        gameLogic.locomotionTimer.stop()
                        reset = false
                    } else {
                        text = "Reset"
                        gameLogic.locomotionTimer.restart()
                        reset = true
                    }
                }
            }

        }



    }

    Button{
        id: buttonChangeActivity
        anchors.left: page.right
        anchors.top: userinfo.bottom
        anchors.topMargin: 40
        anchors.leftMargin: 40
        signal changeTypeOfActivity(var type, var value)
        text: "Click here to go to the other activity"
        onClicked: {
            isInActivity1 = !isInActivity1
            buttonChangeActivity.changeTypeOfActivity("TOUCHBUTTONCHANGEACTIVITY", isInActivity1)
        }
    }

    Text {
        id: userinfo
        anchors.left: page.right
        anchors.leftMargin: 40
        anchors.verticalCenter: page.verticalCenter
        text: isInActivity1? "activity1 playing": "activity2 playing"
        font.pixelSize: 35
        color: "black"
    }


    Rectangle{
        id: page
        focus: true
        color: "black"
        border.color: "black"
        border.width: 2
        radius: 5
        width: scaleCoeff*zoneE.realPlaygroundWidth
        height: scaleCoeff*zoneE.realPlaygroundHeight
        anchors.left: parent.left
        anchors.top: robotConnect.bottom
        anchors.margins: robotHalf
        property real robotHalf: robotDiagonal*scaleCoeff/2
        //property real scaleCoeff: Math.min((Screen.width*0.8)/zoneE.realPlaygroundWidth, (Screen.height*0.8)/zoneE.realPlaygroundHeight)
        property real scaleCoeff: 0.87
        property real robotDiagonal: 80
        property real robotSideToSide: 75

        Keys.onEscapePressed: {
            window.close();
        }
    }


    CelluloBluetooth{
        id: robot0
        property var locomotionCalculator: locomotionCalculatorRobot0
        property var speedCalculator: speedCalculatorRobot0
        property var collisionBorder: collisionBorder0
        signal zoneValueUpdated(var type, int value, var robot, var zone)
        signal robotBehaviourUpdated(var type, int value, var robot)
        property bool isMoving: false

        onZonesChangesHandlerChanged: {
            var zoneConcerned = zonesChangesHandler[0]
            var value = zonesChangesHandler[1]
            var robot = robot0
            switch(zoneConcerned.type){
            case CelluloZoneTypes.CIRCLEINNER:
                debugView.valueCInner = value
                zoneValueUpdated("CIRCLEINNER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.CIRCLEBORDER:
                debugView.valueCBorder = value
                zoneValueUpdated("CIRCLEBORDER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.CIRCLEDISTANCE:
                zoneValueUpdated("CIRCLEDISTANCE", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.RECTANGLEINNER:
                debugView.valueRInner = value
                zoneValueUpdated("RECTANGLEINNER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.RECTANGLEBORDER:
                debugView.valueRBorder = value
                zoneValueUpdated("RECTANGLEBORDER", value, robot, zoneConcerned)
                break;
            default:
                console.log("UNKNOW IN " + zonesChangesHandler[0] + " " + value)
                break;
            }
        }

        onTouchBegan: {
            robotBehaviourUpdated("TOUCHPAD", key, robot0)
        }

        onKidnappedChanged: {
            robotBehaviourUpdated("KIDNAPPED", kidnapped, robot0)
        }

        function followNewPoint(p){
            gameLogic.actOnNewPointToFollow(0, p)
        }

        onPoseChanged: {
            if(!isInActivity1 && gameLogic.currentGoalPoses[0] !== Qt.point(-1,-1) && isMoving){
                gameLogic.checkWhenGoalPointIsReached(0, x,y)
            }
        }

        LocomotionCalculator{
            id: locomotionCalculatorRobot0
            leaderPosition: Qt.point(robot0.x*gridSpacing, robot0.y*gridSpacing)
            leaderTheta: robot0.theta
            playgroundWidth: zoneE.realPlaygroundWidth - margin
            playgroundHeight: zoneE.realPlaygroundHeight - margin
            playgroundZeroX: margin
            playgroundZeroY: margin
            playgroundMargin: playgroundBorderMargin - 15
        }

        SpeedCalculator{
            id: speedCalculatorRobot0
            robotPosition: Qt.point(robot0.x*gridSpacing, robot0.y*gridSpacing)
            maxSpeed: base.maxSpeed
            minSpeed: base.minSpeed
            sigma: base.sigma
            heatZones: circularHeatZones
        }

        CelluloZoneCircleBorder{
            id: collisionBorder0
            active: associatedRobot.connected
            marginThickeness: 10
            name: "circleRobot0"
            property var associatedRobot: robot0
            x: associatedRobot.x*gridSpacing
            y: associatedRobot.y*gridSpacing
            r: page.robotDiagonal + 5
        }
    }

    CelluloBluetooth{
        id: robot1
        property var locomotionCalculator: locomotionCalculatorRobot1
        property var speedCalculator: speedCalculatorRobot1
        property var collisionBorder: collisionBorder1
        signal zoneValueUpdated(var type, int value, var robot, var zone)
        signal robotBehaviourUpdated(var type, int value, var robot)
        property bool isMoving: false

        onZonesChangesHandlerChanged: {
            var zoneConcerned = zonesChangesHandler[0]
            var value = zonesChangesHandler[1]
            var robot = robot1
            switch(zoneConcerned.type){
            case CelluloZoneTypes.CIRCLEINNER:
                debugView.valueCInner = value
                zoneValueUpdated("CIRCLEINNER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.CIRCLEBORDER:
                debugView.valueCBorder = value
                zoneValueUpdated("CIRCLEBORDER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.CIRCLEDISTANCE:
                zoneValueUpdated("CIRCLEDISTANCE", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.RECTANGLEINNER:
                debugView.valueRInner = value
                zoneValueUpdated("RECTANGLEINNER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.RECTANGLEBORDER:
                debugView.valueRBorder = value
                zoneValueUpdated("RECTANGLEBORDER", value, robot, zoneConcerned)
                break;
            default:
                console.log("UNKNOW IN " + zonesChangesHandler[0] + " " + value)
                break;
            }
        }

        onTouchBegan: {
            robotBehaviourUpdated("TOUCHPAD", key, robot1)
        }

        onKidnappedChanged: {
            robotBehaviourUpdated("KIDNAPPED", kidnapped, robot1)
        }

        function followNewPoint(p){
            gameLogic.actOnNewPointToFollow(1, p)
        }
        onPoseChanged: {
            if(!isInActivity1 && gameLogic.currentGoalPoses[1] !== Qt.point(-1,-1) && isMoving){
                gameLogic.checkWhenGoalPointIsReached(1, x,y)
            }
        }

        LocomotionCalculator{
            id: locomotionCalculatorRobot1
            leaderPosition: Qt.point(robot1.x*gridSpacing, robot1.y*gridSpacing)
            leaderTheta: parent.theta
            playgroundWidth: zoneE.realPlaygroundWidth - margin
            playgroundHeight: zoneE.realPlaygroundHeight - margin
            playgroundZeroX: margin
            playgroundZeroY: margin
            playgroundMargin: playgroundBorderMargin - 15
        }

        SpeedCalculator{
            id: speedCalculatorRobot1
            robotPosition: Qt.point(robot1.x*gridSpacing, robot1.y*gridSpacing)
            maxSpeed: base.maxSpeed
            minSpeed: base.minSpeed
            sigma: base.sigma
            heatZones: circularHeatZones
        }

        CelluloZoneCircleBorder{
            id: collisionBorder1
            active: associatedRobot.connected
            marginThickeness: 10
            name: "circleRobot1"
            property var associatedRobot: robot1
            x: associatedRobot.x*gridSpacing
            y: associatedRobot.y*gridSpacing
            r: page.robotDiagonal + 5
        }

    }

    CelluloBluetooth{
        id: robot2
        property var locomotionCalculator: locomotionCalculatorRobot2
        property var speedCalculator: speedCalculatorRobot2
        property var collisionBorder: collisionBorder2
        signal zoneValueUpdated(var type, int value, var robot, var zone)
        signal robotBehaviourUpdated(var type, int value, var robot)
        property bool isMoving: false

        onZonesChangesHandlerChanged: {
            var zoneConcerned = zonesChangesHandler[0]
            var value = zonesChangesHandler[1]
            var robot = robot2
            switch(zoneConcerned.type){
            case CelluloZoneTypes.CIRCLEINNER:
                debugView.valueCInner = value
                zoneValueUpdated("CIRCLEINNER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.CIRCLEBORDER:
                debugView.valueCBorder = value
                zoneValueUpdated("CIRCLEBORDER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.CIRCLEDISTANCE:
                zoneValueUpdated("CIRCLEDISTANCE", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.RECTANGLEINNER:
                debugView.valueRInner = value
                zoneValueUpdated("RECTANGLEINNER", value, robot, zoneConcerned)
                break;
            case CelluloZoneTypes.RECTANGLEBORDER:
                debugView.valueRBorder = value
                zoneValueUpdated("RECTANGLEBORDER", value, robot, zoneConcerned)
                break;
            default:
                console.log("UNKNOW IN " + zonesChangesHandler[0] + " " + value)
                break;
            }
        }

        onTouchBegan: {
            robotBehaviourUpdated("TOUCHPAD", key, robot2)
        }

        onKidnappedChanged: {
            robotBehaviourUpdated("KIDNAPPED", kidnapped, robot2)
        }

        function followNewPoint(p){
            gameLogic.actOnNewPointToFollow(2, p)
        }

        onPoseChanged: {
            if(!isInActivity1 && gameLogic.currentGoalPoses[2] !== Qt.point(-1,-1) && isMoving){
                gameLogic.checkWhenGoalPointIsReached(2, x,y)
            }
        }

        LocomotionCalculator{
            id: locomotionCalculatorRobot2
            leaderPosition: Qt.point(robot2.x*gridSpacing, robot2.y*gridSpacing)
            leaderTheta: parent.theta
            playgroundWidth: zoneE.realPlaygroundWidth - margin
            playgroundHeight: zoneE.realPlaygroundHeight - margin
            playgroundZeroX: margin
            playgroundZeroY: margin
            playgroundMargin: playgroundBorderMargin - 15
        }

        SpeedCalculator{
            id: speedCalculatorRobot2
            robotPosition: Qt.point(robot2.x*gridSpacing, robot2.y*gridSpacing)
            maxSpeed: base.maxSpeed
            minSpeed: base.minSpeed
            sigma: base.sigma
            heatZones: circularHeatZones
        }

        CelluloZoneCircleBorder{
            id: collisionBorder2
            marginThickeness: 10
            active: associatedRobot.connected
            name: "circleRobot2"
            property var associatedRobot: robot2
            x: associatedRobot.x*gridSpacing
            y: associatedRobot.y*gridSpacing
            r: page.robotDiagonal + 5
        }
    }

    CelluloZoneEngine{
        id: zoneE
        objectName: "ZoneEngine"
        vRplaygroundWidth: page.width
        vRplaygroundHeight: page.height
        realPlaygroundHeight: 841
        realPlaygroundWidth:  841


        onInitializationDone: {
            connectAll()
            EducationalActivityDrawer.setVisualParent(page)
            if(zoneE.addNewZoneFromJSON("://testDemo.json")){
                var zone;
                var heatType;
                //fill gradient color depending on speed interval
                for(var a = 0; a < gradientBlueToRed.length; a++ ){
                    gradientSpeed.push(minSpeed + a*diffSpeedInterval)
                }
                for(var i = 0; i< zoneE.getAllZoneNames().length; i++){
                    var name = zoneE.getAllZoneNames()[i]
                    if(name === "border_playground"){
                        //case rectangle border playground
                        playgroundBorderMargin = getZoneFromName(name).marginThickeness
                    } else if(name.indexOf("area") > -1 && name.indexOf("distance") > -1){
                        //case circular heatzones
                        heatType = gameLogic.getHeatType(name)
                        if(heatType !== -1){
                            zone = getZoneFromName(zoneE.getAllZoneNames()[i])
                            //compute placement points for activity 2
                            var pointsPlacementForRobot = []
                            if(heatType){
                                if(zoneE.addNewZoneFromQML(CelluloZoneTypes.RPOLYGONINNER, {"name": "pointsPlacementHot", "x": zone.x, "y": zone.y, "r": zone.r, "numEdges": robotsList.length, "rotAngle": 0})){
                                    pointsPlacementForRobot = getZoneFromName("pointsPlacementHot").vertices
                                }
                            }else {
                                if(zoneE.addNewZoneFromQML(CelluloZoneTypes.RPOLYGONINNER, {"name": "pointsPlacementCold", "x": zone.x, "y": zone.y, "r": zone.r-120, "numEdges": robotsList.length, "rotAngle": 0})){
                                    pointsPlacementForRobot = getZoneFromName("pointsPlacementCold").vertices
                                }
                            }
                            //take only need information from the zone needed by the activities
                            circularHeatZones.push({nameHeatZone: zone.name.split("_")[1], x: zone.x, y: zone.y, r: zone.r, isHot: heatType, pointsPlacementForRobot: pointsPlacementForRobot, onceInZone: [false,false,false], numberRobotsInZone: 0})
                        }
                    }
                }
                for(var j = 0; j < robotsList.length; j++){
                    robotsList[j].speedCalculator.heatZones = circularHeatZones
                    gameLogic.currentGoalPoses[j] = Qt.point(-1,-1)
                    //create debug view components for activity 1
                    debugView.createDebugComponentsLocomotionCalculator(j)
                    //create debug view components for activity 2
                    debugView.createDebugComponentsSpeedCalculator(j)
                    //create visual for robot
                    EducationalActivityDrawer.createRobotVizu(j)
                }
            } else {
                console.log("problem loading zones")
            }
            gameLogic.locomotionTimer.start()
        }

        //do extra connection between signal/slot
        function connectAll(){
            zoneE.newZoneCreatedReadyForVisualization.connect(EducationalActivityDrawer.drawNewZone)
            for(var i = 0; i < robotsList.length; i++){
                (robotsList[i].locomotionCalculator).onNewPointToFollow.connect(robotsList[i].followNewPoint)
                robotsList[i].zoneValueUpdated.connect(gameLogic.reactUponGameChange)
                robotsList[i].robotBehaviourUpdated.connect(gameLogic.reactUponGameChange)

            }
            buttonChangeActivity.changeTypeOfActivity.connect(gameLogic.reactUponGameChange)
        }
    }



    CelluloZoneJsonHandler{
        id: jsonHandler
    }

    CelluloZoneTypes{
        id: typesEnum
    }

    GameLogic{
        id: gameLogic
        gameRobotsList: robotsList
        gameGradientSpeed: gradientSpeed
        gameGradientBlueToRed :gradientBlueToRed
        gameCircularHeatZones: circularHeatZones
        gameGridSpacing: gridSpacing
    }

    DebugView{
        id: debugView
        page: page
        gameLogic: gameLogic
        isActivity1Playing: isInActivity1
    }
}
