import QtQuick 2.0

Item {
    property var gameRobotsList
    property var gameGridSpacing: 0
    property var gameGradientSpeed: []
    property var gameGradientBlueToRed: []
    property var gameCircularHeatZones: []
    property var currentGoalPoses: []
    property var currentStage: 0
    property var thresoldGoalPosition: 5
    property bool collisionHappening: false
    property var locomotionTimer: locomotionTimer

    property var game_stage: {
        "ACTIVITY1": 0,
                "ACTIVITY2": 1
    };


    property var signal_type: {
        "RECTANGLEBORDER": 0,
                "RECTANGLEINNER": 1,
                "CIRCLEBORDER": 2,
                "CIRCLEINNER": 3,
                "CIRCLEDISTANCE": 4,
                "TOUCHPAD": 5,
                "POSECHANGED": 6,
                "TOUCHBUTTONCHANGEACTIVITY": 7,
                "KIDNAPPED": 8
    }

    /////////////////////////////////////////////////////// SIGNAL HANDLER SLOT FUNCTION


    function reactUponGameChange(type, value, robot, zone){
        if(signal_type[type] !== signal_type["CIRCLEDISTANCE"]){
            console.log("Received" + type + " of "+ zone + ", " + value + " from " + robot)
        }
        switch(signal_type[type]){
        case signal_type["RECTANGLEBORDER"]:
            if(value === 1 && currentStage === game_stage["ACTIVITY1"]){
                robot.locomotionCalculator.needApplyReflection = true
            }
            break;
        case signal_type["RECTANGLEINNER"]:
            break;
        case signal_type["CIRCLEBORDER"]:
            if(currentStage === game_stage["ACTIVITY1"]){
                if(value === 1){
                    if(zone!== undefined) {
                        if(zone.associatedRobot !== robot && !collisionHappening){
                            collisionHappening = true
                            collisionTimer.start()
                            var colliderInitiator = robot
                            var colliderReceiver = zone.associatedRobot
                            colliderInitiator.locomotionCalculator.collisionPointWithRobot = Qt.point(colliderInitiator.x*gameGridSpacing, colliderInitiator.y*gameGridSpacing)
                            colliderInitiator.locomotionCalculator.centerCircleRobotCollided = Qt.point(zone.x, zone.y)
                            colliderInitiator.locomotionCalculator.needApplyReflection = true

                            colliderReceiver.locomotionCalculator.collisionPointWithRobot = Qt.point(colliderReceiver.x*gameGridSpacing, colliderReceiver.y*gameGridSpacing)
                            colliderReceiver.locomotionCalculator.centerCircleRobotCollided = Qt.point(colliderInitiator.collisionBorder.x, colliderInitiator.collisionBorder.y)
                            colliderReceiver.locomotionCalculator.needApplyReflection = true
                        } else{
                            console.log("Collision with robot itself, ignored")
                        }
                    } else {
                        console.log("Collision with robot not connected")
                    }
                } else{
                }
            }
            break;
        case signal_type["CIRCLEINNER"]:
            if(currentStage === game_stage["ACTIVITY2"]){
                var heatZone = getHeatZoneFromName(zone.name)
                if(value === 1){
                    heatZone.onceInZone[0] = true
                    heatZone.numberRobotsInZone++
                    robot.setVisualEffect(0, getHeatType(heatZone.nameHeatZone)===1?"red":"blue", 0);
                } else{
                    robot.setVisualEffect(0, "white", 0);
                    if(heatZone.onceInZone[0]){
                        heatZone.numberRobotsInZone--
                    }
                }

                if(heatZone.numberRobotsInZone < 0){
                    heatZone.numberRobotsInZone = 0
                }
                console.log("Number  of robot in heat zone " + heatZone.nameHeatZone + ": " + heatZone.numberRobotsInZone)
                if(gameRobotsList.length === heatZone.numberRobotsInZone){
                    console.log("Enough robot in heat zone " + heatZone.nameHeatZone)
                    var pointsToGoTo = heatZone.pointsPlacementForRobot
                    for(var i=0; i<gameRobotsList.length; i++){
                        gameRobotsList[i].isMoving = true
                        gameRobotsList[i].setGoalPosition(pointsToGoTo[i].x/gameGridSpacing, pointsToGoTo[i].y/gameGridSpacing, 20)
                        currentGoalPoses[i] = Qt.point(pointsToGoTo[i].x/gameGridSpacing, pointsToGoTo[i].y/gameGridSpacing)
                    }
                }
            }
            break;
        case signal_type["CIRCLEDISTANCE"]:
            if(currentStage === game_stage["ACTIVITY1"]){
                robot.speedCalculator.changeDistanceForHeatZone(zone.name, value<0?0:value)
            }
            break;
        case signal_type["TOUCHPAD"]:
            if(!robot.kidnapped && currentStage === game_stage["ACTIVITY1"]){
                robot.locomotionCalculator.selectedPadIndex = value
            }
            break;
        case signal_type["POSECHANGED"]:
            if(!robot.kidnapped && currentStage === game_stage["ACTIVITY1"]){
                robot.locomotionCalculator.selectedPadIndex = value
            }
            break;
        case signal_type["TOUCHBUTTONCHANGEACTIVITY"]:
            if(value){
                currentStage = game_stage["ACTIVITY1"]
            }else{
                currentStage = game_stage["ACTIVITY2"]
            }
            for(var i=0; i<gameRobotsList.length; i++){
                gameRobotsList[i].isMoving = false
                resetAction()
                currentGoalPoses[i] = Qt.point(-1,-1)
            }
            break;
        case signal_type["KIDNAPPED"]:
            robot.setAllMotorOutputs(0,0,0)
            break;
        default:
            console.log("Unhandled signal")
        }
    }

    /////////////////////////////////////////////////////// TIMERS

    Timer {
        id: locomotionTimer
        interval: 250
        repeat: true
        running: true
        onTriggered: {
            for(var i = 0; i < gameRobotsList.length; i++){
                if(gameRobotsList[i].isMoving && currentStage === game_stage["ACTIVITY1"]){
                    var speed = gameRobotsList[i].speedCalculator.computeSpeed()
                    gameRobotsList[i].setGoalPosition(currentGoalPoses[i].x, currentGoalPoses[i].y,speed)
                    gameRobotsList[i].setVisualEffect(0, gameGradientBlueToRed[getColorFromSpeed(speed, 0, gameGradientSpeed.length -1)], 0);
                } else if (gameRobotsList[i].isMoving && currentStage === game_stage["ACTIVITY2"]){
                    gameRobotsList[i].setGoalPosition(currentGoalPoses[i].x, currentGoalPoses[i].y,20)
                }
            }
        }
    }

    Timer {
        id: collisionTimer
        interval: 2000
        repeat: false
        running: true
        onTriggered: {
            collisionHappening = false
        }
    }

    /////////////////////////////////////////////////////// HELPER FUNCTIONS


    //reset game
    function resetAction(){
        for(var i = 0; i < gameRobotsList.length; i++){
            gameRobotsList[i].setVisualEffect(0, "white", 0);
            gameRobotsList[i].reset()
            gameRobotsList[i].setGoalPosition(0,0,0)
        }
    }

    //act following new point to follow
    function actOnNewPointToFollow(robotIndex, pointToFollow){
        var robot = gameRobotsList[robotIndex]
        var speed = gameRobotsList[robotIndex].speedCalculator.computeSpeed()
        console.log("New pose for robot " + robotIndex + " : " + robot + " in mm(" + pointToFollow.x*gameGridSpacing +  "," + pointToFollow.y*gameGridSpacing + ") with speed " + speed)
        robot.setGoalPosition(pointToFollow.x, pointToFollow.y,speed)
        currentGoalPoses[robotIndex] = pointToFollow
        if(!robot.isMoving){
            robot.isMoving = true
        }
    }

    //check when goal point is reached and update accordingly robot's infos
    function checkWhenGoalPointIsReached(robotIndex,x,y){
        var robot = gameRobotsList[robotIndex]
        if(Math.abs(currentGoalPoses[robotIndex].x - x) < thresoldGoalPosition && Math.abs(currentGoalPoses[robotIndex].y - y) < thresoldGoalPosition){
            console.log("Targeted point reached for robot " + robotIndex)
            robot.isMoving = false
            robot.reset()
            robot.setGoalPosition(0,0,0)
            currentGoalPoses[robotIndex] = Qt.point(-1,-1)
        }
    }

    //return color associated to the given speed
    function getColorFromSpeed(currSpeed, beginIndex, lastIndex){
        var length = (lastIndex- beginIndex)
        if(length >= 2){
            var middle = Math.floor((lastIndex+ beginIndex)/2)
            if(currSpeed> gameGradientSpeed[middle]){
                return getColorFromSpeed(currSpeed, middle, lastIndex)
            } else {
                return getColorFromSpeed(currSpeed, beginIndex, middle)

            }
        } else {
            return gameGradientSpeed[lastIndex] > currSpeed? beginIndex: lastIndex
        }
    }

    //return heatZone from given name
    function getHeatZoneFromName(zoneName){
        var zoneNameShorten = zoneName.split("_")[1]
        for(var i =0; i <gameCircularHeatZones.length; i++){
            if(gameCircularHeatZones[i].nameHeatZone===zoneNameShorten){
                return gameCircularHeatZones[i]
            }
        }
    }

    //return 1 if it's a hot zone (i.e. has "hot" in its name) and 0 ow (i.e. has "cold" in its name)
    function getHeatType(zoneName){
        var result = -1
        if(zoneName.indexOf("hot") > -1){
            result = 1
        } else if (zoneName.indexOf("cold") > -1){
            result = 0
        }
        return result
    }
}


