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
 * @file CelluloZonePoint.cpp
 * @brief Source for the point zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include "CelluloZonePoint.h"

/**
 * CelluloZonePoint
 */

CelluloZonePoint::CelluloZonePoint() :
    CelluloZone()
{
    x = 0;
    y = 0;
}

void CelluloZonePoint::setX(float newX){
    if(newX != x){
        x = newX;
        emit(xChanged());
        updatePaintedItem();
    }
}

void CelluloZonePoint::setY(float newY){
    if(newY != y){
        y = newY;
        emit(yChanged());
        updatePaintedItem();
    }
}

void CelluloZonePoint::write(QJsonObject &json){
    CelluloZone::write(json);
    json["x"] = x;
    json["y"] = y;
}

void CelluloZonePoint::read(const QJsonObject &json){
    CelluloZone::read(json);
    x = json["x"].toDouble();
    y = json["y"].toDouble();
}

void CelluloZonePoint::paint(QPainter* painter, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){

}

/**
 * CelluloZonePointDistance
 */

CelluloZonePointDistance::CelluloZonePointDistance() :
    CelluloZonePoint()
{
    type = CelluloZoneTypes::POINTDISTANCE;
}

float CelluloZonePointDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    return sqrt((xRobot-x)*(xRobot-x) + (yRobot -y)*(yRobot -y));
}
