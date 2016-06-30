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

#include "../util/CelluloMathUtil.h"

/**
 * CelluloZoneLine
 */

CelluloZoneLine::CelluloZoneLine() : CelluloZone(){
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
}

void CelluloZoneLine::setX1(float newX1){
    if(newX1 != x1){
        x1 = newX1;
        emit(x1Changed());
        updatePaintedItem();
    }
}

void CelluloZoneLine::setY1(float newY1){
    if(newY1 != y1){
        y1 = newY1;
        emit(y1Changed());
        updatePaintedItem();
    }
}

void CelluloZoneLine::setX2(float newX2){
    if(newX2 != x2){
        x2 = newX2;
        emit(x2Changed());
        updatePaintedItem();
    }
}

void CelluloZoneLine::setY2(float newY2){
    if(newY2 != y2){
        y2 = newY2;
        emit(y2Changed());
        updatePaintedItem();
    }
}

void CelluloZoneLine::write(QJsonObject &json){
    CelluloZone::write(json);
    json["x1"] = x1;
    json["y1"] = y1;
    json["x2"] = x2;
    json["y2"] = y2;
}

void CelluloZoneLine::read(const QJsonObject &json){
    CelluloZone::read(json);
    x1 = json["x1"].toDouble();
    y1 = json["y1"].toDouble();
    x2 = json["x2"].toDouble();
    y2 = json["y2"].toDouble();
}

void CelluloZoneLine::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    Q_UNUSED(color);
    Q_UNUSED(canvasWidth);
    Q_UNUSED(canvasHeight);
    Q_UNUSED(physicalWidth);
    Q_UNUSED(physicalHeight);
    painter->setRenderHint(QPainter::Antialiasing);
}

/**
 * CelluloZoneLineDistance
 */

CelluloZoneLineDistance::CelluloZoneLineDistance() : CelluloZoneLine(){
    type = CelluloZoneTypes::LINEDISTANCE;
}

float CelluloZoneLineDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    return CelluloMathUtil::pointToSegmentDist(QVector2D(xRobot, yRobot), QVector2D(x1, y1), QVector2D(x2, y2));
}

void CelluloZoneLineDistance::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneLine::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QBrush(color), 2));

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    painter->drawLine(QPointF(x1*horizontalScaleCoeff, y1*verticalScaleCoeff), QPointF(x2*horizontalScaleCoeff, y2*verticalScaleCoeff));
}
