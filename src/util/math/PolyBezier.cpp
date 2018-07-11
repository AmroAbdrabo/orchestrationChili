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
 * @file PolyBezier.cpp
 * @brief A composite cubic Bézier curve
 * @author Ayberk Özgür
 * @date 2018-07-10
 */

#include "PolyBezier.h"

#include "CelluloMathUtil.h"

#include <QPointF>
#include <QDebug>

namespace Cellulo{

PolyBezier::PolyBezier(QQuickItem* parent) : QQuickItem(parent) { }

QVariantList PolyBezier::getControlPoints() const {
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

void PolyBezier::setControlPoints(QVariantList const& newControlPoints){
    int newSize = newControlPoints.size();
    if(newSize < 4){
        qWarning() << "PolyBezier::setControlPoints(): At least 4 points must be provided, not initializing.";
        return;
    }
    int newSizeExtra = (newSize - 1) % 3;
    if(newSizeExtra > 0){
        qWarning() << "PolyBezier::setControlPoints(): New control points contain " << newSizeExtra << " extra points, they will be discarded.";
        newSize -= newSizeExtra;
    }

    segments.clear();
    for(int i=0; i+3<newSize; i+=3)
        segments.push_back(
            CubicBezier(
                newControlPoints[i].value<QVector2D>(),
                newControlPoints[i + 1].value<QVector2D>(),
                newControlPoints[i + 2].value<QVector2D>(),
                newControlPoints[i + 3].value<QVector2D>(),
                false)
            );

    invalidateCalc();
    emit controlPointsChanged();
}

void PolyBezier::removeFirstSegment(){
    if(segments.size() > 0){
        segments.removeFirst();
        invalidateCalc();
        emit controlPointsChanged();
    }
    else
        qWarning() << "PolyBezier::removeFirstSegment(): Curve empty, doing nothing.";
}

void PolyBezier::clear(){
    if(!segments.isEmpty()){
        segments.clear();
        invalidateCalc();
        emit controlPointsChanged();
    }
}

void PolyBezier::start(QVector2D const& firstPoint, QVector2D const& secondPoint, qreal smoothness){
    if(!segments.isEmpty()){
        qWarning() << "PolyBezier::start(): Called on a nonempty curve, clearing.";
        segments.clear();
    }

    segments.push_back(
        CubicBezier(
            firstPoint,
            (1 - smoothness)*firstPoint     + smoothness*secondPoint,
            (1 - smoothness)*secondPoint    + smoothness*firstPoint,
            secondPoint,
            false)
        );

    invalidateCalc();
    emit controlPointsChanged();
}

void PolyBezier::appendPoint(QVector2D const& targetPoint, qreal entrySmoothness, qreal exitSmoothness){
    if(segments.isEmpty()){
        qWarning() << "PolyBezier::appendPoint(): Called on an empty curve, doing nothing.";
        return;
    }

    QVector2D lastPoint = segments.last().getControlPoint(3);

    //Maximum entry smoothness (C1 continuous) implies equal derivative in previous segment's exit and this segment's
    //entry i.e vector connecting last two control points of the previous segment must be equal to the one connecting
    //the first two control points of this segment. Lower smoothness ensures the same derivative direction (G1
    //continuous) but takes lower magnitude to get the new segment closer to a line:
    QVector2D controlPoint1 = lastPoint + entrySmoothness*(lastPoint - segments.last().getControlPoint(2));

    //We take the second control point on the line segment connecting the first control point to the target point,
    //thus ensuring shortest segment length (by not being outside the triangle made by the starting point, first control
    //point and target point) while having no inflection point (by not being inside the aforementioned triangle),
    //i.e no turning direction change while traveling on the curve. Maximum smoothness makes the second control point
    //equal to the first, minimizing the sharpness. Lower smoothness ensures shorter curve length and quicker arrival
    //to the target:
    QVector2D controlPoint2 = exitSmoothness*controlPoint1 + (1 - exitSmoothness)*targetPoint;

    segments.push_back(
        CubicBezier(
            lastPoint,
            controlPoint1,
            controlPoint2,
            targetPoint,
            false)
        );

    invalidateCalc();
    emit controlPointsChanged();
}

int PolyBezier::getSegmentIndex(qreal& t){
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

qreal PolyBezier::getClosest(const QVector2D& m, QVector2D& closestPoint, qreal& closestDist){
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

QVector2D PolyBezier::getPoint(qreal t){
    int i = getSegmentIndex(t);
    return segments[i].getPoint(t);
}

QVector2D PolyBezier::getTangent(qreal t){
    int i = getSegmentIndex(t);
    return segments[i].getDerivative(t);
}

QVector2D PolyBezier::getNormal(qreal t){
    QVector2D tangent = getTangent(t);
    return QVector2D(-tangent.y(), tangent.x());
}

bool PolyBezier::isInside(QVector2D const& point){

    //Check if point is outside the bounding box
    if(!isInBoundingBox(point))
        return 0.0f;

    //Number of crossings on the Bézier segments
    int numCrossings = 0;
    for(auto segment : segments)
        numCrossings += segment.getNumCrossings(point);

    //Check crossing with line segment that closes the curve
    if(!segments.isEmpty())
        if(CelluloMathUtil::hRayCrossesLineSeg(point, segments.first().getControlPoint(0), segments.last().getControlPoint(3)))
            numCrossings++;

    return numCrossings % 2 == 1;
}

void PolyBezier::calculateBoundingBox(){
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

bool PolyBezier::isInBoundingBox(QVector2D const& point){
    calculateBoundingBox();
    return minX <= point.x() && point.x() <= maxX && minY <= point.y() && point.y() <= maxY;
}

void PolyBezier::invalidateCalc(){
    boundingBoxCalculated = false;
}

}
