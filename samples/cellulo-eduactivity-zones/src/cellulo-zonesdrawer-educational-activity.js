var parent = null

function setVisualParent(newparent) {
    parent = newparent
}

function drawNewCircleInner(nameCircleInner, rCircleInner, xCircleInner, yCircleInner, childNumber, playgroundWidth, playgroundHeight) {
    xCircleInner = xCircleInner * playgroundWidth
    yCircleInner = yCircleInner * playgroundHeight
    rCircleInner = Math.sqrt(rCircleInner * playgroundWidth * playgroundHeight)
    var color = "grey"
    if (nameCircleInner.indexOf("hot") > -1) {
        color = "red"
    } else if (nameCircleInner.indexOf("cold") > -1) {
        color = "blue"
    }

    Qt.createQmlObject(
        'import QtQuick 2.2;Rectangle{id: child' + childNumber + ';property var nameHeatZone: "' + nameCircleInner + '"; x:' + xCircleInner + '-' + rCircleInner + ';y: ' + yCircleInner + '- ' + rCircleInner + ';height: ' + rCircleInner + ' * 2;width: ' + rCircleInner + ' * 2;color: "' + color + '";border.color: "black";border.width: 1;radius: ' + rCircleInner + ';}',
        parent, 'child' + childNumber)
}

function drawNewCircleDistance(nameCircleDistance, rCircleDistance, xCircleDistance, yCircleDistance, childNumber, playgroundWidth, playgroundHeight) {
    xCircleDistance = xCircleDistance * playgroundWidth
    yCircleDistance = yCircleDistance * playgroundHeight
    rCircleDistance = Math.sqrt(rCircleDistance * playgroundWidth * playgroundHeight)
    var color = "grey"
    if (nameCircleDistance.indexOf("hot") > -1) {
        color = "#8A0808"
    } else if (nameCircleDistance.indexOf("cold") > -1) {
        color = "#0B2161"
    }

    Qt.createQmlObject(
        'import QtQuick 2.2;Rectangle{id: child' + childNumber + ';property var nameHeatZone: "' + nameCircleDistance + '"; x:' + xCircleDistance + ';y: ' + yCircleDistance + ';height: 10 ;width: 10 ;color: "' + color + '";border.color: "black";border.width: 1;radius: width*0.5;}',
        parent, 'child' + childNumber)
}

function drawNewRectangleBorder(xRectangleBorder, yRectangleBorder, heightRectangleBorder, widthRectangleBorder, marginRectangleBorder, childNumber, playgroundWidth, playgroundHeight) {
    marginRectangleBorder = marginRectangleBorder * playgroundWidth
    xRectangleBorder = xRectangleBorder * playgroundWidth
    yRectangleBorder = yRectangleBorder * playgroundHeight
    widthRectangleBorder = widthRectangleBorder * playgroundWidth
    heightRectangleBorder = heightRectangleBorder * playgroundHeight

    Qt.createQmlObject(
        'import QtQuick 2.2;  \
            Rectangle{ \
        x:' + xRectangleBorder + '; \
        y:' + yRectangleBorder + '; \
        height: ' + heightRectangleBorder + '; \
        width: ' + widthRectangleBorder + ';\
        color: "#00000000";border.color: "grey"; \
        border.width:' + marginRectangleBorder / 2 + '; \
            }',
        parent, 'child' + childNumber)
}

function drawNewZone(type, properties, childnumber, playgroundWidth, playgroundHeight) {
    if (parent == null) {
        console.log("You forgot to set a visual parent with setVisualParent or your parent is null")

    } else {

        switch (type) {
            case CelluloZoneTypes.CIRCLEINNER:
                drawNewCircleInner(properties["name"], properties["r"], properties["x"], properties["y"], childnumber, playgroundWidth, playgroundHeight)
                break;
            case CelluloZoneTypes.CIRCLEDISTANCE:
                drawNewCircleDistance(properties["name"], properties["r"], properties["x"], properties["y"], childnumber, playgroundWidth, playgroundHeight)
                break;
            case CelluloZoneTypes.RECTANGLEBORDER:
                drawNewRectangleBorder(properties["x"], properties["y"], properties["height"], properties["width"], properties["marginThickeness"], childnumber, playgroundWidth, playgroundHeight)
                break;
            case CelluloZoneTypes.RPOLYGONINNER:
                //case handled in DebugView
                break;
            default:
                console.debug("Forgot to handle an enum case for this activity");
                break;
        }
    }
}

function createRobotVizu(i) {
    var robotId = ""
    var name = ""
    robotId = "robot" + i
    name = "R" + i
    Qt.createQmlObject(
        'import QtQuick 2.2; \
                    Image{id: robotImage' + robotId + ';source: ' + robotId + '.kidnapped ? "../assets/redHexagon.svg" : "../assets/greenHexagon.svg";rotation: -' + robotId + '.theta;x: ' + robotId + '.x*gridSpacing*parent.scaleCoeff - width/2;y: ' + robotId + '.y*gridSpacing*parent.scaleCoeff - height/2;sourceSize.width: parent.robotSideToSide*parent.scaleCoeff;sourceSize.height: parent.robotDiagonal*parent.scaleCoeff;z: 5; \
                    Text {text: "' + name + '";anchors.horizontalCenter: robotImage' + robotId + '.horizontalCenter;anchors.verticalCenter: robotImage' + robotId + '.verticalCenter;z: 10;font.pointSize: 24; font.bold: true;} \
                    }',
        page, 'robot')

}
