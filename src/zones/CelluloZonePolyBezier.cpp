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

namespace Cellulo{

CelluloZonePolyBezier::CelluloZonePolyBezier() : CelluloZone(){}

QVariantList CelluloZonePolyBezier::getControlPoints(){
    QVariantList points;

    if(segments.size() > 0){
        points.push_back(QVariant(segments[0].getControlPoint(0)));
        for(auto& segment : segments){
            points.push_back(QVariant(segment.getControlPoint(1)));
            points.push_back(QVariant(segment.getControlPoint(2)));
            points.push_back(QVariant(segment.getControlPoint(3)));
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

bool CelluloZonePolyBezier::isMouseInside(QVector2D  mousePosition, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    float mouseX = mousePosition.x()/canvasWidth*physicalWidth;
    float mouseY = mousePosition.y()/canvasHeight*physicalHeight;
    return isPointInside(mouseX,mouseY);
}

bool CelluloZonePolyBezier::isPointInside(float pointX, float pointY){
    QVector2D robotPos(pointX, pointY);

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

int CelluloZonePolyBezier::getSegmentIndex(qreal& t){
    if(t >= segments.size()){
        t = 1;
        return segments.size() - 1;
    }
    else if(t < 0){
        t = 0;
        return 0;
    }
    else{
        int i = (int)t;
        t = t - i;
        return i;
    }
}

qreal CelluloZonePolyBezier::getClosest(const QVector2D& m, QVector2D& closestPoint, qreal& closestDist){
    qreal dist, t, closestT = 0;
    QVector2D point;
    closestDist = std::numeric_limits<qreal>::max();
    int closestSegment = 0;
    for(int i=0;i<segments.size();i++){
        CubicBezier& segment = segments[i];

        //First, check distance to bounding box, if this rough distance is not good enough, actual curve distance won't be
        if(segment.getDistToBoundingBox(m) < closestDist){
            t = segment.getClosest(m, point, dist);
            if(dist < closestDist){
                closestPoint = point;
                closestDist = dist;
                closestT = t;
                closestSegment = i;
            }
        }
    }
    return closestT + closestSegment;
}

QVector2D CelluloZonePolyBezier::getPoint(qreal t){
    int i = getSegmentIndex(t);
    return segments[i].getPoint(t);
}

QVector2D CelluloZonePolyBezier::getTangent(qreal t){
    int i = getSegmentIndex(t);
    return segments[i].getDerivative(t);
}

QVector2D CelluloZonePolyBezier::getNormal(qreal t){
    QVector2D tangent = getTangent(t);
    return QVector2D(-tangent.y(), tangent.x());
}

/**
 * CelluloZonePolyBezierClosestT
 */

CelluloZonePolyBezierClosestT::CelluloZonePolyBezierClosestT() : CelluloZonePolyBezier(){
    type = CelluloZoneTypes::POLYBEZIERCLOSESTT;
}

float CelluloZonePolyBezierClosestT::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    QVector2D dummyv;
    qreal dummyf;
    return getClosest(QVector2D(xRobot, yRobot), dummyv, dummyf);
}

void CelluloZonePolyBezierClosestT::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
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
 * CelluloZonePolyBezierXT
 */

CelluloZonePolyBezierXT::CelluloZonePolyBezierXT() : CelluloZonePolyBezierClosestT(){
    type = CelluloZoneTypes::POLYBEZIERXT;
}

float CelluloZonePolyBezierXT::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(yRobot);
    Q_UNUSED(thetaRobot);

    qreal t = (qreal)segments.size()/2;
    qreal intervalSize = (qreal)segments.size()/4;

    //Assumption that curve is 1-to-1 on the x/y axes, i.e is a function of the form y = f(t), allows us to give an increasing/decreasing direction
    qreal incDecCoeff = segments.last().getPointX(1) >= segments.first().getPointX(0) ? 1 : -1;

    //Outside curve cases
    if(incDecCoeff > 0){
        if(xRobot >= segments.last().getPointX(1))
            return segments.size();
        else if(xRobot <= segments.first().getPointX(0))
            return 0;
    }
    else{
        if(xRobot <= segments.last().getPointX(1))
            return segments.size();
        else if(xRobot >= segments.first().getPointX(0))
            return 0;
    }

    //Binary search for t that gives x
    while(intervalSize >= GET_T_LIM_T){
        qreal localT = t;
        int i = getSegmentIndex(localT);
        qreal currentX = segments[i].getPointX(localT);

        if(currentX > xRobot){
            if(currentX - xRobot <= GET_T_EPSILON)
                break;
            else
                t -= incDecCoeff*intervalSize;
        }
        else{
            if(xRobot - currentX <= GET_T_EPSILON)
                break;
            else
                t += incDecCoeff*intervalSize;
        }

        intervalSize /= 2;
    }

    return t;
}

void CelluloZonePolyBezierXT::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolyBezierClosestT::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);
}

/**
 * CelluloZonePolyBezierYT
 */

CelluloZonePolyBezierYT::CelluloZonePolyBezierYT() : CelluloZonePolyBezierClosestT(){
    type = CelluloZoneTypes::POLYBEZIERYT;
}

float CelluloZonePolyBezierYT::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(xRobot);
    Q_UNUSED(thetaRobot);

    qreal t = (qreal)segments.size()/2;
    qreal intervalSize = (qreal)segments.size()/4;

    //Assumption that curve is 1-to-1 on the x/y axes, i.e is a function of the form y = f(t), allows us to give an increasing/decreasing direction
    qreal incDecCoeff = segments.last().getPointY(1) >= segments.first().getPointY(0) ? 1 : -1;

    //Outside curve cases
    if(incDecCoeff > 0){
        if(yRobot >= segments.last().getPointY(1))
            return segments.size();
        else if(yRobot <= segments.first().getPointY(0))
            return 0;
    }
    else{
        if(yRobot <= segments.last().getPointY(1))
            return segments.size();
        else if(yRobot >= segments.first().getPointY(0))
            return 0;
    }

    //Binary search for t that gives x
    while(intervalSize >= GET_T_LIM_T){
        qreal localT = t;
        int i = getSegmentIndex(localT);
        qreal currentY = segments[i].getPointY(localT);

        if(currentY > xRobot){
            if(currentY - yRobot <= GET_T_EPSILON)
                break;
            else
                t -= incDecCoeff*intervalSize;
        }
        else{
            if(yRobot - currentY <= GET_T_EPSILON)
                break;
            else
                t += incDecCoeff*intervalSize;
        }

        intervalSize /= 2;
    }

    return t;
}

void CelluloZonePolyBezierYT::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolyBezierClosestT::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);
}

/**
 * CelluloZonePolyBezierDistance
 */

CelluloZonePolyBezierDistance::CelluloZonePolyBezierDistance() : CelluloZonePolyBezierClosestT(){
    type = CelluloZoneTypes::POLYBEZIERDISTANCE;
}

float CelluloZonePolyBezierDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    QVector2D dummy;
    qreal dist;
    getClosest(QVector2D(xRobot, yRobot), dummy, dist);
    return dist;
}

void CelluloZonePolyBezierDistance::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolyBezierClosestT::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);
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
    QVector2D dummy;
    qreal dist;
    getClosest(QVector2D(xRobot, yRobot), dummy, dist);
    return dist <= borderThickness/2 ? 1.0f : 0.0f;
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

    return isPointInside(xRobot, yRobot) ? 1 : 0;
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

}
