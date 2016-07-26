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
#include <QDebug>

CelluloZonePolyBezier::CelluloZonePolyBezier() : CelluloZone(){}

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

    invalidateCalc();
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

void CelluloZonePolyBezier::sendPathToRobot(CelluloBluetooth* robot) const {
    if(segments.isEmpty())
        qDebug() << "CelluloZonePolyBezier::sendPathToRobot(): Path is empty.";
    else{
        robot->polyBezierInit(segments[0].getControlPoint(0));
        for(auto segment : segments)
            robot->polyBezierAppend(segment.getControlPoint(1), segment.getControlPoint(2), segment.getControlPoint(3));
    }
}

void CelluloZonePolyBezier::calculateBoundingBox(){
    if(boundingBoxCalculated)
        return;

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

    boundingBoxCalculated = true;
}

bool CelluloZonePolyBezier::inBoundingBox(const QVector2D& m){
    calculateBoundingBox();
    return minX <= m.x() && m.x() <= maxX && minY <= m.y() && m.y() <= maxY;
}

void CelluloZonePolyBezier::invalidateCalc(){
    boundingBoxCalculated = false;
}

qreal CelluloZonePolyBezier::getClosestDistance(const QVector2D& m){
    QVector2D dummy;
    return getClosestDistance(m, dummy);
}

qreal CelluloZonePolyBezier::getClosestDistance(const QVector2D& m, QVector2D& closestPoint){
    qreal dist, dummy;
    QVector2D point;
    qreal closestDist = std::numeric_limits<qreal>::max();
    for(auto segment : segments)

        //First, check distance to bounding box, if this rough distance is not good enough, actual curve distance won't be
        if(segment.getDistToBoundingBox(m) < closestDist){
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

QVector2D CelluloZonePolyBezierDistance::getClosestPoint(const QVector2D& m){
    QVector2D closestPoint;
    getClosestDistance(m, closestPoint);
    return closestPoint;
}

float CelluloZonePolyBezierDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    return getClosestDistance(QVector2D(xRobot, yRobot));
}

void CelluloZonePolyBezierDistance::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolyBezier::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QBrush(color), 2, Qt::DotLine));

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
 * CelluloZonePolyBezierBorder
 */

CelluloZonePolyBezierBorder::CelluloZonePolyBezierBorder() : CelluloZonePolyBezier(){
    type = CelluloZoneTypes::POLYBEZIERBORDER;
    borderThickness = 0;
}

void CelluloZonePolyBezierBorder::setBorderThickness(qreal newThickness){
    if(borderThickness != newThickness){
        borderThickness = newThickness;
        emit borderThicknessChanged();
        updatePaintedItem();
    }
}

void CelluloZonePolyBezierBorder::write(QJsonObject &json){
    CelluloZonePolyBezier::write(json);

    json["borderThickness"] = borderThickness;
}

void CelluloZonePolyBezierBorder::read(const QJsonObject &json){
    CelluloZonePolyBezier::read(json);

    borderThickness = json["borderThickness"].toDouble();
}

float CelluloZonePolyBezierBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    return getClosestDistance(QVector2D(xRobot, yRobot)) <= borderThickness/2 ? 1.0f : 0.0f;
}

void CelluloZonePolyBezierBorder::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolyBezier::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    QVector2D scale(canvasWidth/physicalWidth, canvasHeight/physicalHeight);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QColor(color), borderThickness*(scale.x() + scale.y())/2, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));

    //Draw segments separately to ensure round caps
    for(auto segment : segments){
        QPainterPath path;
        path.moveTo((scale*segment.getControlPoint(0)).toPointF());
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

    QVector2D robotPos(xRobot, yRobot);

    //Check if point is outside the bounding box
    if(!inBoundingBox(robotPos))
        return 0.0f;

    //Number of crossings on the Bézier segments
    int numCrossings = 0;
    for(auto segment : segments)
        numCrossings += segment.getNumCrossings(robotPos);

    //Check crossing with line segment that closes the curve
    if(!segments.isEmpty())
        if(CelluloMathUtil::hRayCrossesLineSeg(robotPos, segments.first().getControlPoint(0), segments.last().getControlPoint(3)))
            numCrossings++;

    return numCrossings % 2 == 1;
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
    }
}
