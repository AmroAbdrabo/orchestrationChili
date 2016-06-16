import QtQuick 2.0

//item to compute next point to follow for the robot depeding on the motion case
Item {
    //ALL VALUES ARE IN MM
    id: locomotionCalculator

    /////////////////////////////////////////////////////// General infos
    property var playgroundWidth: 0
    property var playgroundHeight: 0
    property var playgroundZeroX: 0
    property var playgroundZeroY: 0
    property var margin: playgroundMargin/2
    property var playgroundMargin: 0
    property var gridSpacing: 0.508

    /////////////////////////////////////////////////////// Robot infos
    property var leaderPosition: Qt.point(0,0)
    property var leaderTheta: 0

    /////////////////////////////////////////////////////// Intersection with rectangle border infos
    property var rectLines: getLinesFromRect(playgroundZeroX,playgroundZeroY,playgroundWidth, playgroundHeight)
    property var pointsOnRect: [Qt.point(0,0), Qt.point(0,0)]

    /////////////////////////////////////////////////////// Computation of point to follow infos
    property var currentPoint: Qt.point(0,0)
    property var previousPoint: Qt.point(0,0)
    property var reflectedPoint: Qt.point(0,0)
    property var goalPositionInmm: Qt.point(0,0)

    /////////////////////////////////////////////////////// Pad locomotion infos
    property var selectedPadIndex: 0
    property var padVerticesRegularRobot: getPadPoints(6, leaderPosition.x,leaderPosition.y, 15, -leaderTheta +60)
    property var padPoint: Qt.point(0,0)

    /////////////////////////////////////////////////////// Bouncing infos
    property var needApplyReflection: false

    /////////////////////////////////////////////////////// Collision infos
    property var collisionPointWithRobot: Qt.point(-1,-1)
    property var centerCircleRobotCollided: Qt.point(-1,-1)


    signal onNewPointToFollow(var p)                /// signal emitted to give to the robot a new point to follow

    //case motion by pad direction
    onSelectedPadIndexChanged: {
        console.log("Motion by pad direction");
        padPoint = Qt.point(padVerticesRegularRobot[selectedPadIndex].x, padVerticesRegularRobot[selectedPadIndex].y)
        pointsOnRect = rectLineIntersect(rectLines, padPoint, leaderPosition)
        goalPositionInmm = (pointsOnRect.length === 2)? selectPointToFollowPad(leaderPosition, padPoint, pointsOnRect[0], pointsOnRect[1]): Qt.point(0,0)
        previousPoint = padPoint
        currentPoint = Qt.point(goalPositionInmm.x, goalPositionInmm.y)
        onNewPointToFollow(Qt.point((goalPositionInmm.x)/gridSpacing,(goalPositionInmm.y)/gridSpacing))
    }

    //case motion by bouncing
    onNeedApplyReflectionChanged: {
        if(needApplyReflection){
            if(collisionPointWithRobot === Qt.point(-1,-1)){
                //case motion by bouncing on playground border
                console.log("Motion by bouncing on playground border");
                reflectedPoint = getReflectedPointFromBorderCollision()
                pointsOnRect = rectLineIntersect(rectLines, currentPoint, reflectedPoint)
                goalPositionInmm = (pointsOnRect.length === 2)? selectPointToFollowReflection(currentPoint, pointsOnRect[0], pointsOnRect[1]): Qt.point(0,0)

            } else {
                //case motion by bouncing following collision
                console.log("Motion by bouncing following collisio");
                var borderCollisionPoint = Qt.point((centerCircleRobotCollided.x + collisionPointWithRobot.x)/2, (centerCircleRobotCollided.y + collisionPointWithRobot.y)/2)
                currentPoint = borderCollisionPoint
                reflectedPoint = getReflectedPointFromRobotCollision()
                pointsOnRect = rectLineIntersect(rectLines, currentPoint, reflectedPoint)
                goalPositionInmm = (pointsOnRect.length === 2)? selectPointToFollowCollision(currentPoint, reflectedPoint, pointsOnRect[0], pointsOnRect[1]): Qt.point(0,0)
                collisionPointWithRobot = Qt.point(-1,-1)
                centerCircleRobotCollided = Qt.point(-1,-1)
            }

            previousPoint = currentPoint
            currentPoint = Qt.point(goalPositionInmm.x, goalPositionInmm.y)

            //check for case where robot is in corners
            if(Math.abs(currentPoint.x - previousPoint.x) < 20 && Math.abs(currentPoint.y - previousPoint.y) < 20){
                var delta = 50
                if(Math.abs(currentPoint.x - playgroundWidth) < 10){
                    if(Math.abs(currentPoint.y - playgroundHeight) < 10){
                        currentPoint = Qt.point(playgroundZeroX, playgroundZeroY + delta)
                    } else {
                        currentPoint = Qt.point(playgroundZeroX, playgroundHeight - delta)
                    }
                }else if (Math.abs(currentPoint.x - playgroundZeroX) < 10){
                    if(Math.abs(currentPoint.y - playgroundHeight) < 10){
                        currentPoint = Qt.point(playgroundWidth, playgroundZeroY + delta)
                    } else {
                        currentPoint = Qt.point(playgroundWidth, playgroundHeight - delta)
                    }
                }
                goalPositionInmm = currentPoint

            }
            onNewPointToFollow(Qt.point((goalPositionInmm.x)/gridSpacing,(goalPositionInmm.y)/gridSpacing))
            needApplyReflection = false
        }
    }

    //General functions for 3 cases
    function getLinesFromRect(x,y,width,height){
        return [{x1: x, y1: y, x2: width, y2: y},{x1: width, y1: y, x2: width, y2: height},{x1: width, y1: height, x2: x, y2: height},{x1: x, y1: height, x2: x, y2: y}]
    }

    function rectLineIntersect(rectLines, p1, p2){
        var results = []
        for(var i = 0; i<rectLines.length; i++){
            var result = checkLineIntersection(rectLines[i].x1, rectLines[i].y1, rectLines[i].x2, rectLines[i].y2, p1.x, p1.y, p2.x, p2.y)
            if(result.x !== null && result.y !== null && result.x <= playgroundWidth && result.y <= playgroundHeight && result.x >= playgroundZeroX && result.y >= playgroundZeroY){
                results.push(result)
            }
        }
        return results
    }

    //taken from: http://jsfiddle.net/justin_c_rounds/Gd2S2/
    function checkLineIntersection(line1StartX, line1StartY, line1EndX, line1EndY, line2StartX, line2StartY, line2EndX, line2EndY) {
        var denominator, a, b, numerator1, numerator2, result = {
            x: null,
            y: null,
            onLine1: false,
            onLine2: false
        };
        denominator = ((line2EndY - line2StartY) * (line1EndX - line1StartX)) - ((line2EndX - line2StartX) * (line1EndY - line1StartY));
        if (denominator === 0) {
            return result;
        }
        a = line1StartY - line2StartY;
        b = line1StartX - line2StartX;
        numerator1 = ((line2EndX - line2StartX) * a) - ((line2EndY - line2StartY) * b);
        numerator2 = ((line1EndX - line1StartX) * a) - ((line1EndY - line1StartY) * b);
        a = numerator1 / denominator;
        b = numerator2 / denominator;

        result.x = line1StartX + (a * (line1EndX - line1StartX));
        result.y = line1StartY + (a * (line1EndY - line1StartY));

        if (a > 0 && a < 1) {
            result.onLine1 = true;
        }
        if (b > 0 && b < 1) {
            result.onLine2 = true;
        }
        return result;
    }

    //Functions for motion by pad direction
    function getPadPoints(numEdges, x, y, r, rotAngleDegree){
        var rotAngleRadian = rotAngleDegree * (Math.PI/180)
        var points = []
        if(numEdges>2){
            for (var i = 0; i < numEdges; i++) {
                //taken from: http://stackoverflow.com/questions/3436453/calculate-coordinates-of-a-regular-polygons-vertices
                var point = Qt.point(x + r * Math.cos(2 * Math.PI * (5-i) / numEdges + rotAngleRadian), y + r * Math.sin(2 * Math.PI * (5-i) / numEdges + rotAngleRadian));
                points.push(point);
            }
        } else {
            console.log("n must be >2");
        }
        return points;
    }

    function selectPointToFollowPad(center, pad, p1, p2){
        if(center.x >= pad.x){
            if(p1.x <= pad.x){
                return p1
            }
            if(p2.x <= pad.x){
                return p2
            }
        } else {
            if(p1.x >= pad.x){
                return p1
            }
            if(p2.x >= pad.x){
                return p2
            }
        }

    }

    //Functions for motion by bouncing
    function getReflectedVector(v1,n){
        var normN = Math.sqrt(n.x*n.x + n.y*n.y)
        var nNormed = {x: n.x/normN, y: n.y/normN}
        var dotProductResult = v1.x*nNormed.x + v1.y*nNormed.y
        var newX = v1.x - (2*dotProductResult*nNormed.x)
        var newY = v1.y - (2*dotProductResult*nNormed.y)
        return {x: newX, y: newY}
    }

    //Functions for motion by bouncing on playground border
    function selectPointToFollowReflection(border, p1, p2){
        if(border.x.toFixed(2) === p1.x.toFixed(2) && border.y.toFixed(2) === p1.y.toFixed(2)){
            return p2
        } else {
            return p1
        }
    }

    function getReflectedPointFromBorderCollision(){
        var perpendicularVector = Qt.point(0,0)

        if(currentPoint.x .toFixed(1)=== playgroundWidth.toFixed(1)){
            perpendicularVector.x = playgroundWidth - 50
            perpendicularVector.y = currentPoint.y
        }else if(currentPoint.x === playgroundZeroX){
            perpendicularVector.x = playgroundZeroX + 50
            perpendicularVector.y = currentPoint.y
        }else if(currentPoint.y.toFixed(1) === playgroundHeight.toFixed(1)){
            perpendicularVector.x = currentPoint.x
            perpendicularVector.y = playgroundHeight - 50
        }else if(currentPoint.y === playgroundZeroY){
            perpendicularVector.x = currentPoint.x
            perpendicularVector.y = playgroundZeroY + 50
        }
        var v = getReflectedVector({x: currentPoint.x - previousPoint.x, y: currentPoint.y - previousPoint.y},{x: perpendicularVector.x - currentPoint.x, y:perpendicularVector.y - currentPoint.y})
        return {x: currentPoint.x + v.x, y: currentPoint.y + v.y}
    }


    //Functions for motion by bouncing following collision
    function selectPointToFollowCollision(bordercollision, reflected, p1, p2){
        if(reflected.x < playgroundZeroX){
            reflected.x = playgroundZeroX
        }
        if (reflected.y < playgroundZeroY){
            reflected.y = playgroundZeroY
        }
        if(reflected.x > playgroundWidth){
            reflected.x = playgroundWidth - playgroundZeroX
        }
        if(reflected.y > playgroundHeight){
            reflected.y = playgroundHeight - playgroundZeroY
        }
        if(bordercollision.x >= reflected.x){
            if(p1.x <= reflected.x || p1.y <= reflected.y){
                return p1
            }
            if(p2.x <= reflected.x || p2.y <= reflected.y){
                return p2
            }
        } else {
            if(p1.x >= reflected.x || p1.y >= reflected.y){
                return p1
            }
            if(p2.x >= reflected.x || p2.y >= reflected.y){
                return p2
            }
        }
    }

    function getReflectedPointFromRobotCollision(){
        var v = getReflectedVector({x: currentPoint.x - previousPoint.x, y: currentPoint.y - previousPoint.y},{x: collisionPointWithRobot.x - currentPoint.x, y:collisionPointWithRobot.y - currentPoint.y})
        return {x: currentPoint.x + v.x, y: currentPoint.y + v.y}
    }

}
