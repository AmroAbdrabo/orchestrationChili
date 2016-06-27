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

QVariantMap CelluloZoneRectangle::getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight){
    QVariantMap properties;
    properties["name"] = QVariant(name);
    properties["stackingOrder"] = QVariant(stackingOrder);
    properties["marginThickeness"] = QVariant(marginThickeness/realPlaygroundWidth);
    properties["x"] = QVariant(x/realPlaygroundWidth);
    properties["y"] = QVariant(y/realPlaygroundHeight);
    properties["width"] = QVariant(width/realPlaygroundWidth);
    properties["height"] = QVariant(height/realPlaygroundHeight);
    return properties;
}

void CelluloZoneRectangle::write(QJsonObject &json){
    json["type"] = CelluloZoneTypes::ZoneTypeString(type);
    json["name"] = name;
    json["stackingOrder"] = stackingOrder;
    json["marginThickeness"] = marginThickeness;
    json["x"] = x;
    json["y"] = y;
    json["width"] = width;
    json["height"] = height;
}

void CelluloZoneRectangle::read(const QJsonObject &json){
    type = CelluloZoneTypes::typeFromString(json["type"].toString());
    name = json["name"].toString();
    stackingOrder= json["stackingOrder"].toInt();
    marginThickeness = json["marginThickeness"].toDouble();
    x = json["x"].toDouble();
    y = json["y"].toDouble();
    width = json["width"].toDouble();
    height = json["height"].toDouble();
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

/**
 * CelluloZoneRectangleBorder
 */

CelluloZoneRectangleBorder::CelluloZoneRectangleBorder() :
    CelluloZoneRectangle()
{
    type = CelluloZoneTypes::RECTANGLEBORDER;
}

float CelluloZoneRectangleBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    return
        (((x - (marginThickeness/2)) <= xRobot && (x + width + (marginThickeness/2)) >= xRobot && (y - (marginThickeness/2)) <= yRobot && (y + height + (marginThickeness/2)) >= yRobot) == 1) &&
        (((x + (marginThickeness/2)) <= xRobot && (x + width - (marginThickeness/2)) >= xRobot && (y + (marginThickeness/2)) <= yRobot && (y + height - (marginThickeness/2)) >= yRobot) == 0);
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
