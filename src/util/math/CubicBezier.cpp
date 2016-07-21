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

    //First pass, calculate distances to equidistant t
    distances[0] = 0;
    QVector2D prevP = getPoint(0);
    for(int i=1;i<=numSteps;i++){
        qreal t = i/((qreal)numSteps);
        QVector2D currentP = getPoint(t);
        distances[i] = distances[i - 1] + currentP.distanceToPoint(prevP);
        prevP = currentP;
    }
    qreal curveLength = distances[numSteps];

    //Second pass, pick t that are equidistant on the curve
    int ti = 0;
    for(int i=0;i<=numSteps;i++)
        if(distances[i] >= ti*curveLength/((qreal)T_LUT_SIZE)){
            equidistantTLUT[ti] = i/((qreal)numSteps);
            ti++;
        }
}

qreal CubicBezier::getDistance(const QVector2D& m){

}
