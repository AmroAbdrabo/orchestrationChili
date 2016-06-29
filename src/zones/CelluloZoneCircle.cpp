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
 * @file CelluloZoneCircle.cpp
 * @brief Header for circle zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include "CelluloZoneCircle.h"
#include <QQmlEngine>

/**
 * CelluloZoneCircle
 */

CelluloZoneCircle::CelluloZoneCircle() :
    CelluloZone()
{
    x = 0;
    y = 0;
    r = 0;
}

void CelluloZoneCircle::write(QJsonObject &json){
    CelluloZone::write(json);
    json["x"] = x;
    json["y"] = y;
    json["r"] = r;
}

void CelluloZoneCircle::read(const QJsonObject &json){
    CelluloZone::read(json);
    x = json["x"].toDouble();
    y = json["y"].toDouble();
    r = json["r"].toDouble();
}

void CelluloZoneCircle::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){

}

void CelluloZoneCircle::setX(float newX){
    if(newX != x){
        x = newX;
        emit(xChanged());
        updatePaintedItem();
    }
}

void CelluloZoneCircle::setY(float newY){
    if(newY != y){
        y = newY;
        emit(yChanged());
        updatePaintedItem();
    }
}

void CelluloZoneCircle::setR(float newR){
    if(newR != r){
        r = newR;
        emit(rChanged());
        updatePaintedItem();
    }
}

/**
 * CelluloZoneCircleInner
 */

CelluloZoneCircleInner::CelluloZoneCircleInner() :
    CelluloZoneCircle()
{
    type = CelluloZoneTypes::CIRCLEINNER;
}

float CelluloZoneCircleInner::calculate(float xRobot, float yRobot, float thetaRobot){
    return ((xRobot-x)*(xRobot-x) + (yRobot -y)*(yRobot -y) <= r*r) ? 1 : 0;
}

/**
 * CelluloZoneCircleBorder
 */

CelluloZoneCircleBorder::CelluloZoneCircleBorder() :
    CelluloZoneCircle()
{
    type = CelluloZoneTypes::CIRCLEBORDER;
}

float CelluloZoneCircleBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    float temp = (xRobot-x)*(xRobot-x) + (yRobot -y)*(yRobot -y);
    float rOuter = r;// + marginThickeness/2; //TODO: PUT MARGIN HERE
    float rInner = r;// - marginThickeness/2; //TODO: PUT MARGIN HERE
    return temp <= (rOuter*rOuter) && temp > (rInner* rInner) ? 1 : 0;
}

/**
 * CelluloZoneCircleDistance
 */

CelluloZoneCircleDistance::CelluloZoneCircleDistance() :
    CelluloZoneCircle()
{
    type = CelluloZoneTypes::CIRCLEDISTANCE;
}

float CelluloZoneCircleDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    return fabs(sqrt((xRobot-x)*(xRobot-x) + (yRobot -y)*(yRobot -y)) - r);
}
