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
 * @file CelluloZoneRectangle.cpp
 * @brief Source for the rectangular zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include "CelluloZoneRectangle.h"

/**
 * CelluloZoneRectangle
 */

CelluloZoneRectangle::CelluloZoneRectangle() :
    CelluloZone()
{
    x = 0;
    y = 0;
    height = 0;
    width = 0;
}

void CelluloZoneRectangle::setX(float newX) {
    if(newX!=x){
        x = newX;
        emit(xChanged());
        updatePaintedItem();
    }
}

void CelluloZoneRectangle::setY(float newY) {
    if(newY!=y){
        y = newY;
        emit(yChanged());
        updatePaintedItem();
    }
}

void CelluloZoneRectangle::setHeight(float newHeight) {
    if(newHeight!=height){
        height = newHeight;
        emit(heightChanged());
        updatePaintedItem();
    }
}

void CelluloZoneRectangle::setWidth(float newWidth) {
    if(newWidth!=width){
        width = newWidth;
        emit(widthChanged());
        updatePaintedItem();
    }
}

void CelluloZoneRectangle::write(QJsonObject &json){
    CelluloZone::write(json);

    json["x"] = x;
    json["y"] = y;
    json["width"] = width;
    json["height"] = height;
}

void CelluloZoneRectangle::read(const QJsonObject &json){
    CelluloZone::read(json);

    x = json["x"].toDouble();
    y = json["y"].toDouble();
    width = json["width"].toDouble();
    height = json["height"].toDouble();
}

void CelluloZoneRectangle::paint(QPainter* painter, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    QBrush brush(QColor("#007430"));

    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    painter->drawRect(x*horizontalScaleCoeff, y*verticalScaleCoeff, width*horizontalScaleCoeff, height*verticalScaleCoeff);
}

/**
 * CelluloZoneRectangleInner
 */

CelluloZoneRectangleInner::CelluloZoneRectangleInner() :
    CelluloZoneRectangle()
{
    type = CelluloZoneTypes::RECTANGLEINNER;
}

float CelluloZoneRectangleInner::calculate(float xRobot, float yRobot, float thetaRobot){
    return x <= xRobot && x + width >= xRobot && y <= yRobot && y + height >= yRobot ? 1 : 0;
}

void CelluloZoneRectangleInner::paint(QPainter* painter, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneRectangle::paint(painter, canvasWidth, canvasHeight, physicalWidth, physicalHeight);
}

/**
 * CelluloZoneRectangleBorder
 */

CelluloZoneRectangleBorder::CelluloZoneRectangleBorder() :
    CelluloZoneRectangle()
{
    type = CelluloZoneTypes::RECTANGLEBORDER;
}

float CelluloZoneRectangleBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    return 0; //TODO: GET MARGIN THICKNESS IN HERE
    /*return
        (((x - (marginThickeness/2)) <= xRobot && (x + width + (marginThickeness/2)) >= xRobot && (y - (marginThickeness/2)) <= yRobot && (y + height + (marginThickeness/2)) >= yRobot) == 1) &&
        (((x + (marginThickeness/2)) <= xRobot && (x + width - (marginThickeness/2)) >= xRobot && (y + (marginThickeness/2)) <= yRobot && (y + height - (marginThickeness/2)) >= yRobot) == 0);*/
}

/**
 * CelluloZoneRectangleDistance
 */

CelluloZoneRectangleDistance::CelluloZoneRectangleDistance() :
    CelluloZoneRectangle()
{
    type = CelluloZoneTypes::RECTANGLEDISTANCE;
}

float CelluloZoneRectangleDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    float distances[4] = { pointToSegmentDistance(xRobot, yRobot, x,y,width+x,y),
                           pointToSegmentDistance(xRobot, yRobot, width+x,y,width+x,height+y),
                           pointToSegmentDistance(xRobot, yRobot, width+x,height+y,x,height+y),
                           pointToSegmentDistance(xRobot, yRobot, x,height+y,x,y)};

    float min = std::numeric_limits<float>::max();
    for( int i = 0; i < 4; i++ ){
        if( distances[i] < min ){
            min = distances[i];
        }
    }

    return min;
}
