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

PolyBezier::PolyBezier(){ }

QList<QVector2D> PolyBezier::getControlPoints() const {
    QList<QVector2D> points;
    if(segments.size() > 0){
        points.push_back(segments[0].getControlPoint(0));
        for(auto& segment : segments){
            points.push_back(segment.getControlPoint(1));
            points.push_back(segment.getControlPoint(2));
            points.push_back(segment.getControlPoint(3));
        }
    }
    return points;
}

void PolyBezier::setControlPoints(QList<QVector2D> const& newControlPoints){
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
                newControlPoints[i],
                newControlPoints[i + 1],
                newControlPoints[i + 2],
                newControlPoints[i + 3],
                false)
            );

    invalidateCalc();
}

int PolyBezier::getNumSegments(){
    return segments.size();
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
