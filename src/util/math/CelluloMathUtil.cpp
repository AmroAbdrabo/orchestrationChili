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
 * @file CelluloMathUtil.cpp
 * @brief Header for mathematical and geometrical utilities
 * @author Joanna Salathé
 * @author Ayberk Özgür
 * @date 2016-06-30
 */

#include "CelluloMathUtil.h"

#include <cmath>

CelluloMathUtil::CelluloMathUtil(QObject* parent) : QObject(parent){
}

CelluloMathUtil::~CelluloMathUtil(){
}

qreal CelluloMathUtil::pointToSegmentDist(const QVector2D& p, const QVector2D& seg1, const QVector2D& seg2){
    //Taken from http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment

    const qreal segLenSquared = (seg1 - seg2).lengthSquared();
    if(segLenSquared == 0.0)
        return seg1.distanceToPoint(p);

    //Consider the line extending the segment, parameterized as v + t (w - v).
    //We find projection of point p onto the line.
    //It falls where t = [(p-v) . (w-v)] / |w-v|^2
    //We clamp t from [0,1] to handle points outside the segment vw.
    const qreal t = fmax(0, fmin(1, QVector2D::dotProduct(p - seg1, seg2 - seg1)/segLenSquared));
    const QVector2D projection = seg1 + t*(seg2 - seg1); //Projection falls on the segment
    return projection.distanceToPoint(p);
}

qreal CelluloMathUtil::pointToLineDistSigned(const QVector2D& p, const QVector2D& lp1, const QVector2D& lp2){
    //Taken from https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line

    QVector2D diff = lp2 - lp1;
    return ((diff.y()*p.x() - diff.x()*p.y()) + (lp2.x()*lp1.y() - lp2.y()*lp1.x()))/diff.length();
}

bool CelluloMathUtil::pointInPoly(const QVector2D& p, const QList<QVector2D>& v){
    //Taken from: https://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html

    bool result = false;
    for(int i = 0, j = v.size() - 1; i < v.size(); j = i++){
        if((v[i].y() > p.y()) != (v[j].y() > p.y()) &&
           (p.x() < (v[j].x() - v[i].x())*(p.y() - v[i].y())/(v[j].y() - v[i].y()) + v[i].x()))
            result = !result;
    }
    return result;
}

qreal CelluloMathUtil::pointToPolyBorderDist(const QVector2D& p, const QList<QVector2D>& v){
    qreal minDist = std::numeric_limits<qreal>::max();
    qreal tempDist;
    for(int i=0;i<v.size()-1;i++){
        tempDist = pointToSegmentDist(p, v[i], v[i + 1]);
        if(tempDist < minDist)
            minDist = tempDist;
    }
    tempDist = pointToSegmentDist(p, v[v.size() - 1], v[0]);
    if(tempDist < minDist)
        minDist = tempDist;
    return minDist;
}
