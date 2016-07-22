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
 * @file CubicBezier.cpp
 * @brief Source for a cubic Bézier curve
 * @author Ayberk Özgür
 * @date 2016-07-21
 */

#include "CubicBezier.h"

#include <QDebug>


CubicBezier::CubicBezier(){}

CubicBezier::CubicBezier(const QVector2D& p0, const QVector2D& p1, const QVector2D& p2, const QVector2D& p3){
    setControlPoints(p0, p1, p2, p3);
}

void CubicBezier::setControlPoints(const QVector2D& p0, const QVector2D& p1, const QVector2D& p2, const QVector2D& p3){
    p[0] = p0;
    p[1] = p1;
    p[2] = p2;
    p[3] = p3;

    buildEquidistantTLUT();
}

QVector2D CubicBezier::getControlPoint(unsigned char i){
    if(i > 3)
        return QVector2D();
    else
        return p[i];
}

QVector2D CubicBezier::getPoint(qreal t){
    if(t == 0)
        return p[0];
    else if(t == 1)
        return p[3];
    else{
        qreal one_minus_t = 1 - t;
        qreal one_minus_t_squared = one_minus_t*one_minus_t;
        qreal t_squared = t*t;
        return one_minus_t_squared*(one_minus_t*p[0] + 3*t*p[1]) + t_squared*(3*one_minus_t*p[2] + t*p[3]);
    }
}

void CubicBezier::buildEquidistantTLUT(){
    static const int numSteps = 100; //Number of discretization steps
    qreal distances[numSteps + 1];
    QVector2D points[numSteps + 1];

    //First pass, calculate distances to equidistant t
    distances[0] = 0;
    points[0] = getPoint(0);
    for(int i=1;i<=numSteps;i++){
        qreal t = i/((qreal)numSteps);
        points[i] = getPoint(t);
        distances[i] = distances[i - 1] + points[i].distanceToPoint(points[i - 1]);
    }
    curveLength = distances[numSteps];
    qreal lutDist = curveLength/((qreal)(T_LUT_SIZE - 1));

    //Second pass, pick t that are equidistant on the curve
    int ti = 0;
    for(int i=0;i<=numSteps;i++)
        if(distances[i] >= ti*lutDist){
            equidistantTLut[ti] = i/((qreal)numSteps);
            equidistantPointLut[ti] = points[i];
            ti++;
        }
}

void CubicBezier::getClosestPoint(const QVector2D& m, QVector2D& closestPoint, qreal& closestDist){
    qreal closestT;
    closestDist = std::numeric_limits<qreal>::max();

    //Find closest point in lookup table
    for(int i=0;i<T_LUT_SIZE;i++){
        qreal currentDist = equidistantPointLut[i].distanceToPoint(m);
        if(currentDist < closestDist){
            closestT = equidistantTLut[i];
            closestDist = currentDist;
            closestPoint = equidistantPointLut[i];
        }
    }

    //Check interval around for a closer point
    qreal intervalSizeEpsilon = T_INTERVAL_EPSILON/curveLength;
    qreal currentIntervalSize = T_INTERVAL_SIZE;
    while(currentIntervalSize > intervalSizeEpsilon){
        qreal leftT = closestT - currentIntervalSize;
        qreal rightT = closestT + currentIntervalSize;
        QVector2D leftPoint = leftT >= 0 ? getPoint(leftT) : QVector2D();
        QVector2D rightPoint = rightT <= 1 ? getPoint(rightT) : QVector2D();
        qreal leftDist = leftT >= 0 ? leftPoint.distanceToPoint(m) : std::numeric_limits<qreal>::max();
        qreal rightDist = rightT <= 1 ? rightPoint.distanceToPoint(m) : std::numeric_limits<qreal>::max();

        if(leftDist < closestDist && leftDist < rightDist){
            closestT = leftT;
            closestDist = leftDist;
            closestPoint = leftPoint;
        }
        else if(rightDist < closestDist && rightDist < leftDist){
            closestT = rightT;
            closestDist = rightDist;
            closestPoint = rightPoint;
        }

        currentIntervalSize /= 2;
    }
}
