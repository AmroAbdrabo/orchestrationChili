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
 * @brief Source for angular zones
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
    fromAngle = 0;
    toAngle = 0;
}

void CelluloZoneAngle::setFromAngle(float newFromAngle) {
    while(newFromAngle < 0)
        newFromAngle += 360;
    while(newFromAngle >= 360)
        newFromAngle -= 360;

    if(newFromAngle != fromAngle){
        fromAngle = newFromAngle;
        emit(fromAngleChanged());
        updatePaintedItem();
    }
}

void CelluloZoneAngle::setToAngle(float newToAngle) {
    while(newToAngle < 0)
        newToAngle += 360;
    while(newToAngle >= 360)
        newToAngle -= 360;

    if(newToAngle != toAngle){
        toAngle = newToAngle;
        emit(toAngleChanged());
        updatePaintedItem();
    }
}

void CelluloZoneAngle::write(QJsonObject &json){
    CelluloZone::write(json);

    json["fromAngle"] = fromAngle;
    json["toAngle"] = toAngle;
}

void CelluloZoneAngle::read(const QJsonObject &json){
    CelluloZone::read(json);

    fromAngle = json["fromAngle"].toDouble();
    toAngle = json["toAngle"].toDouble();
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
 * CelluloZoneAngleInner
 */

CelluloZoneAngleInner::CelluloZoneAngleInner() : CelluloZoneAngle(){
    type = CelluloZoneTypes::ANGLEINNER;
}

float CelluloZoneAngleInner::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(xRobot);
    Q_UNUSED(yRobot);

    while(thetaRobot < 0)
        thetaRobot += 360;
    while(thetaRobot >= 360)
        thetaRobot -= 360;

    if(fromAngle < toAngle)
        return (fromAngle <= thetaRobot && thetaRobot <= toAngle) ? 1 : 0;
    else if(fromAngle > toAngle)
        return !(toAngle < thetaRobot && thetaRobot < fromAngle) ? 1 : 0;
    else
        return 0;
}

void CelluloZoneAngleInner::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneAngle::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(QBrush(color));
    painter->setPen(Qt::NoPen);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    //TODO: FIGURE THIS OUT
    //painter->drawRect(x*horizontalScaleCoeff, y*verticalScaleCoeff, width*horizontalScaleCoeff, height*verticalScaleCoeff);
}

/**
 * CelluloZoneAngleBorder
 */

CelluloZoneAngleBorder::CelluloZoneAngleBorder() : CelluloZoneAngle(){
    type = CelluloZoneTypes::ANGLEBORDER;
    borderThickness = 0;
}

void CelluloZoneAngleBorder::setBorderThickness(qreal newThickness){
    if(borderThickness != newThickness){
        borderThickness = newThickness;
        emit borderThicknessChanged();
        updatePaintedItem();
    }
}

void CelluloZoneAngleBorder::write(QJsonObject &json){
    CelluloZoneAngle::write(json);

    json["borderThickness"] = borderThickness;
}

void CelluloZoneAngleBorder::read(const QJsonObject &json){
    CelluloZoneAngle::read(json);

    borderThickness = json["borderThickness"].toDouble();
}

float CelluloZoneAngleBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(xRobot);
    Q_UNUSED(yRobot);

    while(thetaRobot < 0)
        thetaRobot += 360;
    while(thetaRobot >= 360)
        thetaRobot -= 360;

    qreal fromDiff = fromAngle - thetaRobot;
    while(fromDiff <= -180)
        fromDiff += 360;
    while(fromDiff > 180)
        fromDiff -= 360;
    fromDiff = fabs(fromDiff);

    qreal toDiff = toAngle - thetaRobot;
    while(toDiff <= -180)
        toDiff += 360;
    while(toDiff > 180)
        toDiff -= 360;
    toDiff = fabs(toDiff);

    return (fromDiff <= borderThickness || toDiff <= borderThickness) ? 1 : 0;
}

void CelluloZoneAngleBorder::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneAngle::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QColor(color), borderThickness*(horizontalScaleCoeff + verticalScaleCoeff)/2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));

    //TODO: FIGURE THIS OUT
    //painter->drawRect(x*horizontalScaleCoeff, y*verticalScaleCoeff, width*horizontalScaleCoeff, height*verticalScaleCoeff);
}

/**
 * CelluloZoneAngleDistance
 */

CelluloZoneAngleDistance::CelluloZoneAngleDistance() : CelluloZoneAngle(){
    type = CelluloZoneTypes::ANGLEDISTANCE;
}

float CelluloZoneAngleDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(xRobot);
    Q_UNUSED(yRobot);

    while(thetaRobot < 0)
        thetaRobot += 360;
    while(thetaRobot >= 360)
        thetaRobot -= 360;

    if(fromAngle < toAngle){
        if(fromAngle <= thetaRobot && thetaRobot <= toAngle)
            return 0;
    }
    else if(fromAngle > toAngle){
        if(!(toAngle < thetaRobot && thetaRobot < fromAngle))
            return 0;
    }

    qreal fromDiff = fromAngle - thetaRobot;
    while(fromDiff <= -180)
        fromDiff += 360;
    while(fromDiff > 180)
        fromDiff -= 360;
    fromDiff = fabs(fromDiff);

    qreal toDiff = toAngle - thetaRobot;
    while(toDiff <= -180)
        toDiff += 360;
    while(toDiff > 180)
        toDiff -= 360;
    toDiff = fabs(toDiff);

    return fmin(fromDiff, toDiff);
}

void CelluloZoneAngleDistance::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneAngle::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(QBrush(color, Qt::Dense5Pattern));
    painter->setPen(Qt::NoPen);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    //TODO: FIGURE THIS OUT
    //painter->drawRect(x*horizontalScaleCoeff, y*verticalScaleCoeff, width*horizontalScaleCoeff, height*verticalScaleCoeff);
}
