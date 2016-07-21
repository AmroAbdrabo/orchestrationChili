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
 * @file CelluloZonePolyBezier.cpp
 * @brief Source for composite cubic Bézier curves
 * @author Ayberk Özgür
 * @date 2016-07-21
 */

#include "CelluloZonePolyBezier.h"

CelluloZonePolyBezier::CelluloZonePolyBezier() : CelluloZone(){
    maxX = std::numeric_limits<qreal>::min();
    maxY = std::numeric_limits<qreal>::min();
    minX = std::numeric_limits<qreal>::max();
    minY = std::numeric_limits<qreal>::max();
}

QVariantList CelluloZonePolyBezier::getControlPoints(){
    QVariantList points;

    if(segments.size() > 0){
        points.push_back(QVariant(segments[0].getControlPoint(0)));
        for(int i=0;i<segments.size();i++){
            points.push_back(QVariant(segments[i].getControlPoint(1)));
            points.push_back(QVariant(segments[i].getControlPoint(2)));
            points.push_back(QVariant(segments[i].getControlPoint(3)));
        }
    }

    return points;
}

void CelluloZonePolyBezier::setControlPoints(const QVariantList& newControlPoints){
    int newSize = newControlPoints.size();

    if(newSize < 4){
        qWarning() << "CelluloZonePolyBezier::setControlPoints(): At least 4 points must be provided, not initializing.";
        return;
    }

    int newSizeExtra = (newSize - 1) % 3;
    if(newSizeExtra != 0){
        qWarning() << "CelluloZonePolyBezier::setControlPoints(): New control points contain " << newSizeExtra << " extra points, they will be discarded.";
        newSize -= newSizeExtra;
    }

    segments.clear();
    for(int i=0;i+3<newSize;i+=3)
        segments.push_back(
            CubicBezier(
                newControlPoints[i].value<QVector2D>(),
                newControlPoints[i + 1].value<QVector2D>(),
                newControlPoints[i + 2].value<QVector2D>(),
                newControlPoints[i + 3].value<QVector2D>()
            )
        );

    emit controlPointsChanged();
}

void CelluloZonePolyBezier::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    Q_UNUSED(color);
    Q_UNUSED(canvasWidth);
    Q_UNUSED(canvasHeight);
    Q_UNUSED(physicalWidth);
    Q_UNUSED(physicalHeight);
    painter->setRenderHint(QPainter::Antialiasing);
}

void CelluloZonePolyBezier::write(QJsonObject& json){
    CelluloZone::write(json);

    QJsonArray controlPointsArray;
        QJsonObject controlPointObj;
        for(const QVariant& controlPoint : getControlPoints()){
        controlPointObj["x"] = controlPoint.value<QVector2D>().x();
        controlPointObj["y"] = controlPoint.value<QVector2D>().y();
        controlPointsArray.append(controlPointObj);
    }
    json["controlPoints"] = controlPointsArray;
}

void CelluloZonePolyBezier::read(const QJsonObject &json){
    CelluloZone::read(json);

    QVariantList newControlPoints;
    QJsonArray controlPointsArray = json["controlPoints"].toArray();
    for(const QJsonValue& controlPointValue : controlPointsArray){
        const QJsonObject& controlPointObj = controlPointValue.toObject();
        newControlPoints.append(QVariant(QVector2D(controlPointObj["x"].toDouble(), controlPointObj["y"].toDouble())));
    }
    setControlPoints(newControlPoints);
}

/**
 * CelluloZonePolyBezierInner
 */

CelluloZonePolyBezierInner::CelluloZonePolyBezierInner() : CelluloZonePolyBezier(){
    type = CelluloZoneTypes::POLYBEZIERINNER;
}

float CelluloZonePolyBezierInner::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);








    return 0;
}

void CelluloZonePolyBezierInner::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolyBezier::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(QBrush(color));
    painter->setPen(Qt::NoPen);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    if(segments.size() > 0){
        QPainterPath path;

        path.moveTo(segments[0].getControlPoint(0).x()*horizontalScaleCoeff, segments[0].getControlPoint(0).y()*verticalScaleCoeff);
        for(auto segment : segments)
            path.cubicTo(
                segment.getControlPoint(1).x()*horizontalScaleCoeff, segment.getControlPoint(1).y()*verticalScaleCoeff,
                segment.getControlPoint(2).x()*horizontalScaleCoeff, segment.getControlPoint(2).y()*verticalScaleCoeff,
                segment.getControlPoint(3).x()*horizontalScaleCoeff, segment.getControlPoint(3).y()*verticalScaleCoeff
            );

        painter->drawPath(path);
    }
}
