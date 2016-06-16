import QtQuick 2.0
import QtQuick.Controls 1.2

Item {
    id: debugView
    property var base: parent
    property var page
    property var gameLogic
    property var isActivity1Playing
    visible: false
    anchors.left: page.right
    anchors.top: page.top
    anchors.leftMargin: 40

    property var  valueRInner: 0
    property var valueRBorder: 0
    property var  valueCInner: 0
    property var valueCBorder: 0

    Column{
        Column{
            visible: debugView.visible
            id: debugValuesBase

            Text{
                text: "RectangleInner?"
                color: (valueRInner===1) ? "green" : "red"
            }
            Text{
                text: "RectangleBorder?"
                color: (valueRBorder===1) ? "green" : "red"
            }
            Text{
                text: "CircleInner?"
                color: (valueCInner===1) ? "green" : "red"
            }
            Text{
                text: "CircleBorder?"
                color: (valueCBorder===1) ? "green" : "red"
            }
        }

        Column{
            id: debugValuesGameLogic
            visible:  debugView.visible && !(gameLogic === undefined)
            Text{
                text: "Activity1?"
                color: gameLogic.currentStage === gameLogic.game_stage["ACTIVITY1"] ? "green" : "red"
            }
            Text {
                visible: debugView.visible
                text: gameLogic.collisionHappening? "COLLISION? YES": "COLLISION? NO"
                color: "black"
            }
        }
    }

    function createDebugComponentsSpeedCalculator(i){
        var speedCalculator = base.robotsList[i].speedCalculator
        if(speedCalculator !== undefined){
            var heatzones = speedCalculator.heatZones



            for(var j= 0; j< heatzones.length; j++){
                var isHot = heatzones[j].isHot
                var pointsPlacementForRobot = heatzones[j].pointsPlacementForRobot
                if(isHot){
                    Qt.createQmlObject(
                                'import QtQuick 2.2;
                        Rectangle{id: placementPoint' + i + ';\
                            visible:  debugView.visible && !isActivity1Playing; \
                            z:10;x:'+ (realToVr(pointsPlacementForRobot[i]).x -5) +';\
                            y: '+ (realToVr(pointsPlacementForRobot[i]).y -5) + ';\
                            height: '+ 10 + ';\
                            width: '+ 10 +';\
                            color: "#ffb3b3";\
                            border.color: "black";\
                            border.width: 1;\
                        }',
                                page,'point' + i)
                    Qt.createQmlObject(
                                'import QtQuick 2.2;
                        Text {id: placementText' + i + ';\
                            visible:  debugView.visible && !isActivity1Playing; \
                            text: "' +i+'";x: '+realToVr(pointsPlacementForRobot[i]).x+';y: '+realToVr(pointsPlacementForRobot[i]).y+';\
                            z: 10;font.pointSize: 24; \
                            font.bold: true; \
                            color: "#ffb3b3";\
                        }',
                                page,'text' + i)
                }else {

                    Qt.createQmlObject(
                                'import QtQuick 2.2;
                        Rectangle{id: point' + i + ';\
                            visible:  debugView.visible && !isActivity1Playing; \
                            z:10;\
                            x:'+ (realToVr(pointsPlacementForRobot[i]).x -5) +';\
                            y: '+ (realToVr(pointsPlacementForRobot[i]).y -5) + ';\
                            height: '+ 10 + ';\
                            width: '+ 10 +';\
                            color: "cyan";\
                            border.color: "black";\
                            border.width: 1;\
                        }',
                                page,'point' + i)
                    Qt.createQmlObject(
                                'import QtQuick 2.2;
                        Text {id: placementText' + i + ';\
                            visible:  debugView.visible && !isActivity1Playing; \
                            text: "' +i+'";x: '+realToVr(pointsPlacementForRobot[i]).x+';y: '+realToVr(pointsPlacementForRobot[i]).y+';\
                            z: 10;\
                            font.pointSize: 24;\
                            font.bold: true;\
                            color: "cyan";\
                        }',
                                page,'text' + i)
                }
            }
        }
    }

    function createDebugComponentsLocomotionCalculator(i){
        Qt.createQmlObject('import QtQuick 2.2;
                            Rectangle{
                                id: debugComponentPadBouceLocomotion' + i + '; \
                                color: "#00000000"; \
                                anchors.fill: parent; \
                                property var locomotionCalculator: base.robotsList['+i+'].locomotionCalculator; \
                                visible:  debugView.visible && !(locomotionCalculator === undefined) && isActivity1Playing; \
                                z: 20; \

                                Rectangle{
                                    id: selectedPad' + i + '; \
                                    x: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.padVerticesRegularRobot[locomotionCalculator.selectedPadIndex].x) -5; \
                                    y: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.padVerticesRegularRobot[locomotionCalculator.selectedPadIndex].y) -5; \
                                    z:6; \
                                    height: 10; \
                                    width: 10; \
                                    color: "black"; \
                                } \

                                Rectangle{
                                    id: current' + i + '; \
                                    z:10; \
                                    x:(locomotionCalculator === undefined)? 0 :  debugView.mmToVR(locomotionCalculator.currentPoint.x) -width/2; \
                                    y: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.currentPoint.y) -height/2; \
                                    height: 30; \
                                    width: 30; \
                                    color: "yellow"; \
                                    Text {text: "' + i + '";anchors.horizontalCenter: current' + i + '.horizontalCenter;anchors.verticalCenter: current' + i + '.verticalCenter;z: 10;font.pointSize: 24; font.bold: true;}
                                } \
                                Rectangle{
                                    id: previous' + i + '; \
                                    z:10; \
                                    x: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.previousPoint.x) -width/2; \
                                    y: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.previousPoint.y) -height/2; \
                                    height: 30; \
                                    width: 30; \
                                    color: "purple"; \
                                    Text {text: "' + i + '";anchors.horizontalCenter: previous' + i + '.horizontalCenter;anchors.verticalCenter: previous' + i + '.verticalCenter;z: 10;font.pointSize: 24; font.bold: true;}
                                } \
                                Rectangle{
                                    id: reflected' + i + '; \
                                    visible:  debugView.visible && !(locomotionCalculator === undefined) && isActivity1Playing; \
                                    z:10; \
                                    x: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.reflectedPoint.x) -width/2; \
                                    y:(locomotionCalculator === undefined)? 0 :  debugView.mmToVR(locomotionCalculator.reflectedPoint.y) -height/2; \
                                    height: 30; \
                                    width: 30; \
                                    color: "red"; \
                                    Text {text: "' + i + '";anchors.horizontalCenter: reflected' + i + '.horizontalCenter;anchors.verticalCenter: reflected' + i + '.verticalCenter;z: 10;font.pointSize: 24; font.bold: true;}
                                } \
                                Rectangle{
                                    id: centerCircleRobotCollidedVizu
                                    visible:  debugView.visible && !(locomotionCalculator === undefined) && isActivity1Playing; \
                                    x: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.centerCircleRobotCollided.x) -width/2; \
                                    y: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.centerCircleRobotCollided.y) -height/2; \
                                    width: 40
                                    height: 40
                                    z: 15
                                    color: "pink"
                                } \

                                Rectangle{
                                    id: collisionPointWithRobotVizu
                                    visible:  debugView.visible && !(locomotionCalculator === undefined) && isActivity1Playing; \
                                    x: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.collisionPointWithRobot.x) -width/2; \
                                    y: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.collisionPointWithRobot.y) -height/2; \
                                    width: 40
                                    height: 40
                                    z: 15
                                    color: "yellow"
                                } \

                                Rectangle{
                                    id: borderPointCollisionVizu
                                    visible:  debugView.visible && !(locomotionCalculator === undefined) && isActivity1Playing; \
                                    x: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.centerCircleRobotCollided.x) -width/2; \
                                    y: (locomotionCalculator === undefined)? 0 : debugView.mmToVR(locomotionCalculator.centerCircleRobotCollided.y) -height/2; \
                                    width: 40
                                    height: 40
                                    z: 15
                                    color: "blue"
                                } \

                                Rectangle{id: collisionBorderVizu;
                                    visible:  debugView.visible && !(locomotionCalculator === undefined) && isActivity1Playing && robot.connected; \
                                    property var robot: base.robotsList['+i+'];
                                    property var collisionBorder: robot.collisionBorder;
                                    property var xCircleVizu: (collisionBorder.x/zoneE.realPlaygroundWidth)*zoneE.vRplaygroundWidth
                                    property var yCircleVizu: (collisionBorder.y/zoneE.realPlaygroundHeight)*zoneE.vRplaygroundHeight
                                    property var rCircleVizu: Math.sqrt(((collisionBorder.r*collisionBorder.r)/(zoneE.realPlaygroundWidth*zoneE.realPlaygroundHeight))*zoneE.vRplaygroundWidth*zoneE.vRplaygroundWidth)
                                    property var marginCircleVizu: (collisionBorder.marginThickeness/zoneE.realPlaygroundWidth)*zoneE.vRplaygroundWidth
                                    x: xCircleVizu- (rCircleVizu+marginCircleVizu/2)
                                    y: yCircleVizu - (rCircleVizu+marginCircleVizu/2)
                                    height: (rCircleVizu+marginCircleVizu/2) * 2;
                                    width: (rCircleVizu+marginCircleVizu/2) * 2;
                                    color: "#00000000"
                                    border.color: "grey";
                                    border.width: marginCircleVizu;
                                    radius: (rCircleVizu+marginCircleVizu/2)
                                    z:15
                                    rotation: robot.theta
                                } \


}',
                           page, 'debugComponentPadBouceLocomotion' + i)
    }

    function mmToVR(coord){
        return coord*page.scaleCoeff
    }

    function realToVr(p){
        return Qt.point((p.x/zoneE.realPlaygroundWidth)*zoneE.vRplaygroundWidth, (p.y/zoneE.realPlaygroundHeight)*zoneE.vRplaygroundHeight)
    }

}
