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

QList<QVector2D> CelluloZonePolyBezier::getControlPoints(){
    QList<QVector2D> points;

    if(segments.size() > 0){
        points.push_back(segments[0].getControlPoint(0));
        points.push_back(segments[0].getControlPoint(1));
        points.push_back(segments[0].getControlPoint(2));
        points.push_back(segments[0].getControlPoint(3));
        for(int i=1;i<segments.size();i++){
            points.push_back(segments[i].getControlPoint(1));
            points.push_back(segments[i].getControlPoint(2));
            points.push_back(segments[i].getControlPoint(3));
        }
    }

    return points;
}

void CelluloZonePolyBezier::setControlPoints(const QList<QVector2D>& newControlPoints){
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
        segments.push_back(CubicBezier(newControlPoints[i], newControlPoints[i + 1], newControlPoints[i + 2], newControlPoints[i + 3]));

    emit controlPointsChanged();
}
