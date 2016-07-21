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
 * @file CelluloMathUtil.h
 * @brief Header for mathematical and geometrical utilities
 * @author Joanna Salathé
 * @author Ayberk Özgür
 * @date 2016-06-30
 */

#ifndef CELLULOMATHUTIL_H
#define CELLULOMATHUTIL_H

#include <QObject>
#include <QVector2D>

class CelluloMathUtil : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloMathUtil(QObject* parent = 0);
    ~CelluloMathUtil();

    /**
     * @brief Calculates the distance of a point to a line segment in 2D
     *
     * @param p The point
     * @param seg1 The first endpoint of the line segment
     * @param seg2 The second endpoint of the line segment
     * @return Distance between the point and the line segment
     */
    Q_INVOKABLE static qreal pointToSegmentDist(const QVector2D& p, const QVector2D& seg1, const QVector2D& seg2);

    /**
     * @brief Calculates the signed distance of a point to a line in 2D
     *
     * @param p The point
     * @param lp1 First point the line passes through
     * @param lp2 Second point the line passes through
     * @return Distance between the point and line segment, negative if point is below the line
     */
    Q_INVOKABLE static qreal pointToLineDistSigned(const QVector2D& p, const QVector2D& lp1, const QVector2D& lp2);

    /**
     * @brief Calculates whether the given point is in the given polygon
     *
     * @param p The point
     * @param v The vertices of the polygon
     * @return Whether the point lies in the given polygon
     */
    Q_INVOKABLE static bool pointInPoly(const QVector2D& p, const QList<QVector2D>& v);

    /**
     * @brief Calculates the distance of the point to the polygon border
     *
     * @param p The point (may be in the polygon)
     * @param v The vertices of the polygon
     * @return The distance of the point to the polygon border
     */
    Q_INVOKABLE static qreal pointToPolyBorderDist(const QVector2D& p, const QList<QVector2D>& v);

};

#endif // CELLULOMATHUTIL_H
