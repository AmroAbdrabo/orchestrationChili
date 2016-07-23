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

#include "../util/math/CelluloMathUtil.h"

#include <QPointF>

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
        for(int i=0; i<segments.size(); i++){
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
    for(int i=0; i+3<newSize; i+=3)
        segments.push_back(
            CubicBezier(
                newControlPoints[i].value<QVector2D>(),
                newControlPoints[i + 1].value<QVector2D>(),
                newControlPoints[i + 2].value<QVector2D>(),
                newControlPoints[i + 3].value<QVector2D>()
                )
            );

    calculateBoundingBox();
    updatePaintedItem();
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

void CelluloZonePolyBezier::calculateBoundingBox(){
    minX = std::numeric_limits<qreal>::max();
    maxX = std::numeric_limits<qreal>::min();
    minY = std::numeric_limits<qreal>::max();
    maxY = std::numeric_limits<qreal>::min();

    qreal minXSeg, maxXSeg, minYSeg, maxYSeg;
    for(auto segment : segments){
        segment.getBoundingBox(minXSeg, maxXSeg, minYSeg, maxYSeg);
        if(minXSeg < minX)
            minX = minXSeg;
        if(maxXSeg > maxX)
            maxX = maxXSeg;
        if(minYSeg < minY)
            minY = minYSeg;
        if(maxYSeg > maxY)
            maxY = maxYSeg;
    }
}

qreal CelluloZonePolyBezier::getClosestDistance(const QVector2D& m){
    QVector2D dummy;
    return getClosestDistance(m, dummy);
}

qreal CelluloZonePolyBezier::getClosestDistance(const QVector2D& m, QVector2D& closestPoint){
    qreal dist, dummy;
    QVector2D point;
    qreal closestDist = std::numeric_limits<qreal>::max();
    for(auto segment : segments){
        segment.getClosestPoint(m, point, dist, dummy);
        if(dist < closestDist){
            closestDist = dist;
            closestPoint = point;
        }
    }
    return closestDist;
}

/**
 * CelluloZonePolyBezierDistance
 */

CelluloZonePolyBezierDistance::CelluloZonePolyBezierDistance() : CelluloZonePolyBezier(){
    type = CelluloZoneTypes::POLYBEZIERDISTANCE;
}

float CelluloZonePolyBezierDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    return getClosestDistance(QVector2D(xRobot, yRobot));
}

void CelluloZonePolyBezierDistance::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolyBezier::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QBrush(color), 2));

    QVector2D scale(canvasWidth/physicalWidth, canvasHeight/physicalHeight);

    if(segments.size() > 0){
        QPainterPath path;

        path.moveTo((scale*segments[0].getControlPoint(0)).toPointF());
        for(auto segment : segments)
            path.cubicTo(
                (scale*segment.getControlPoint(1)).toPointF(),
                (scale*segment.getControlPoint(2)).toPointF(),
                (scale*segment.getControlPoint(3)).toPointF()
                );

        painter->drawPath(path);
    }
}

/**
 * CelluloZonePolyBezierInner
 */

CelluloZonePolyBezierInner::CelluloZonePolyBezierInner() : CelluloZonePolyBezier(){
    type = CelluloZoneTypes::POLYBEZIERINNER;
}

float CelluloZonePolyBezierInner::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);

    for(auto segment : segments){
        qDebug() << segment.side(QVector2D(xRobot, yRobot));
    }

    updatePaintedItem();
    return 0;
}

void CelluloZonePolyBezierInner::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolyBezier::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(QBrush(color));
    painter->setPen(Qt::NoPen);

    QVector2D scale(canvasWidth/physicalWidth, canvasHeight/physicalHeight);

    if(segments.size() > 0){
        QPainterPath path;

        path.moveTo((scale*segments[0].getControlPoint(0)).toPointF());
        for(auto segment : segments)
            path.cubicTo(
                (scale*segment.getControlPoint(1)).toPointF(),
                (scale*segment.getControlPoint(2)).toPointF(),
                (scale*segment.getControlPoint(3)).toPointF()
                );

        painter->drawPath(path);



        //for(auto segment : segments)
        //for(int i=0;i<segment.T_LUT_SIZE;i++){
        //QVector2D pt = segment.equidistantPointLut[i];
        //painter->drawPoint(QPointF(pt.x()*horizontalScaleCoeff, pt.y()*verticalScaleCoeff));
        //}
    }

    painter->setPen(QPen(QBrush("green"), 2));
    painter->drawLine((scale*curvePt).toPointF(), (scale*(curvePt + tangentVec)).toPointF());





























    qreal x1, x2, x3;
    qreal num = CelluloMathUtil::solveCubicEq(1,1,0,-0.1,x1,x2,x3);
    qDebug() << num << " " << x1 << " " << x2 << " " << x3;
}
