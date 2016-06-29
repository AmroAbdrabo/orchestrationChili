/*
 * Copyright (C) 2016 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file CelluloZone.cpp
 * @brief Source for base class zone architecture
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include "CelluloZone.h"
#include "CelluloZoneClient.h"

CelluloZone::CelluloZone(QQuickItem* parent) :
    QQuickItem(parent)
{
    marginThickeness = 0;
    active = true;
    stackingOrder = 0;
    name = "anonymousZone";
}

void CelluloZone::onClientPoseChanged(qreal x, qreal y, qreal theta){
    CelluloZoneClient* client = qobject_cast<CelluloZoneClient*>(QObject::sender());

    if(client){

        //TODO: REPLACE ACTIVE WITH ENABLED
        if(active){

            //Calculate the new value associated with the client whose pose has changed
            qreal newVal = calculate(x*0.508, y*0.508, theta); //TODO: GET RID OF 0.508

            //We already have a previous value for this client
            if(clientsLastValues.contains(client)){

                //If the value of this zone changed, alert the client
                qreal& oldValRef = clientsLastValues[client];
                if(oldValRef != newVal){
                    emit client->zoneValueChanged(this, newVal);
                    oldValRef = newVal;
                }
            }

            //We don't have a previous value for this client, simply create it and alert the client
            else{
                client->zoneValueChanged(this, newVal);
                clientsLastValues[client] = newVal;
            }
        }
    }
    else
        qDebug() << "CelluloZone::onClientPoseChanged(): Zone can only connect to a CelluloZoneClient-derived object.";
}

void CelluloZone::write(QJsonObject& json){
    json["type"] = CelluloZoneTypes::ZoneTypeString(type);
    json["name"] = name;
    json["stackingOrder"] = stackingOrder;
    json["marginThickeness"] = marginThickeness;
}

void CelluloZone::read(const QJsonObject& json){
    type = CelluloZoneTypes::typeFromString(json["type"].toString());
    name = json["name"].toString();
    stackingOrder= json["stackingOrder"].toInt();
    marginThickeness = json["marginThickeness"].toDouble();
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
    if(len_sq != 0){  //in case of 0 length line
        param = dot / len_sq;
    }

    float xx, yy;

    if(param < 0){
        xx = x1;
        yy = y1;
    }
    else if(param > 1){
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
        for(i = 0, j = pointsQt.size()-1; i < pointsQt.size(); j = i++){
            if( ((pointsQt.at(i).y()>yRobot) != (pointsQt.at(j).y()>yRobot)) &&
                (xRobot < (pointsQt.at(j).x()-pointsQt.at(i).x()) * (yRobot-pointsQt.at(i).y()) / (pointsQt.at(j).y()-pointsQt.at(i).y()) + pointsQt.at(i).x()))
                c = !c;
        }
        return c ? 1 : 0;
    }
    else{
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

CelluloZonePaintedItem* CelluloZone::createPaintedItem(QQuickItem* parent, qreal physicalPlaygroundWidth, qreal physicalPlaygroundHeight){
    CelluloZonePaintedItem* item = new CelluloZonePaintedItem(parent);
    item->setAssociatedZone(this);
    item->setPhysicalPlaygroundWidth(physicalPlaygroundWidth);
    item->setPhysicalPlaygroundHeight(physicalPlaygroundHeight);
    return item;
}
