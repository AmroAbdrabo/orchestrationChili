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
 * @file CelluloZoneLine.cpp
 * @brief Source for the line zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include "CelluloZoneLine.h"

/**
 * CelluloZoneLine
 */

CelluloZoneLine::CelluloZoneLine() :
    CelluloZone()
{
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
}

QVariantMap CelluloZoneLine::getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight){
    QVariantMap properties;
    properties["name"] = QVariant(name);
    properties["stackingOrder"] = QVariant(stackingOrder);
    properties["marginThickeness"] = QVariant(marginThickeness/realPlaygroundWidth);
    properties["x1"] = QVariant(x1/realPlaygroundWidth);
    properties["y1"] = QVariant(y1/realPlaygroundHeight);
    properties["x2"] = QVariant(x2/realPlaygroundWidth);
    properties["y2"] = QVariant(y2/realPlaygroundHeight);
    return properties;
}

void CelluloZoneLine::write(QJsonObject &json){
    json["type"] = CelluloZoneTypes::typeToString(type);
    json["name"] = name;
    json["stackingOrder"] = stackingOrder;
    json["marginThickeness"] = marginThickeness;
    json["x1"] = x1;
    json["y1"] = y1;
    json["x2"] = x2;
    json["y2"] = y2;
}

void CelluloZoneLine::read(const QJsonObject &json){
    type = CelluloZoneTypes::typeFromString(json["type"].toString());
    name = json["name"].toString();
    stackingOrder= json["stackingOrder"].toInt();
    marginThickeness = json["marginThickeness"].toDouble();
    x1 = json["x1"].toDouble();
    y1 = json["y1"].toDouble();
    x2 = json["x2"].toDouble();
    y2 = json["y2"].toDouble();
}

/**
 * CelluloZoneLineDistance
 */

CelluloZoneLineDistance::CelluloZoneLineDistance() :
    CelluloZoneLine()
{
    type = CelluloZoneTypes::LINEDISTANCE;
}

float CelluloZoneLineDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    return pointToSegmentDistance(xRobot, yRobot, x1, y1, x2, y2);
}
