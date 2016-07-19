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
 * @file CelluloZoneAngle.cpp
 * @brief Source for single angle zones
 * @author Ayberk Özgür
 * @date 2018-07-18
 */

#include "CelluloZoneAngle.h"

#include <cmath>

#include "../util/CelluloMathUtil.h"

/**
 * CelluloZoneAngle
 */

CelluloZoneAngle::CelluloZoneAngle() : CelluloZone(){
    angle = 0;
}

void CelluloZoneAngle::setAngle(float newAngle) {
    while(newAngle < 0)
        newAngle += 360;
    while(newAngle >= 360)
        newAngle -= 360;

    if(newAngle != angle){
        angle = newAngle;
        emit(angleChanged());
        updatePaintedItem();
    }
}

void CelluloZoneAngle::write(QJsonObject &json){
    CelluloZone::write(json);

    json["angle"] = angle;
}

void CelluloZoneAngle::read(const QJsonObject &json){
    CelluloZone::read(json);

    angle = json["angle"].toDouble();
}

void CelluloZoneAngle::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    Q_UNUSED(color);
    Q_UNUSED(canvasWidth);
    Q_UNUSED(canvasHeight);
    Q_UNUSED(physicalWidth);
    Q_UNUSED(physicalHeight);
    painter->setRenderHint(QPainter::Antialiasing);
}

/**
 * CelluloZoneAngleThreshold
 */

CelluloZoneAngleThreshold::CelluloZoneAngleThreshold() : CelluloZoneAngle(){
    type = CelluloZoneTypes::ANGLETHRESHOLD;
    currentValue = 0;
    prevDiff = 0;
}

float CelluloZoneAngleThreshold::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(xRobot);
    Q_UNUSED(yRobot);

    while(thetaRobot < 0)
        thetaRobot += 360;
    while(thetaRobot >= 360)
        thetaRobot -= 360;

    qreal diff = angle - thetaRobot;
    while(diff <= -180)
        diff += 360;
    while(diff > 180)
        diff -= 360;

    if(currentValue == 0){
        prevDiff = diff;
        currentValue = -1;
    }

    if(-90 <= diff && diff <= 90)
        if((prevDiff > 0 && diff <= 0) || (prevDiff <= 0 && diff > 0))
            currentValue = -currentValue;

    prevDiff = diff;

    return currentValue;
}

void CelluloZoneAngleThreshold::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneAngle::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(QBrush(color));
    painter->setPen(Qt::NoPen);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    //TODO: FIGURE THIS OUT
    //painter->drawRect(x*horizontalScaleCoeff, y*verticalScaleCoeff, width*horizontalScaleCoeff, height*verticalScaleCoeff);
}
