#include "CelluloZone.h"
#include "src/CelluloBluetooth.h"

CelluloZone::CelluloZone(QQuickItem* parent) :
    QQuickItem(parent)
{
    marginThickeness = 0;
    active = true;
    stackingOrder = 0;
    name = "anonymousZone";
}


void CelluloZone::calculateOnPoseChanged(){
    CelluloBluetooth *cellulo = qobject_cast<CelluloBluetooth *>(QObject::sender());
    if(cellulo && active)
    {
        changeInCellulosCalculate(cellulo->getMacAddr(),this->calculate(cellulo->getX()*0.508, cellulo->getY()*0.508, cellulo->getTheta()));
    }
}


void CelluloZone::changeInCellulosCalculate(const QString& key, float value){
    // only emit value changed if the value has actually changed
    QHash<QString, float>::iterator it = cellulosCalculate.find(key);
    if(it != cellulosCalculate.end()){
        if(it.value() != value){
            cellulosCalculate[key] = value;
            emit calculateCelluloChanged(key, value);
        }
    } else {
        cellulosCalculate.insert(key, value);
        emit calculateCelluloChanged(key, value);
    }
}

// taken from http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
float CelluloZone::pointToSegmentDistance(float x,float y, float x1, float y1, float x2, float y2) {
    float A = x - x1;
    float B = y - y1;
    float C = x2 - x1;
    float D = y2 - y1;

    float dot = A * C + B * D;
    float len_sq = C * C + D * D;
    float param = -1;
    if (len_sq != 0) {//in case of 0 length line
        param = dot / len_sq;
    }

    float xx, yy;

    if (param < 0) {
        xx = x1;
        yy = y1;
    }
    else if (param > 1) {
        xx = x2;
        yy = y2;
    }
    else {
        xx = x1 + param * C;
        yy = y1 + param * D;
    }

    float dx = x - xx;
    float dy = y - yy;
    return sqrt(dx * dx + dy * dy);
}

//taken from: https://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
float CelluloZone::pointInPoly(float xRobot, float yRobot,float minX,float maxX, float minY, float maxY, QList<QPointF> pointsQt){
    if(!(xRobot>maxX || xRobot<minX || yRobot>maxY || yRobot<minY)){
        int i, j, c = 0;
        for (i = 0, j = pointsQt.size()-1; i < pointsQt.size(); j = i++) {
            if ( ((pointsQt.at(i).y()>yRobot) != (pointsQt.at(j).y()>yRobot)) &&
                 (xRobot < (pointsQt.at(j).x()-pointsQt.at(i).x()) * (yRobot-pointsQt.at(i).y()) / (pointsQt.at(j).y()-pointsQt.at(i).y()) + pointsQt.at(i).x()))
                c = !c;
        }
        return c? 1:0;
    } else {
        return 0;
    }
}

QList<QPointF> CelluloZone::getRectangleFromLine(float x1,float y1,float x2, float y2, float rectangleWidth){
    QList<QPointF> list;

    float dx = x2-x1;
    float dy = y2-y1;
    float norm = sqrt(dy*dy + dx*dx);

    float v1x = -dy/norm * rectangleWidth;
    float v1y = dx/norm * rectangleWidth;

    float v2x = dy/norm * rectangleWidth;
    float v2y = -dx/norm * rectangleWidth;

    list.append(QPointF(x1+v1x, y1+v1y));
    list.append(QPointF(x2+v1x, y2+v1y));
    list.append(QPointF(x2+v2x, y2+v2y));
    list.append(QPointF(x1+v2x, y1+v2y));

    return list;
}
