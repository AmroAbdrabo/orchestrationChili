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

CelluloZonePoint::CelluloZonePoint() :
    CelluloZone()
{
    x = 0;
    y = 0;
}

QVariantMap CelluloZonePoint::getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight){
    QVariantMap properties;
    properties["name"] = QVariant(name);
    properties["stackingOrder"] = QVariant(stackingOrder);
    properties["marginThickeness"] = QVariant(marginThickeness/realPlaygroundWidth);
    properties["x"] = QVariant(x/realPlaygroundWidth);
    properties["y"] = QVariant(y/realPlaygroundHeight);
    return properties;
}

void CelluloZonePoint::write(QJsonObject &json){
    json["type"] = CelluloZoneTypes::typeToString(type);
    json["name"] = name;
    json["stackingOrder"] = stackingOrder;
    json["marginThickeness"] = marginThickeness;
    json["x"] = x;
    json["y"] = y;
}

void CelluloZonePoint::read(const QJsonObject &json){
    type = CelluloZoneTypes::typeFromString(json["type"].toString());
    name = json["name"].toString();
    stackingOrder= json["stackingOrder"].toInt();
    marginThickeness = json["marginThickeness"].toDouble();
    x = json["x"].toDouble();
    y = json["y"].toDouble();
}

CelluloZonePointInner::CelluloZonePointInner() :
    CelluloZonePoint()
{
    type = CelluloZoneTypes::POINTINNER;
}

float CelluloZonePointInner::calculate(float xRobot, float yRobot, float thetaRobot){
    return xRobot == x && yRobot == y;
}

CelluloZonePointDistance::CelluloZonePointDistance() :
    CelluloZonePoint()
{
    type = CelluloZoneTypes::POINTDISTANCE;
}

float CelluloZonePointDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    return sqrt((xRobot-x)*(xRobot-x) + (yRobot -y)*(yRobot -y));
}
